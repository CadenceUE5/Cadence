// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "Cadence/K8_WorldSubsystem.h"

#include "K8_DeveloperSettings.generated.h"

/**
 *
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Cadence Settings"))
class CADENCE_API UK8_DeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Config)
    TSoftObjectPtr<UK8_WorldSubsystemSettingsDataAsset> WorldSubsystemSettings;
};

UCLASS(BlueprintType)
class CADENCE_API UK8_WorldSubsystemSettingsDataAsset : public UDataAsset
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
