// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"
#include "GrabbableDataLibrary.generated.h"

UENUM(BlueprintType)
enum class EGrabbableMaterial : uint8
{
    Metal UMETA(DisplayName = "Metal"),
    Wood UMETA(DisplayName = "Wood"),
    Plastic UMETA(DisplayName = "Plastic"),
    China UMETA(DisplayName = "China"),
    Stone UMETA(DisplayName = "Stone"),
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType) struct FGrabbableMaterialPair : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterial MaterialA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterial MaterialB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* Sound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color = FColor::White;
};

/**
 *
 */
UCLASS()
class CADENCE_API UGrabbableDataLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintPure, Category = "Grabbable Data")
    static FName MakeGrabbableMaterialPairRowName(EGrabbableMaterial A, EGrabbableMaterial B);
};
