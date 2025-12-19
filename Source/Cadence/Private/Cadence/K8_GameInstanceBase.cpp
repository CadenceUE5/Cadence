// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/K8_GameInstanceBase.h"

#include "MVVMGameSubsystem.h"

#include "Cadence/UI/WorldSubsystemSettingsViewModel.h"
#include "Cadence/UI/UIFunctionLibrary.h"

void UK8_GameInstanceBase::Init()
{
    UGameInstance::Init();

    bSubsystemsIntialized = true;

    CurrentWorldSettings = UK8_DeveloperSettings::GetDefaultWorldSubsystemSettings();

    PostSubsystemInit();
}

UK8_WorldSubsystemSettingsDataAsset* UK8_GameInstanceBase::GetCurrentWorldSettings_Implementation()
{
    return CurrentWorldSettings;
}

UK8_WorldSubsystemSettingsDataAsset* UK8_GameInstanceBase::GetCurrentWorldSettingsStatic(
    UObject const* Outer)
{
    UWorld* World = Outer->GetWorld();

    if (!World)
    {
        K8_LOG(Error, "While retrieving current world settings, found that world was not valid.");

        return nullptr;
    }

    UK8_GameInstanceBase* Game = Cast<UK8_GameInstanceBase>(World->GetGameInstance());

    if (!Game)
    {
        K8_LOG(
            Error,
            "While retrieving current world settings, found that Game Instance is not valid for Cadence.");
        return nullptr;
    }

    return Game->CurrentWorldSettings;
}

bool UK8_GameInstanceBase::ConstructAllViewModels()
{
    if (!bSubsystemsIntialized)
    {
        K8_LOG(Error, "Subsystems must be initialized before constructing view models.")
        return false;
    }

    UMVVMViewModelCollectionObject* GlobalViewModelCollection
        = GetWorld()->GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();

    if (!GlobalViewModelCollection)
    {
        K8_LOG(Error, "Unable to get view model collection from MVVM plugin.")
        return false;
    }

    UVM_BeatsPerMinute* VM_BeatsPerMinuteInstance = NewObject<UVM_BeatsPerMinute>();
    VM_BeatsPerMinuteInstance->Initialize(CurrentWorldSettings);

    GlobalViewModelCollection->AddViewModelInstance(UUIFunctionLibrary::MakeViewModelContext(
                                                        UVM_BeatsPerMinute::StaticClass()),
                                                    VM_BeatsPerMinuteInstance);

    return true;
}
