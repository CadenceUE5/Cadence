// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopPlaybackListenerComponent.h"

ULoopPlaybackListenerComponent::ULoopPlaybackListenerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void ULoopPlaybackListenerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld())
    {
        return;
    }

    CachedSubsystem = GetWorld()->GetSubsystem<UK8_WorldSubsystem>();
    if (!CachedSubsystem)
    {
        return;
    }

    CachedSubsystem->OnPlaybackStarted
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandlePlaybackStarted);

    CachedSubsystem->OnPlaybackKilled
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandlePlaybackKilled);

    CachedSubsystem->OnLoopWrappedToStart
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandleLoopWrapped);

    CachedSubsystem->OnMuteLoopTypePlaybackSuccess
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandleMuteLoopTypePlaybackSuccess);

    CachedSubsystem->OnUnmuteLoopTypePlaybackSuccess
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandleUnmuteLoopTypePlaybackSuccess);

    CachedSubsystem->OnUserLoopAdd.AddDynamic(this,
                                              &ULoopPlaybackListenerComponent::HandleUserLoopAdd);

    CachedSubsystem->OnUserLoopUndo.AddDynamic(this,
                                               &ULoopPlaybackListenerComponent::HandleUserLoopUndo);

    CachedSubsystem->OnUserLoopCleared
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandleUserLoopCleared);

    CachedSubsystem->OnUserToGoalSimilarityScoreComputed
        .AddDynamic(this, &ULoopPlaybackListenerComponent::HandleSimilarityScore);
}

void ULoopPlaybackListenerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (CachedSubsystem)
    {
        CachedSubsystem->OnPlaybackStarted.RemoveAll(this);
        CachedSubsystem->OnPlaybackKilled.RemoveAll(this);
        CachedSubsystem->OnLoopWrappedToStart.RemoveAll(this);
        CachedSubsystem->OnMuteLoopTypePlaybackSuccess.RemoveAll(this);
        CachedSubsystem->OnUnmuteLoopTypePlaybackSuccess.RemoveAll(this);
        CachedSubsystem->OnUserLoopAdd.RemoveAll(this);
        CachedSubsystem->OnUserLoopUndo.RemoveAll(this);
        CachedSubsystem->OnUserLoopCleared.RemoveAll(this);
        CachedSubsystem->OnUserToGoalSimilarityScoreComputed.RemoveAll(this);
    }

    Super::EndPlay(EndPlayReason);
}

void ULoopPlaybackListenerComponent::HandlePlaybackStarted(FLoopRootSignature Signature)
{
    OnPlaybackStarted.Broadcast(Signature);
}

void ULoopPlaybackListenerComponent::HandlePlaybackKilled()
{
    OnPlaybackKilled.Broadcast();
}

void ULoopPlaybackListenerComponent::HandleLoopWrapped()
{
    OnLoopWrappedToStart.Broadcast();
}

void ULoopPlaybackListenerComponent::HandleMuteLoopTypePlaybackSuccess(ELoopType MutedLoopType)
{
    OnMuteLoopTypePlaybackSuccess.Broadcast(MutedLoopType);
}

void ULoopPlaybackListenerComponent::HandleUnmuteLoopTypePlaybackSuccess(ELoopType UnmutedLoopType)
{
    OnUnmuteLoopTypePlaybackSuccess.Broadcast(UnmutedLoopType);
}

void ULoopPlaybackListenerComponent::HandleUserLoopAdd(FLoopItemPayload Payload)
{
    OnUserLoopAdd.Broadcast(Payload);
}

void ULoopPlaybackListenerComponent::HandleUserLoopUndo(FLoopItemPayload Payload)
{
    OnUserLoopUndo.Broadcast(Payload);
}

void ULoopPlaybackListenerComponent::HandleUserLoopCleared()
{
    OnUserLoopCleared.Broadcast();
}

void ULoopPlaybackListenerComponent::HandleSimilarityScore(float Score)
{
    OnSimilarityScoreComputed.Broadcast(Score);
}
