// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopSoundDataAsset.h"

void ULoopSoundDataAssetBase::InitializeSoundItemsPerBeat()
{
    mLoopData.gLoopSounds.SetNum(mLoopData.mTotalBeatsPerLoop);
}

int32 ULoopSoundDataAssetBase::AddSoundItemAtNearestBeatFromContext(
    const float TimeInLoop, const FGrabbableMaterialPair& SoundItemContext)
{
    return INDEX_NONE;
}

int32 ULoopSoundDataAssetBase::RoundTimeInLoopToNearestBeat(const float TimeInLoop)
{
    const int32 Beat = FMath::RoundToInt(TimeInLoop / mLoopData.mBeatDuration);

    return FMath::Clamp(Beat, 0, mLoopData.mTotalBeatsPerLoop - 1);
}

bool ULoopSoundDataAssetBase::RemoveLastAddedSoundItem()
{
    if (!mLoopData.gLoopSounds.IsValidIndex(mBeatOfLastAddedSoundItem))
    {
        return false;
    }

    TArray<FLoopSoundItem>& Items = mLoopData.gLoopSounds[mBeatOfLastAddedSoundItem].SoundItems;

    if (Items.Num() == 0)
    {
        return false;
    }

    Items.Pop();
    mBeatOfLastAddedSoundItem = INDEX_NONE;
    return true;
}

void ULoopSoundDataAssetBase::ClearAllLoopSounds()
{
    for (FLoopSoundItemArray& Beat : mLoopData.gLoopSounds)
    {
        Beat.SoundItems.Reset();
    }

    mBeatOfLastAddedSoundItem = INDEX_NONE;
}

void UTemplateLoopSoundPrimaryDataAsset::ComputeLoopDuration()
{
    float MaxEndTime = 0.f;

    for (int32 Beat = 0; Beat < mLoopData.gLoopSounds.Num(); Beat++)
    {
        const float BeatStartTime = Beat * mLoopData.mBeatDuration;

        for (const FLoopSoundItem& Item : mLoopData.gLoopSounds[Beat].SoundItems)
        {
            if (!Item.Sound)
            {
                continue;
            }

            const float EndTime = BeatStartTime + Item.Sound->GetDuration();

            MaxEndTime = FMath::Max(MaxEndTime, EndTime);
        }
    }

    mLoopData.mLoopDuration = MaxEndTime;

    ULoopSoundDataLibrary::ComputeLoopDescriptorVariables(this->mLoopData);
}

void UGoalLoopSoundPrimaryDataAsset::FindContextForLoopSounds() {}
