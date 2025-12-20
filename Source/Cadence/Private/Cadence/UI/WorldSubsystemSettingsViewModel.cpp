// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/UI/WorldSubsystemSettingsViewModel.h"

#include "Cadence/K8_UtilityCore.h"

bool UVM_WorldAesthetics::Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings)
{
    K8::Utility::GetAssetDataOfClass(UTemplateLoopPrimaryDataAsset::StaticClass(),
                                     TemplateLoopAssetData);

    K8::Utility::GetAssetDataOfClass(UGoalLoopPrimaryDataAsset::StaticClass(), GoalLoopAssetData);

    FSoftObjectPath DefaultTemplateAssetPath(Settings->TemplateLoopAsset);

    if (CurrentTemplateLoopIndex = K8::Utility::FindAssetIndexByObjectPath(TemplateLoopAssetData,
                                                                           DefaultTemplateAssetPath);
        CurrentTemplateLoopIndex == INDEX_NONE)
    {
        CurrentTemplateLoopIndex = 0;
    }

    const FSoftObjectPath DefaultGoalLoopAssetPath(Settings->GoalLoopAsset);

    if (CurrentGoalLoopIndex = K8::Utility::FindAssetIndexByObjectPath(GoalLoopAssetData,
                                                                       DefaultGoalLoopAssetPath);
        CurrentGoalLoopIndex == INDEX_NONE)
    {
        CurrentGoalLoopIndex = 0;
    }

    CurrentSettings = Settings;

    return SetTemplateLoopAssetFromCurrentIndex() && SetGoalLoopAssetFromCurrentIndex();
}

FText UVM_WorldAesthetics::GetTemplateLoopAssetName() const
{
    if (TemplateLoopAssetData.IsValidIndex(CurrentTemplateLoopIndex))
    {
        return FText::FromName(TemplateLoopAssetData[CurrentTemplateLoopIndex].AssetName);
    }

    return FText::GetEmpty();
}

void UVM_WorldAesthetics::SetTemplateLoopAssetName(const FText& NewValue)
{
    if (CurrentSettings)
    {
        const int32 NewIndex = K8::Utility::FindAssetIndexByDisplayText(TemplateLoopAssetData,
                                                                        NewValue);

        if (NewIndex == INDEX_NONE)
        {
            return;
        }

        const FText NewText = FText::FromName(TemplateLoopAssetData[NewIndex].AssetName);

        if (!UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopAssetName, NewText))
        {
            return;
        }

        CurrentTemplateLoopIndex = NewIndex;

        CurrentSettings->TemplateLoopAsset = Cast<UTemplateLoopPrimaryDataAsset>(
            TemplateLoopAssetData[CurrentTemplateLoopIndex].GetAsset());
    }
}

void UVM_WorldAesthetics::SetNextTemplateLoopAssetName()
{
    CurrentTemplateLoopIndex = (CurrentTemplateLoopIndex + 1) % TemplateLoopAssetData.Num();

    if (SetTemplateLoopAssetFromCurrentIndex() && CurrentSettings)
    {
        CurrentSettings->TemplateLoopAsset = Cast<UTemplateLoopPrimaryDataAsset>(
            TemplateLoopAssetData[CurrentTemplateLoopIndex].GetAsset());
    }
}

void UVM_WorldAesthetics::SetPreviousTemplateLoopAssetName()
{
    CurrentTemplateLoopIndex = (CurrentTemplateLoopIndex - 1 + TemplateLoopAssetData.Num())
                               % TemplateLoopAssetData.Num();

    if (SetTemplateLoopAssetFromCurrentIndex() && CurrentSettings)
    {
        CurrentSettings->TemplateLoopAsset = Cast<UTemplateLoopPrimaryDataAsset>(
            TemplateLoopAssetData[CurrentTemplateLoopIndex].GetAsset());
    }
}

FText UVM_WorldAesthetics::GetGoalLoopAssetName() const
{
    if (GoalLoopAssetData.IsValidIndex(CurrentGoalLoopIndex))
    {
        return FText::FromName(GoalLoopAssetData[CurrentGoalLoopIndex].AssetName);
    }

    return FText::GetEmpty();
}

void UVM_WorldAesthetics::SetGoalLoopAssetName(const FText& NewValue)
{
    if (CurrentSettings)
    {
        const int32 NewIndex = K8::Utility::FindAssetIndexByDisplayText(GoalLoopAssetData, NewValue);

        if (NewIndex == INDEX_NONE)
        {
            return;
        }

        const FText NewText = FText::FromName(GoalLoopAssetData[NewIndex].AssetName);

        if (!UE_MVVM_SET_PROPERTY_VALUE(GoalLoopAssetName, NewText))
        {
            return;
        }

        CurrentGoalLoopIndex = NewIndex;

        CurrentSettings->GoalLoopAsset = Cast<UGoalLoopPrimaryDataAsset>(
            GoalLoopAssetData[CurrentGoalLoopIndex].GetAsset());
    }
}

void UVM_WorldAesthetics::SetNextGoalLoopAssetName()
{
    CurrentGoalLoopIndex = (CurrentGoalLoopIndex + 1) % GoalLoopAssetData.Num();

    if (SetGoalLoopAssetFromCurrentIndex() && CurrentSettings)
    {
        CurrentSettings->GoalLoopAsset = Cast<UGoalLoopPrimaryDataAsset>(
            GoalLoopAssetData[CurrentGoalLoopIndex].GetAsset());
    }
}

void UVM_WorldAesthetics::SetPreviousGoalLoopAssetName()
{
    CurrentGoalLoopIndex = (CurrentGoalLoopIndex - 1 + GoalLoopAssetData.Num())
                           % GoalLoopAssetData.Num();

    if (SetGoalLoopAssetFromCurrentIndex() && CurrentSettings)
    {
        CurrentSettings->GoalLoopAsset = Cast<UGoalLoopPrimaryDataAsset>(
            GoalLoopAssetData[CurrentGoalLoopIndex].GetAsset());
    }
}

bool UVM_WorldAesthetics::SetTemplateLoopAssetFromCurrentIndex()
{
    if (TemplateLoopAssetData.IsValidIndex(CurrentTemplateLoopIndex))
    {
        return UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopAssetName,
                                          FText::FromName(
                                              TemplateLoopAssetData[CurrentTemplateLoopIndex]
                                                  .AssetName));
    }
    return false;
}

bool UVM_WorldAesthetics::SetGoalLoopAssetFromCurrentIndex()
{
    if (GoalLoopAssetData.IsValidIndex(CurrentGoalLoopIndex))
    {
        return UE_MVVM_SET_PROPERTY_VALUE(GoalLoopAssetName,
                                          FText::FromName(
                                              GoalLoopAssetData[CurrentGoalLoopIndex].AssetName));
    }
    return false;
}

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
