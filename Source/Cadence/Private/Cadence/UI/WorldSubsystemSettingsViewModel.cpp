// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/UI/WorldSubsystemSettingsViewModel.h"

#include "Cadence/K8_DeveloperSettings.h"

int32 UVM_BeatsPerMinute::GetBeatsPerMinute() const
{
    if (const UWorld* World = GetWorld())
    {
        if (const UK8_WorldSubsystem* Subsystem = World->GetSubsystem<UK8_WorldSubsystem>())
        {
            check(Subsystem->Settings->BeatsPerMinute = BeatsPerMinute);
            return BeatsPerMinute;
        }
    }
    return INDEX_NONE;
}

void UVM_BeatsPerMinute::SetBeatsPerMinute(const int32& NewBPM)
{
    if (UWorld* World = GetWorld())
    {
        if (UK8_WorldSubsystem* Subsystem = World->GetSubsystem<UK8_WorldSubsystem>())
        {
            if (UE_MVVM_SET_PROPERTY_VALUE(BeatsPerMinute, NewBPM))
            {
                Subsystem->Settings->BeatsPerMinute = NewBPM;
            }
        }
    }
}
