// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/K8_WorldSubsystem.h"

#include "Cadence/K8_UtilityCore.h"

#include "Cadence/Loop/LoopFunctionLibrary.h"

void UK8_WorldSubsystem::OnWorldBeginPlay(UWorld& World) {}

void UK8_WorldSubsystem::Deinitialize()
{
    KillPlayback();
}

bool UK8_WorldSubsystem::InitializeCadence(UK8_WorldSubsystemSettingsDataAsset const* DesiredSettings)
{
    K8_LOG(Error, "Given world settings not valid. Aborting...");
    if (!DesiredSettings)
    {
        K8_LOG(Error, "Given world settings not valid. Aborting...");
        return false;
    }

    this->Settings = DesiredSettings;

    UWorld* World = GetWorld();

    if (!World)
    {
        K8_LOG(Error, "Attempting to initialize Cadence without a valid World. Aborting...")
        return false;
    }

    return InitializeLoopInstances() && SpawnPlaybackActor(World);
}

bool UK8_WorldSubsystem::StartPlayback()
{
    if (!Settings)
    {
        K8_LOG(Error, "Missing settings. Cadence must be initialized first. Aborting...");
        return false;
    }

    if (GetWorld()->GetTimerManager().IsTimerActive(mBeatTimerHandle))
    {
        K8_LOG(Warning, "Loop playback already started. Invalid call.");
        return false;
    }

    mCurrentBeatInLoop = 0;

    GetWorld()->GetTimerManager().SetTimer(mBeatTimerHandle, this, &UK8_WorldSubsystem::HandleBeat,
                                           GetGlobalBeatDuration(), true);

    bLoopDataCacheDirty = true;

    OnPlaybackStarted.Broadcast(GetGlobalLoopSignature());

    K8_LOG(Log, "Loop playback started successfully.");

    return true;
}

void UK8_WorldSubsystem::KillPlayback()
{
    auto& Manager = GetWorld()->GetTimerManager();

    Manager.ClearTimer(mBeatTimerHandle);

    mCurrentBeatInLoop = 0;

    bLoopDataCacheDirty = true;

    if (mLoopPlaybackActor)
    {
        mLoopPlaybackActor->Destroy();
    }
    Settings = nullptr;

    mLoopInstances.Empty();
}

bool UK8_WorldSubsystem::MuteLoopTypePlayback(ELoopType type)
{
    FLoopInstance& LoopInstance = mLoopInstances[type];

    if (!LoopInstance.bIsMuted)
    {
        LoopInstance.bIsMuted = true;

        bLoopDataCacheDirty = true;

        OnMuteLoopTypePlaybackSuccess.Broadcast(type);
        return true;
    }
    return false;
}

bool UK8_WorldSubsystem::UnmuteLoopTypePlayback(ELoopType type)
{
    FLoopInstance& LoopInstance = mLoopInstances[type];

    if (LoopInstance.bIsMuted)
    {
        LoopInstance.bIsMuted = false;

        bLoopDataCacheDirty = true;

        OnUnmuteLoopTypePlaybackSuccess.Broadcast(type);
        return true;
    }
    return false;
}

FLoopItemPayload UK8_WorldSubsystem::AddItemToUserLoop(const FLoopItem& Item)
{
    FLoopInstance& UserLoop = mLoopInstances.FindChecked(ELoopType::USER);

    if (UserLoop.bIsMuted)
    {
        K8_LOG(Warning, "Attempting to modify user loop while it is muted. Aborting...");
        return { .BeatInLoop = INDEX_NONE, .OrderInBeat = INDEX_NONE, .Item = {} };
    }

    const int32 TargetBeat = (mCurrentBeatInLoop + 1) % GetGlobalLoopSignature().TotalBeatsPerLoop;

    const FLoopItemPayload Payload = ULoopFunctionLibrary::AddItemToLoopAtBeat(UserLoop, TargetBeat,
                                                                               Item);

    if (Payload.BeatInLoop > INDEX_NONE && Payload.OrderInBeat > INDEX_NONE)
    {
        bLoopDataCacheDirty = true;

        OnUserLoopAdd.Broadcast(Payload);
    }

    return Payload;
}

