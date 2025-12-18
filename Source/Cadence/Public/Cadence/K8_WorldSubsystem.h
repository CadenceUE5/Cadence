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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUserGoalLoopPlaybackToggled, ELoopType, NewLoopType,
                                             ELoopType, OldLoopType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLoopAdd, FLoopItemPayload, Payload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLoopUndo, FLoopItemPayload, Payload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserLoopCleared);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserToGoalSimilarityScoreComputed, float, Score);

UCLASS(BlueprintType)
class CADENCE_API UK8_WorldSubsystemSettings : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "World Aesthetics")
    UTemplateLoopPrimaryDataAsset* TemplateLoopAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "World Aesthetics")
    UGoalLoopPrimaryDataAsset* GoalLoopAsset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization")
    int32 BeatsPerMinute = 180;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization")
    float TemplateLoopVolumeMultiplier = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization")
    float GoalLoopVolumeMultiplier = 0.8f;

    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization",
        meta
        = (ToolTip
           = "Impulse magnitude from grabbable collision required to reach full volume. Lower values make added loop items louder; higher values make them quieter."))
    float GrabbableHitImpulseVolumeNormalization = 1000.f;

    UPROPERTY(
        EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization",
        meta = (ToolTip = "Minimum time (in seconds) between successive grabbable hit detections."))
    float GrabbableHitDetectionFrequency = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Customization")
    float GrabbableOutlineLineWidth = 0.75f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Object Classes")
    TSubclassOf<ALoopPlaybackActor> PlaybackActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Object Classes")
    UDataTable* GrabbableMaterialDataTable;
};

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Cadence Settings"))
class CADENCE_API UK8_WorldSubsystemDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UK8_WorldSubsystemSettings> DeveloperSettings;
};

UCLASS(Config = Game)
class CADENCE_API UK8_WorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UK8_WorldSubsystemSettings* Settings;

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
    FLoopItemPayload AddItemToUserLoop(const FLoopItem& Item);

    UFUNCTION(BlueprintCallable)
    FLoopItemPayload UndoLastItemInUserLoop();

    UFUNCTION(BlueprintCallable)
    void ClearUserLoop();

    UFUNCTION(BlueprintCallable)
    bool ToggleUserGoalLoopPlayback();

    UFUNCTION(BlueprintCallable)
    float ComputeUserToGoalSimilarityScore();

    UFUNCTION(BlueprintPure)
    float GetGlobalLoopDuration() const;

    UFUNCTION(BlueprintPure)
    float GetGlobalBeatDuration() const;

    UFUNCTION(BlueprintPure)
    bool IsMuted(ELoopType type) const;

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
    FOnUserGoalLoopPlaybackToggled OnUserGoalLoopPlaybackToggled;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopAdd OnUserLoopAdd;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopUndo OnUserLoopUndo;

    UPROPERTY(BlueprintAssignable)
    FOnUserLoopCleared OnUserLoopCleared;

    UPROPERTY(BlueprintAssignable)
    FOnUserToGoalSimilarityScoreComputed OnUserToGoalSimilarityScoreComputed;
};
