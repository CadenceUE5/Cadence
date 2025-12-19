// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "Cadence/K8_DeveloperSettings.h"
#include "Cadence/UI/ViewModelMacros.h"

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
class CADENCE_API UVM_TemplateLoopAsset : public UMVVMViewModelBase, public IK8_ViewModelInterface
{
    GENERATED_BODY()

public:
    virtual bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bInitialized = false;

    UFUNCTION(BlueprintPure)
    UTemplateLoopPrimaryDataAsset* GetTemplateLoopAsset() const;

    UFUNCTION(BlueprintPure)
    void SetTemplateLoopAsset(UTemplateLoopPrimaryDataAsset*& NewValue);

private:
    UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    UTemplateLoopPrimaryDataAsset* TemplateLoopAsset;
};

UCLASS()
class CADENCE_API UVM_BeatsPerMinute : public UMVVMViewModelBase, public IK8_ViewModelInterface
{
    GENERATED_BODY()

public:
    virtual bool Initialize(UK8_WorldSubsystemSettingsDataAsset* Settings) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bInitialized = false;

    UFUNCTION(BlueprintPure)
    int32 GetBeatsPerMinute() const;

    UFUNCTION(BlueprintPure)
    void SetBeatsPerMinute(const int32& NewBPM);

private:
    UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    int32 BeatsPerMinute = INDEX_NONE;
};
