// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "Cadence/K8_DeveloperSettings.h"

#include "WorldSubsystemSettingsViewModel.generated.h"

UCLASS()
class CADENCE_API UVM_WorldAesthetics : public UMVVMViewModelBase
{
    GENERATED_BODY()

public:
    bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings);

    UFUNCTION(BlueprintPure)
    FText GetTemplateLoopAssetName() const;

    UFUNCTION(BlueprintCallable)
    void SetTemplateLoopAssetName(const FText& NewValue);

    UFUNCTION(BlueprintCallable)
    void SetNextTemplateLoopAssetName();

    UFUNCTION(BlueprintCallable)
    void SetPreviousTemplateLoopAssetName();

    UFUNCTION(BlueprintPure)
    FText GetGoalLoopAssetName() const;

    UFUNCTION(BlueprintCallable)
    void SetGoalLoopAssetName(const FText& NewValue);

    UFUNCTION(BlueprintCallable)
    void SetNextGoalLoopAssetName();

    UFUNCTION(BlueprintCallable)
    void SetPreviousGoalLoopAssetName();

private:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    FText TemplateLoopAssetName;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    FText GoalLoopAssetName;

    UK8_WorldSubsystemSettingsDataAsset* CurrentSettings;

    int32 CurrentTemplateLoopIndex;
    TArray<FAssetData> TemplateLoopAssetData;

    int32 CurrentGoalLoopIndex;
    TArray<FAssetData> GoalLoopAssetData;

    bool SetTemplateLoopAssetFromCurrentIndex();
    bool SetGoalLoopAssetFromCurrentIndex();
};

UCLASS()
class CADENCE_API UVM_GameplayCustomization : public UMVVMViewModelBase
{
    GENERATED_BODY()

public:
    bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings);

    UFUNCTION(BlueprintPure)
    float GetBeatsPerMinute() const;

    UFUNCTION(BlueprintCallable)
    void SetBeatsPerMinute(const float& NewValue);

    UFUNCTION(BlueprintPure)
    float GetTemplateLoopVolumeMultiplier() const;

    UFUNCTION(BlueprintCallable)
    void SetTemplateLoopVolumeMultiplier(const float& NewValue);

    UFUNCTION(BlueprintPure)
    float GetGoalLoopVolumeMultiplier() const;

    UFUNCTION(BlueprintCallable)
    void SetGoalLoopVolumeMultiplier(const float& NewValue);

    UFUNCTION(BlueprintPure)
    float GetGrabbableHitImpulseVolumeNormalization() const;

    UFUNCTION(BlueprintCallable)
    void SetGrabbableHitImpulseVolumeNormalization(const float& NewValue);

    UFUNCTION(BlueprintPure)
    float GetGrabbableHitDetectionFrequency() const;

    UFUNCTION(BlueprintCallable)
    void SetGrabbableHitDetectionFrequency(const float& NewValue);

    UFUNCTION(BlueprintPure)
    float GetGrabbableOutlineLineWidth() const;

    UFUNCTION(BlueprintCallable)
    void SetGrabbableOutlineLineWidth(const float& NewValue);

private:
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float BeatsPerMinute = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float TemplateLoopVolumeMultiplier = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float GoalLoopVolumeMultiplier = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float GrabbableHitImpulseVolumeNormalization = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float GrabbableHitDetectionFrequency = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
    float GrabbableOutlineLineWidth = -1.f;

    UK8_WorldSubsystemSettingsDataAsset* CurrentSettings;
};
