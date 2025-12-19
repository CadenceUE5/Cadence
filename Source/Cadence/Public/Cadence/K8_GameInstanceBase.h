// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Cadence/K8_DeveloperSettings.h"

#include "Cadence/K8_UtilityCore.h"

#include "K8_GameInstanceBase.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UK8_GameInstanceInterface : public UInterface
{
    GENERATED_BODY()
};

class IK8_GameInstanceInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UK8_WorldSubsystemSettingsDataAsset* GetCurrentWorldSettings();

    K8_GENERATED_FUNCTION_HEADER(GetCurrentWorldSettings,
                                 virtual UK8_WorldSubsystemSettingsDataAsset*, ());
};

/**
 *
 */
UCLASS()
class CADENCE_API UK8_GameInstanceBase : public UGameInstance, public IK8_GameInstanceInterface
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UK8_WorldSubsystemSettingsDataAsset* CurrentWorldSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bSubsystemsIntialized = false;

    virtual UK8_WorldSubsystemSettingsDataAsset* GetCurrentWorldSettings_Implementation() override;

    /**
     * @brief A C++ helper function as it is more intuitive than using the Unreal generated pathway.
     * @param Outer
     * @return
     */
    static UK8_WorldSubsystemSettingsDataAsset* GetCurrentWorldSettingsStatic(UObject const* Outer);

    UFUNCTION(BlueprintCallable)
    bool ConstructAllViewModels();

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void PostSubsystemInit();
};
