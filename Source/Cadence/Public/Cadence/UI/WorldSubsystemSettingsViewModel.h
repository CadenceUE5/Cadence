// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "Cadence/K8_DeveloperSettings.h"

#include "WorldSubsystemSettingsViewModel.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UK8_ViewModelInterface : public UInterface
{
    GENERATED_BODY()
};

class IK8_ViewModelInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    virtual bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings) = 0;
};

UCLASS()
class CADENCE_API UVM_GameplayCustomization : public UMVVMViewModelBase,
                                              public IK8_ViewModelInterface
{
    GENERATED_BODY()

public:
    virtual bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings) override;

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
    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float BeatsPerMinute = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float TemplateLoopVolumeMultiplier = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float GoalLoopVolumeMultiplier = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float GrabbableHitImpulseVolumeNormalization = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float GrabbableHitDetectionFrequency = -1.f;

    UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    float GrabbableOutlineLineWidth = -1.f;

    UK8_WorldSubsystemSettingsDataAsset* CurrentSettings;
};
