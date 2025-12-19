// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "WorldSubsystemSettingsViewModel.generated.h"

UCLASS()
class CADENCE_API UVM_BeatsPerMinute : public UMVVMViewModelBase
{
    GENERATED_BODY()

    UFUNCTION(BlueprintPure)
    int32 GetBeatsPerMinute() const;

    UFUNCTION(BlueprintPure)
    void SetBeatsPerMinute(const int32& NewBPM);

private:
    UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
    int32 BeatsPerMinute;
};
