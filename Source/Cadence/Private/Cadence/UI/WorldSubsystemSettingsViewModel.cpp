// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/UI/WorldSubsystemSettingsViewModel.h"

#include "Cadence/K8_GameInstanceBase.h"
#include "Cadence/K8_UtilityCore.h"

bool UVM_GameplayCustomization::Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings)
{
    bool Success = true;
    Success &= UE_MVVM_SET_PROPERTY_VALUE(BeatsPerMinute,
                                          static_cast<float>(Settings->BeatsPerMinute));
    Success &= UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopVolumeMultiplier,
                                          Settings->TemplateLoopVolumeMultiplier);
    Success &= UE_MVVM_SET_PROPERTY_VALUE(GoalLoopVolumeMultiplier,
                                          Settings->GoalLoopVolumeMultiplier);
    Success &= UE_MVVM_SET_PROPERTY_VALUE(GrabbableHitImpulseVolumeNormalization,
                                          Settings->GrabbableHitImpulseVolumeNormalization);
    Success &= UE_MVVM_SET_PROPERTY_VALUE(GrabbableHitDetectionFrequency,
                                          Settings->GrabbableHitDetectionFrequency);
    Success &= UE_MVVM_SET_PROPERTY_VALUE(GrabbableOutlineLineWidth,
                                          Settings->GrabbableOutlineLineWidth);

    if (!Success)
    {
        K8_LOG(Error, "Unable to set property values.");
        return Success;
    }

    CurrentSettings = Settings;
    return Success;
}

float UVM_GameplayCustomization::GetBeatsPerMinute() const
{
    return BeatsPerMinute;
}

void UVM_GameplayCustomization::SetBeatsPerMinute(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(BeatsPerMinute, NewValue))
        {
            CurrentSettings->BeatsPerMinute = NewValue;
        }
    }
}

float UVM_GameplayCustomization::GetTemplateLoopVolumeMultiplier() const
{
    return TemplateLoopVolumeMultiplier;
}

void UVM_GameplayCustomization::SetTemplateLoopVolumeMultiplier(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopVolumeMultiplier, NewValue))
        {
            CurrentSettings->TemplateLoopVolumeMultiplier = NewValue;
        }
    }
}

float UVM_GameplayCustomization::GetGoalLoopVolumeMultiplier() const
{
    return GoalLoopVolumeMultiplier;
}

void UVM_GameplayCustomization::SetGoalLoopVolumeMultiplier(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(GoalLoopVolumeMultiplier, NewValue))
        {
            CurrentSettings->GoalLoopVolumeMultiplier = NewValue;
        }
    }
}

float UVM_GameplayCustomization::GetGrabbableHitImpulseVolumeNormalization() const
{
    return GrabbableHitImpulseVolumeNormalization;
}

void UVM_GameplayCustomization::SetGrabbableHitImpulseVolumeNormalization(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(GrabbableHitImpulseVolumeNormalization, NewValue))
        {
            CurrentSettings->GrabbableHitImpulseVolumeNormalization = NewValue;
        }
    }
}

float UVM_GameplayCustomization::GetGrabbableHitDetectionFrequency() const
{
    return GrabbableHitDetectionFrequency;
}

void UVM_GameplayCustomization::SetGrabbableHitDetectionFrequency(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(GrabbableHitDetectionFrequency, NewValue))
        {
            CurrentSettings->GrabbableHitDetectionFrequency = NewValue;
        }
    }
}

float UVM_GameplayCustomization::GetGrabbableOutlineLineWidth() const
{
    return GrabbableOutlineLineWidth;
}

void UVM_GameplayCustomization::SetGrabbableOutlineLineWidth(const float& NewValue)
{
    if (CurrentSettings)
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(GrabbableOutlineLineWidth, NewValue))
        {
            CurrentSettings->GrabbableOutlineLineWidth = NewValue;
        }
    }
}
