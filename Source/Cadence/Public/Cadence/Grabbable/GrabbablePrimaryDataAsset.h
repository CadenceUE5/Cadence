// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Cadence/K8_UtilityCore.h"
#include "Cadence/Grabbable/GrabbableDataTypes.h"

#include "GrabbablePrimaryDataAsset.generated.h"

/**
 *
 */
UCLASS(Abstract)
class CADENCE_API UGrabbablePrimaryDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMesh* Mesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EGrabbableMaterialType MaterialType = EGrabbableMaterialType::Metal;
};
