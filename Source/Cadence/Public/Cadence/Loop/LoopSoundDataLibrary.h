// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoopSoundDataLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLoopSoundItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* Sound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color = FColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier = 1.f;
};

USTRUCT(BlueprintType)
struct FLoopSoundItemArray
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLoopSoundItem> SoundItems;
};

USTRUCT(BlueprintType)
struct FLoopSoundData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 kBeatsPerMinute = 120;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float mBeatDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float mLoopDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 mTotalBeatsPerLoop = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLoopSoundItemArray> gLoopSounds;
};

UCLASS()
class CADENCE_API ULoopSoundDataLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void ComputeLoopDescriptorVariables(FLoopSoundData& Loop);

    UFUNCTION(BlueprintCallable)
    static float ComputeLoopSoundsSimilarityScore(const FLoopSoundData& A, const FLoopSoundData& B);

    UFUNCTION(BlueprintCallable)
    static int32 RoundTimeInLoopToNearestBeat(const FLoopSoundData& Loop, float TimeInLoop);
};