FLoopItemPayload UK8_WorldSubsystem::UndoLastItemInUserLoop()
{
    FLoopInstance& UserLoop = mLoopInstances.FindChecked(ELoopType::USER);

    if (UserLoop.bIsMuted)
    {
        K8_LOG(Warning, "Attempting to modify user loop while it is muted. Aborting...");
        return { .BeatInLoop = INDEX_NONE, .Item = {} };
    }

    const FLoopItemPayload Payload = ULoopFunctionLibrary::RemoveLastAddedLoopItem(UserLoop);

    if (Payload.BeatInLoop != INDEX_NONE)
    {
        OnUserLoopUndo.Broadcast(Payload);
        bLoopDataCacheDirty = true;
    }

    return Payload;
}

void UK8_WorldSubsystem::ClearUserLoop()
{
    FLoopInstance& UserLoop = mLoopInstances.FindChecked(ELoopType::USER);

    if (UserLoop.bIsMuted)
    {
        K8_LOG(Warning, "Attempting to modify user loop while it is muted. Aborting...");
        return;
    }

    ULoopFunctionLibrary::ClearAllLoopItems(UserLoop);

    bLoopDataCacheDirty = true;

    OnUserLoopCleared.Broadcast();
}

bool UK8_WorldSubsystem::ToggleUserGoalLoopPlayback()
{
    if (mLoopInstances.FindChecked(ELoopType::USER).bIsMuted)
    {
        const bool bSuccess = MuteLoopTypePlayback(ELoopType::GOAL)
                              && UnmuteLoopTypePlayback(ELoopType::USER);
        OnUserGoalLoopPlaybackToggled.Broadcast(ELoopType::USER, ELoopType::GOAL);
        return bSuccess;
    }
    else
    {
        const bool bSuccess = MuteLoopTypePlayback(ELoopType::USER)
                              && UnmuteLoopTypePlayback(ELoopType::GOAL);

        OnUserGoalLoopPlaybackToggled.Broadcast(ELoopType::GOAL, ELoopType::USER);
        return bSuccess;
    }
}

float UK8_WorldSubsystem::ComputeUserToGoalSimilarityScore()
{
    const FLoopInstance& User = mLoopInstances.FindChecked(ELoopType::USER);
    const FLoopInstance& Goal = mLoopInstances.FindChecked(ELoopType::GOAL);

    float Score = ULoopFunctionLibrary::ComputeLoopSimilarityScore(User, Goal.Data);

    OnUserToGoalSimilarityScoreComputed.Broadcast(Score);

    return Score;
}

float UK8_WorldSubsystem::GetGlobalLoopDuration() const
{
    return mLoopInstances.FindChecked(ELoopType::TEMPLATE).Signature.LoopDuration;
}

float UK8_WorldSubsystem::GetGlobalBeatDuration() const
{
    return mLoopInstances.FindChecked(ELoopType::TEMPLATE).Signature.BeatDuration;
}

bool UK8_WorldSubsystem::IsMuted(ELoopType type) const
{
    return mLoopInstances.FindChecked(type).bIsMuted;
}

const FLoopRootSignature& UK8_WorldSubsystem::GetGlobalLoopSignature() const
{
    return mLoopInstances.FindChecked(ELoopType::TEMPLATE).Signature;
}

const FLoopData& UK8_WorldSubsystem::GetLoopData(ELoopType type) const
{
    switch (type)
    {
        case ELoopType::USER: return mLoopInstances.FindChecked(ELoopType::USER).Data;
        case ELoopType::GOAL: return mLoopInstances.FindChecked(ELoopType::GOAL).Data;
        default: return mLoopInstances.FindChecked(ELoopType::TEMPLATE).Data;
    }
}

const FLoopInstance& UK8_WorldSubsystem::GetLoopInstance(ELoopType type) const
{
    switch (type)
    {
        case ELoopType::USER: return mLoopInstances.FindChecked(ELoopType::USER);
        case ELoopType::GOAL: return mLoopInstances.FindChecked(ELoopType::GOAL);
        default: return mLoopInstances.FindChecked(ELoopType::TEMPLATE);
    }
}

