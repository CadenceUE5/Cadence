// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/UI/WorldSubsystemSettingsViewModel.h"

#include "Cadence/K8_GameInstanceBase.h"
#include "Cadence/K8_UtilityCore.h"

bool UVM_TemplateLoopAsset::Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings)
{
    if (!Settings)
    {
        K8_LOG(Error, "Initialization failed, invalid settings.");
        return false;
    }
    if (UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopAsset, Settings->TemplateLoopAsset))
    {
        K8_LOG(Error, "Unable to set property value.");
        return false;
    };

    bInitialized = true;
    return true;
}

UTemplateLoopPrimaryDataAsset* UVM_TemplateLoopAsset::GetTemplateLoopAsset() const
{
    if (!bInitialized)
    {
        K8_LOG(Error, "Getter called without initialization");
        return nullptr;
    }
    return TemplateLoopAsset;
}

void UVM_TemplateLoopAsset::SetTemplateLoopAsset(UTemplateLoopPrimaryDataAsset*& NewValue)
{
    if (!bInitialized)
    {
        K8_LOG(Error, "Setter called without initialization");
        return;
    }
    if (UK8_WorldSubsystemSettingsDataAsset* Settings
        = UK8_GameInstanceBase::GetCurrentWorldSettingsStatic(this))
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(TemplateLoopAsset, NewValue))
        {
            Settings->TemplateLoopAsset = NewValue;
        }
    }
}

bool UVM_BeatsPerMinute::Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings)
{
    if (!Settings)
    {
        K8_LOG(Error, "Initialization failed, invalid settings.");
        return false;
    }
    if (!UE_MVVM_SET_PROPERTY_VALUE(BeatsPerMinute, Settings->BeatsPerMinute))
    {
        K8_LOG(Error, "Unable to set property value.");
        return false;
    };

    bInitialized = true;
    return true;
}

int32 UVM_BeatsPerMinute::GetBeatsPerMinute() const
{
    if (!bInitialized)
    {
        K8_LOG(Error, "Getter called without initialization");
        return INDEX_NONE;
    }

    return BeatsPerMinute;
}

void UVM_BeatsPerMinute::SetBeatsPerMinute(const int32& NewBPM)
{
    if (!bInitialized)
    {
        K8_LOG(Error, "Setter called without initialization");
        return;
    }

    if (UK8_WorldSubsystemSettingsDataAsset* Settings
        = UK8_GameInstanceBase::GetCurrentWorldSettingsStatic(this))
    {
        if (UE_MVVM_SET_PROPERTY_VALUE(BeatsPerMinute, NewBPM))
        {
            Settings->BeatsPerMinute = NewBPM;
        }
    }
}
