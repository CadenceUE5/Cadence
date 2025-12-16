// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Cadence/Loop/LoopDataTypes.h"

#include "LoopPlaybackActor.generated.h"

UCLASS()
class CADENCE_API ALoopPlaybackActor : public AActor
{
    GENERATED_BODY()

public:
    ALoopPlaybackActor();

    void PlayOnce(const FLoopItem& LoopItem);

    void PlayLoopItems(const TArray<FLoopItem>& LoopItemsAtBeat);

private:
    UWorld* mWorld;
};