bool UK8_WorldSubsystem::InitializeLoopInstances()
{
    if (!Settings->TemplateLoopAsset || !Settings->GoalLoopAsset
        || !Settings->GrabbableMaterialDataTable)
    {
        K8_LOG(
            Error,
            "TemplateLoopAsset, GoalLoopAsset, and GrabbableMaterialDataTable must be set properly in settings. Aborting...");
        return false;
    }

    mLoopInstances.Reset();

    mLoopInstances.Add(ELoopType::TEMPLATE,
                       Settings->TemplateLoopAsset
                           ->MakeTemplateLoopInstance(Settings->BeatsPerMinute,
                                                      Settings->TemplateLoopVolumeMultiplier,
                                                      false));

    const FLoopRootSignature& TemplateLoopSignature = GetGlobalLoopSignature();

    mLoopInstances.Add(ELoopType::GOAL,
                       Settings->GoalLoopAsset
                           ->MakeGoalLoopInstance(TemplateLoopSignature,
                                                  Settings->GrabbableMaterialDataTable,
                                                  Settings->GoalLoopVolumeMultiplier, true));

    {
        FLoopInstance UserInstance = {
            .Signature = TemplateLoopSignature, .bIsMuted = false, .History = {}, .Data = {}
        };

        ULoopFunctionLibrary::InitializeEmptyLoopToTotalBeats(UserInstance);

        mLoopInstances.Add(ELoopType::USER, UserInstance);
    }

    mCurrentBeatInLoop = 0;

    K8_LOG(Log, "Loop instances successfully spawned.");
    return true;
}

bool UK8_WorldSubsystem::SpawnPlaybackActor(UWorld* World)
{
    if (!Settings->PlaybackActorClass)
    {
        K8_LOG(Error, "PlaybackActorClass must be set properly in settings. Aborting...");
        return false;
    }

    if (!mLoopPlaybackActor)
    {
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Params.ObjectFlags |= RF_Transient;

        mLoopPlaybackActor = World->SpawnActor<ALoopPlaybackActor>(Settings->PlaybackActorClass,
                                                                   FTransform::Identity, Params);

        if (!mLoopPlaybackActor)
        {
            K8_LOG(Error, "Failed to spawn LoopPlaybackActor. Audio will not play.");
            return false;
        }
    }

    K8_LOG(Log, "Playback actor successfully spawned.");
    return true;
}

void UK8_WorldSubsystem::HandleBeat()
{
    if (bLoopDataCacheDirty)
    {
        RebuildLoopDataCache();
    }

    if (!mLoopDataCache.Beats.IsValidIndex(mCurrentBeatInLoop))
    {
        return;
    }

    if (mCurrentBeatInLoop == 0)
    {
        OnLoopWrappedToStart.Broadcast();
    }

    const FLoopBeat& Beat = mLoopDataCache.Beats[mCurrentBeatInLoop];

    if (mLoopPlaybackActor && Beat.Items.Num() > 0)
    {
        mLoopPlaybackActor->PlayLoopItems(Beat.Items);
    }

    mCurrentBeatInLoop++;

    const int32 TotalBeats = GetGlobalLoopSignature().TotalBeatsPerLoop;

    if (mCurrentBeatInLoop >= TotalBeats)
    {
        mCurrentBeatInLoop = 0;
    }
}

void UK8_WorldSubsystem::RebuildLoopDataCache()
{
    const FLoopInstance& TemplateLoop = mLoopInstances.FindChecked(ELoopType::TEMPLATE);

    const int32 TotalBeats = TemplateLoop.Signature.TotalBeatsPerLoop;

    if (TotalBeats <= 0)
    {
        mLoopDataCache.Beats.Reset();
        bLoopDataCacheDirty = false;
        return;
    }

    mLoopDataCache.Beats.SetNum(TotalBeats);

    for (FLoopBeat& Beat : mLoopDataCache.Beats)
    {
        Beat.Items.Reset();
    }

    for (const TPair<ELoopType, FLoopInstance>& Pair : mLoopInstances)
    {
        const FLoopInstance& Loop = Pair.Value;

        if (Loop.bIsMuted)
        {
            continue;
        }

        for (int32 Beat = 0; Beat < TotalBeats; Beat++)
        {
            if (!Loop.Data.Beats.IsValidIndex(Beat))
            {
                continue;
            }

            mLoopDataCache.Beats[Beat].Items.Append(Loop.Data.Beats[Beat].Items);
        }
    }

    bLoopDataCacheDirty = false;
}
