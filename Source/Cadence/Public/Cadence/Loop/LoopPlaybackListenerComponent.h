// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Cadence/K8_UtilityCore.h"

#include "Cadence/K8_WorldSubsystem.h"
#include "LoopPlaybackListenerComponent.generated.h"

UCLASS(ClassGroup = (Cadence), meta = (BlueprintSpawnableComponent))
class CADENCE_API ULoopPlaybackListenerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULoopPlaybackListenerComponent();

    UPROPERTY(BlueprintReadOnly, Category = "Cadence")
    FLoopRootSignature CachedRootSignature;

    UPROPERTY(BlueprintAssignable)
    FOnPlaybackStarted OnPlaybackStarted;

    UPROPERTY(BlueprintAssignable)
    FOnPlaybackKilled OnPlaybackKilled;

    UPROPERTY(BlueprintAssignable)
    FOnLoopWrappedToStart OnLoopWrappedToStart;

    UPROPERTY(BlueprintAssignable)
    FOnMuteLoopTypePlaybackSuccess OnMuteLoopTypePlaybackSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnUnmuteLoopTypePlaybackSuccess OnUnmuteLoopTypePlaybackSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnUserGoalLoopPlaybackToggled OnUserGoalLoopPlaybackToggled;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopAdd OnUserLoopAdd;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopUndo OnUserLoopUndo;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopCleared OnUserLoopCleared;

    UPROPERTY(BlueprintAssignable)
    FOnUserToGoalSimilarityScoreComputed OnSimilarityScoreComputed;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UFUNCTION()
    void HandlePlaybackStarted(FLoopRootSignature Signature);

    UFUNCTION()
    void HandlePlaybackKilled();

    UFUNCTION()
    void HandleLoopWrapped();

    UFUNCTION()
    void HandleMuteLoopTypePlaybackSuccess(ELoopType MutedLoopType);

    UFUNCTION()
    void HandleUnmuteLoopTypePlaybackSuccess(ELoopType UnmutedLoopType);

    UFUNCTION()
    void HandleUserGoalLoopPlaybackToggled(ELoopType NewLoopType, ELoopType OldLoopType);

    UFUNCTION()
    void HandleUserLoopAdd(FLoopItemPayload Payload);

    UFUNCTION()
    void HandleUserLoopUndo(FLoopItemPayload Payload);

    UFUNCTION()
    void HandleUserLoopCleared();

    UFUNCTION()
    void HandleSimilarityScore(float Score);

    UK8_WorldSubsystem* CachedSubsystem = nullptr;
};
