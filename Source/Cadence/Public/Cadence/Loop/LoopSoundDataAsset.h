// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Cadence/Loop/LoopSoundDataLibrary.h"
#include "Cadence/Grabbable/GrabbableDataLibrary.h"

#include "LoopSoundDataAsset.generated.h"

UCLASS(Abstract)
class CADENCE_API ULoopSoundPrimaryDataAssetBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLoopSoundData mLoopData;
};

UCLASS()
class CADENCE_API UTemplateLoopSoundPrimaryDataAsset : public ULoopSoundPrimaryDataAssetBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, CallInEditor)
    void ComputeLoopDuration();
};

UCLASS()
class CADENCE_API UGoalLoopSoundPrimaryDataAsset : public ULoopSoundPrimaryDataAssetBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, CallInEditor)
    void FindContextForLoopSounds();
};

UCLASS(Abstract)
class CADENCE_API ULoopSoundDataAssetBase : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLoopSoundData mLoopData;

    UFUNCTION(BlueprintCallable)
    void InitializeSoundItemsPerBeat();

    UFUNCTION(BlueprintCallable)
    int32 AddSoundItemAtNearestBeatFromContext(const float TimeInLoop,
                                               const FGrabbableMaterialPair& SoundItemContext);

    UFUNCTION(BlueprintCallable)
    bool RemoveLastAddedSoundItem();

    UFUNCTION(BlueprintCallable)
    void ClearAllLoopSounds();

protected:
    int32 RoundTimeInLoopToNearestBeat(const float TimeInLoop);

    int32 mBeatOfLastAddedSoundItem = INDEX_NONE;
};

UCLASS(BlueprintType)
class CADENCE_API UUserLoopSoundDataAssetBase : public ULoopSoundDataAssetBase
{
    GENERATED_BODY()
};
