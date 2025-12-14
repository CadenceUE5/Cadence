// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundIDBank.h"
#include "CollisionSoundLibrary.generated.h"

UENUM(BlueprintType)
enum class ECollisionMaterial : uint8
{
    Metal UMETA(DisplayName = "Metal"),
    Wood UMETA(DisplayName = "Wood"),
    Plastic UMETA(DisplayName = "Plastic"),
    China UMETA(DisplayName = "China"),
    Stone UMETA(DisplayName = "Stone"),
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FCollisionMaterialSoundRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECollisionMaterial Material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<ECollisionMaterial, USoundBase*> Sounds;
};

/**
 *
 */
UCLASS()
class CADENCE_API UCollisionSoundLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Collision Sounds")
    static void LoadCollisionSounds(USoundIDBank* Bank);

    UFUNCTION(BlueprintCallable, Category = "Collision Sounds")
    static USoundBase* GetCollisionSound(ECollisionMaterial MaterialA, ECollisionMaterial MaterialB,
                                         float Velocity);
};
