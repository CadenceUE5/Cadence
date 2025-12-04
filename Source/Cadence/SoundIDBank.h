// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "SoundIDBank.generated.h"

USTRUCT(BlueprintType)
struct FSoundIDEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString SoundID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundBase* Sound;
};

UCLASS(BlueprintType)
class CADENCE_API USoundIDBank : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FSoundIDEntry> Sounds;
};
