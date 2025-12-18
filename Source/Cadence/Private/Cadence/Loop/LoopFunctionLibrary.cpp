// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopFunctionLibrary.h"

#include "Cadence/K8_UtilityCore.h"

#include "Cadence/Grabbable/GrabbableFunctionLibrary.h"

#include "Math/UnrealMathUtility.h"

void ULoopFunctionLibrary::InitializeEmptyLoopToTotalBeats(FLoopInstance& Loop)
{
    if (Loop.Signature.TotalBeatsPerLoop <= 0)
    {
        return;
    }

    Loop.Data.Beats.SetNum(Loop.Signature.TotalBeatsPerLoop);

    for (FLoopBeat& Beat : Loop.Data.Beats)
    {
        Beat.Items.Reset();
    }
}

void ULoopFunctionLibrary::NormalizeLoopData(FLoopData& Data, float VolumeMultiplier)
{
    for (FLoopBeat& Beat : Data.Beats)
    {
        for (FLoopItem& Item : Beat.Items)
        {
            Item.Color = FColor::Transparent;
            Item.VolumeMultiplier = VolumeMultiplier;
            Item.WorldPosition = FVector::ZeroVector;
            Item.PlaybackMode = ELoopItemPlaybackMode::FLAT;

            /*
             * If this method is being called we can assume there will be no need to
             * use .InstigatorName to compute Similarity Score, so DEADBEEF
             */
            Item.InstigatorName = TEXT("DEADBEEF");
        }
    }
}

float ULoopFunctionLibrary::ComputeLoopDuration(const FLoopData& Data, float BeatDuration)
{
    float MaxEndTime = 0.f;

    for (int32 BeatIndex = 0; BeatIndex < Data.Beats.Num(); ++BeatIndex)
    {
        const float BeatStartTime = BeatIndex * BeatDuration;

        const TArray<FLoopItem>& Items = Data.Beats[BeatIndex].Items;

        for (const FLoopItem& Item : Items)
        {
            if (!Item.Sound)
            {
                continue;
            }

            const float EndTime = BeatStartTime + Item.Sound->GetDuration();

            MaxEndTime = FMath::Max(MaxEndTime, EndTime);
        }
    }

    return FMath::Max(MaxEndTime, 0.f);
}

int32 ULoopFunctionLibrary::RoundTimeInLoopToNearestBeat(const FLoopInstance& Loop, float TimeInLoop)
{
    if (Loop.Signature.BeatDuration <= 0.f || Loop.Signature.TotalBeatsPerLoop <= 0)
    {
        return INDEX_NONE;
    }

    const float WrappedTime = FMath::Fmod(TimeInLoop, Loop.Signature.LoopDuration);

    const int32 Beat = FMath::RoundToInt(WrappedTime / Loop.Signature.BeatDuration);

    return FMath::Clamp(Beat, 0, Loop.Signature.TotalBeatsPerLoop - 1);
}

FLoopItemPayload ULoopFunctionLibrary::AddItemToLoopAtBeat(FLoopInstance& Loop, int32 BeatInLoop,
                                                           const FLoopItem& Item)
{
    if (!Loop.Data.Beats.IsValidIndex(BeatInLoop))
    {
        return { .BeatInLoop = INDEX_NONE, .OrderInBeat = INDEX_NONE, .Item = {} };
    }

    TArray<FLoopItem>& Items = Loop.Data.Beats[BeatInLoop].Items;

    const int32 OrderInBeat = Items.Num();
    Items.Add(Item);

    Loop.History.Add(FIntPoint(BeatInLoop, OrderInBeat));

    return { .BeatInLoop = BeatInLoop, .OrderInBeat = OrderInBeat, .Item = Item };
}

FLoopItemPayload ULoopFunctionLibrary::RemoveLastAddedLoopItem(FLoopInstance& Loop)
{
    if (Loop.History.Num() == 0)
    {
        return { .BeatInLoop = INDEX_NONE, .OrderInBeat = INDEX_NONE, .Item = {} };
    }

    const FIntPoint Last = Loop.History.Pop();
    const int32 BeatInLoop = Last.X;
    const int32 OrderInBeat = Last.Y;

    if (!Loop.Data.Beats.IsValidIndex(BeatInLoop))
    {
        return { .BeatInLoop = INDEX_NONE, .OrderInBeat = INDEX_NONE, .Item = {} };
    }

    TArray<FLoopItem>& Items = Loop.Data.Beats[BeatInLoop].Items;

    if (OrderInBeat != Items.Num() - 1)
    {
        K8_LOG(Warning, "Loop History does not follow LIFO invariant. Aborting...");
        return { .BeatInLoop = INDEX_NONE, .OrderInBeat = INDEX_NONE, .Item = {} };
    }

    const FLoopItem RemovedItem = Items.Pop();

    return { .BeatInLoop = BeatInLoop, .OrderInBeat = OrderInBeat, .Item = RemovedItem };
}

