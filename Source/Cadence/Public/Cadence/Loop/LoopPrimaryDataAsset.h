// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Cadence/Loop/LoopDataTypes.h"

#include "LoopPrimaryDataAsset.generated.h"

UCLASS(Abstract)
class CADENCE_API ULoopPrimaryDataAssetBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLoopData LoopData;
};

UCLASS()
class CADENCE_API UTemplateLoopPrimaryDataAsset : public ULoopPrimaryDataAssetBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FLoopInstance MakeTemplateLoopInstance(int32 BeatsPerMinute, float VolumeMultiplier,
                                           bool IsMuted = false) const;
};

UCLASS()
class CADENCE_API UGoalLoopPrimaryDataAsset : public ULoopPrimaryDataAssetBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable const* mGrabbableMaterialDataTable;

    UFUNCTION(BlueprintCallable)
    FLoopInstance MakeGoalLoopInstance(const FLoopRootSignature Signature,
                                       UDataTable const* GrabbableMaterialDataTable,
                                       bool IsMuted = true) const;

    UFUNCTION(BlueprintCallable, CallInEditor)
    void FindColorForAssetLoopItems(UDataTable const* GrabbableMaterialDataTable = nullptr);
};
