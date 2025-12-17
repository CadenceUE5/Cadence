// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopPlaybackActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ALoopPlaybackActor::ALoopPlaybackActor()
{
    PrimaryActorTick.bCanEverTick = false;

    mWorld = GetWorld();
    if (!mWorld)
    {
        return;
    }
}

void ALoopPlaybackActor::PlayOnce(const FLoopItem& LoopItem)
{
    if (!mWorld)
    {
        return;
    }

    if (LoopItem.PlaybackMode == ELoopItemPlaybackMode::FLAT)
    {
        UGameplayStatics::PlaySound2D(mWorld, LoopItem.Sound, LoopItem.VolumeMultiplier);
    }
    else
    {
        UGameplayStatics::PlaySoundAtLocation(mWorld, LoopItem.Sound, LoopItem.WorldPosition,
                                              LoopItem.VolumeMultiplier);
    }
}

void ALoopPlaybackActor::PlayLoopItems(const TArray<FLoopItem>& LoopItemsAtBeat)
{
    if (!mWorld)
    {
        return;
    }

    for (const FLoopItem& Item : LoopItemsAtBeat)
    {
        if (!Item.Sound)
        {
            continue;
        }

        if (Item.PlaybackMode == ELoopItemPlaybackMode::FLAT)
        {
            UGameplayStatics::PlaySound2D(mWorld, Item.Sound, Item.VolumeMultiplier);
        }
        else
        {
            UGameplayStatics::PlaySoundAtLocation(mWorld, Item.Sound, Item.WorldPosition,
                                                  Item.VolumeMultiplier);
        }
    }
}