void ULoopFunctionLibrary::ClearAllLoopItems(FLoopInstance& Loop)
{
    for (FLoopBeat& Beat : Loop.Data.Beats)
    {
        Beat.Items.Reset();
    }

    Loop.History.Reset();
}

float ULoopFunctionLibrary::ComputeLoopSimilarityScore(const FLoopInstance& A, const FLoopData& B)
{
    const int32 TotalBeats = A.Data.Beats.Num();

    if (TotalBeats == 0 || B.Beats.Num() != TotalBeats)
    {
        return 0.f;
    }

    float AccumulatedScore = 0.f;
    int32 ScoredBeats = 0;

    for (int32 Beat = 0; Beat < TotalBeats; ++Beat)
    {
        const TArray<FLoopItem>& ItemsA = A.Data.Beats[Beat].Items;
        const TArray<FLoopItem>& ItemsB = B.Beats[Beat].Items;

        if (ItemsA.Num() == 0 && ItemsB.Num() == 0)
        {
            continue;
        }

        TArray<FLoopItem> SortedA = ItemsA;
        TArray<FLoopItem> SortedB = ItemsB;

        SortedA.Sort();
        SortedB.Sort();

        int32 Matches = 0;

        /* Compare sorted items using their overriden < operator and with pointer incrementation. */
        int32 i = 0, j = 0;
        while (i < SortedA.Num() && j < SortedB.Num())
        {
            if (SortedA[i].InstigatorName == SortedB[j].InstigatorName)
            {
                Matches++;
                i++;
                j++;
            }
            else if (SortedA[i] < SortedB[j])
            {
                i++;
            }
            else
            {
                j++;
            }
        }

        const int32 Denominator = FMath::Max(SortedA.Num(), SortedB.Num());
        const float ScoreForCurrentBeat = Denominator > 0 ? float(Matches) / float(Denominator)
                                                          : 0.f;

        AccumulatedScore += ScoreForCurrentBeat;
        ScoredBeats++;
    }

    return (ScoredBeats > 0) ? AccumulatedScore / float(ScoredBeats) : 0.f;
}

bool ULoopFunctionLibrary::FindContextForLoopItems(FLoopData& Data, float VolumeMultiplier,
                                                   UDataTable const* GrabbableMaterialDataTable)
{
    if (!GrabbableMaterialDataTable)
    {
        return false;
    }

    bool bAnyFound = false;

    const TMap<FName, uint8*>& RowMap = GrabbableMaterialDataTable->GetRowMap();

    for (FLoopBeat& Beat : Data.Beats)
    {
        for (FLoopItem& Item : Beat.Items)
        {
            if (!Item.Sound)
            {
                continue;
            }

            const FString ItemSoundPath = Item.Sound->GetPathName();

            for (const TPair<FName, uint8*>& Pair : RowMap)
            {
                const FGrabbableMaterialPair* Row
                    = GrabbableMaterialDataTable
                          ->FindRow<FGrabbableMaterialPair>(Pair.Key, TEXT(__FUNCTION__));

                if (!Row || !Row->Sound)
                {
                    continue;
                }

                if (Row->Sound->GetPathName() == ItemSoundPath)
                {
                    Item.InstigatorName = Pair.Key;
                    Item.Color = Row->Color;
                    Item.VolumeMultiplier = VolumeMultiplier;
                    bAnyFound = true;
                    break;
                }
            }
        }
    }

    return bAnyFound;
}

TMap<ELoopType, UWidgetListObject*> ULoopFunctionLibrary::MakeLoopTypeToWidgetListObjectMap(
    UObject* Outer)
{
    check(Outer);

    TMap<ELoopType, UWidgetListObject*> Result;

    Result.Add(ELoopType::USER, NewObject<UWidgetListObject>(Outer));

    Result.Add(ELoopType::GOAL, NewObject<UWidgetListObject>(Outer));

    Result.Add(ELoopType::TEMPLATE, NewObject<UWidgetListObject>(Outer));

    return Result;
}
