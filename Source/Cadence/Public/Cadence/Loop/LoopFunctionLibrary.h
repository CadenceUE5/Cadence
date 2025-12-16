// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Cadence/Loop/LoopDataTypes.h"

#include "LoopFunctionLibrary.generated.h"

UCLASS()
class CADENCE_API ULoopFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static void InitializeEmptyLoopToTotalBeats(FLoopInstance& Loop);

    UFUNCTION(BlueprintCallable)
    static void NormalizeLoopData(FLoopData& Data, float VolumeMultiplier);

    UFUNCTION(BlueprintCallable)
    static float ComputeLoopDuration(const FLoopData& Data, float BeatDuration);

    UFUNCTION(BlueprintCallable)
    static int32 RoundTimeInLoopToNearestBeat(const FLoopInstance& Loop, float TimeInLoop);

    UFUNCTION(BlueprintCallable)
    static bool AddItemToLoopAtBeat(FLoopInstance& Loop, int32 BeatInLoop, const FLoopItem& Item);

    UFUNCTION(BlueprintCallable)
    static FLoopItemPayload RemoveLastAddedLoopItem(FLoopInstance& Loop);

    UFUNCTION(BlueprintCallable)
    static void ClearAllLoopItems(FLoopInstance& Loop);

    /**
     * @brief Per-beat, takes the intersection between the collection of sounds in the loop at that
     * beat. It divdes the number of discovered common sounds by the max(ACount, BCount), where each
     * denotes the number of sounds in the loop at that beat.
     *
     * Then, the overall score of the loop similarity is an average of all the scores calculated per
     * beat.
     *
     * @param A
     * @param B
     * @return
     */
    UFUNCTION(BlueprintPure)
    static float ComputeLoopSimilarityScore(const FLoopInstance& A, const FLoopData& B);

    UFUNCTION(BlueprintCallable, CallInEditor)
    static bool FindContextForLoopItems(FLoopData& Data,
                                        UDataTable const* GrabbableMaterialDataTable);

    UFUNCTION(BlueprintCallable)
    static TMap<ELoopType, UWidgetListObject*> MakeLoopTypeToWidgetListObjectMap(UObject* Outer);
};
