// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Engine/DeveloperSettings.h"

#include "Cadence/Loop/LoopDataTypes.h"
#include "Cadence/Loop/LoopPrimaryDataAsset.h"
#include "Cadence/Loop/LoopPlaybackActor.h"

#include "K8_WorldSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlaybackStarted, FLoopRootSignature, Signature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlaybackKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoopWrappedToStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuteLoopTypePlaybackSuccess, ELoopType,
                                            MutedLoopType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnmuteLoopTypePlaybackSuccess, ELoopType,
                                            UnmutedLoopType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLoopAdd, FLoopItemPayload, Payload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLoopUndo, FLoopItemPayload, Payload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserLoopCleared);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserToGoalSimilarityScoreComputed, float, Score);

UCLASS(BlueprintType)
class CADENCE_API UK8WorldSubsystemSettings : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 BeatsPerMinute = 120;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TemplateLoopVolumeMultiplier = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ALoopPlaybackActor> PlaybackActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTemplateLoopPrimaryDataAsset* TemplateLoopAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UGoalLoopPrimaryDataAsset* GoalLoopAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UDataTable* GrabbableMaterialDataTable;
};

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Cadence Settings"))
class CADENCE_API UK8WorldSubsystemDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UK8WorldSubsystemSettings> DeveloperSettings;
};

UCLASS(Config = Game)
class CADENCE_API UK8_WorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    UK8WorldSubsystemSettings* Settings;

    virtual void OnWorldBeginPlay(UWorld& World) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable)
    void StartPlayback();

    UFUNCTION(BlueprintCallable)
    void KillPlayback();

    UFUNCTION(BlueprintCallable)
    bool MuteLoopTypePlayback(ELoopType type);

    UFUNCTION(BlueprintCallable)
    bool UnmuteLoopTypePlayback(ELoopType type);

    UFUNCTION(BlueprintCallable)
    int32 AddItemToUserLoop(const FLoopItem& Item);

    UFUNCTION(BlueprintCallable)
    FLoopItemPayload UndoLastItemInUserLoop();

    UFUNCTION(BlueprintCallable)
    void ClearUserLoop();

    UFUNCTION(BlueprintPure)
    float ComputeUserToGoalSimilarityScore() const;

    UFUNCTION(BlueprintPure)
    float GetGlobalLoopDuration() const;

    UFUNCTION(BlueprintPure)
    float GetGlobalBeatDuration() const;

    UFUNCTION(BlueprintPure)
    const FLoopRootSignature& GetGlobalLoopSignature() const;

    UFUNCTION(BlueprintPure)
    const FLoopData& GetLoopData(ELoopType type) const;

    UFUNCTION(BlueprintPure)
    const FLoopInstance& GetLoopInstance(ELoopType type) const;

private:
    TMap<ELoopType, FLoopInstance> mLoopInstances;

    ALoopPlaybackActor* mLoopPlaybackActor = nullptr;

    FLoopData mLoopDataCache;
    bool bLoopDataCacheDirty = true;

    int32 mCurrentBeatInLoop = 0;

    FTimerHandle mBeatTimerHandle;

    void InitializeLoopInstances();
    void LoadSettingsSynchronous();
    void SpawnPlaybackActor(UWorld& World);

    void HandleBeat();
    void RebuildLoopDataCache();

public:
    UPROPERTY(BlueprintAssignable) FOnPlaybackStarted OnPlaybackStarted;

    UPROPERTY(BlueprintAssignable)
    FOnPlaybackKilled OnPlaybackKilled;

    UPROPERTY(BlueprintAssignable)
    FOnLoopWrappedToStart OnLoopWrappedToStart;

    UPROPERTY(BlueprintAssignable)
    FOnMuteLoopTypePlaybackSuccess OnMuteLoopTypePlaybackSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnUnmuteLoopTypePlaybackSuccess OnUnmuteLoopTypePlaybackSuccess;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopAdd OnUserLoopAdd;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopUndo OnUserLoopUndo;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopCleared OnUserLoopCleared;

    UPROPERTY(BlueprintAssignable)
    FOnUserToGoalSimilarityScoreComputed OnUserToGoalSimilarityScoreComputed;
};
