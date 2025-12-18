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
    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static void InitializeEmptyLoopToTotalBeats(FLoopInstance& Loop);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static void NormalizeLoopData(FLoopData& Data, float VolumeMultiplier);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static float ComputeLoopDuration(const FLoopData& Data, float BeatDuration);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static int32 RoundTimeInLoopToNearestBeat(const FLoopInstance& Loop, float TimeInLoop);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static FLoopItemPayload AddItemToLoopAtBeat(FLoopInstance& Loop, int32 BeatInLoop,
                                                const FLoopItem& Item);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
    static FLoopItemPayload RemoveLastAddedLoopItem(FLoopInstance& Loop);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|Loop")
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
    UFUNCTION(BlueprintPure, Category = "Cadence|Statics|Loop")
    static float ComputeLoopSimilarityScore(const FLoopInstance& A, const FLoopData& B);

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Cadence|Statics|Loop")
    static bool FindContextForLoopItems(FLoopData& Data,
                                        UDataTable const* GrabbableMaterialDataTable);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|UI")
    static TMap<ELoopType, UWidgetListObject*> MakeLoopTypeToWidgetListObjectMap(UObject* Outer);
};
