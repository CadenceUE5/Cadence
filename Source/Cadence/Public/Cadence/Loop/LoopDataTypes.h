// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "Cadence/K8_UtilityCore.h"

#include "LoopDataTypes.generated.h"

UENUM(BlueprintType, Category = "Cadence|Loop")
enum class ELoopType : uint8
{
    USER UMETA(DisplayName = "User"),
    GOAL UMETA(DisplayName = "Goal"),
    TEMPLATE UMETA(DisplayName = "Template"),
    _MAX UMETA(Hidden)
};

UENUM(BlueprintType, Category = "Cadence|Loop")
enum class ELoopItemPlaybackMode : uint8
{
    FLAT,
    SPATIAL
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopItem
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FString DisplayString;  // for pure QOL purposes

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* Sound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color = FColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector WorldPosition = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELoopItemPlaybackMode PlaybackMode = ELoopItemPlaybackMode::SPATIAL;

    /* The row name of the GrabbableMaterialPair that generated this FLoopItem */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InstigatorName;

    /**
     * @brief Necessary for Similarity Score calculation.
     * @param Other
     * @return
     */
    bool operator<(const FLoopItem& Other) const
    {
        return InstigatorName.LexicalLess(Other.InstigatorName);
    }

    void UpdateDisplayString()
    {
        DisplayString = Sound ? Sound->GetName() : TEXT("<UNSET>");
    }
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopItemPayload
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BeatInLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 OrderInBeat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLoopItem Item;
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopBeat
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FString DisplayString;  // for pure QOL purposes

    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              meta = (TitleProperty = "DisplayString", ShowOnlyInnerProperties))
    TArray<FLoopItem> Items;

    void UpdateDisplayString(int32 BeatIndex)
    {
        if (Items.IsEmpty())
        {
            DisplayString = "";
            return;
        }
        TArray<FString> ItemNames;
        ItemNames.Reserve(Items.Num());

        for (const FLoopItem& Item : Items)
        {
            ItemNames.Add(Item.DisplayString);
        }

        DisplayString = FString::Printf(TEXT("Beat %d (%d items): %s"), BeatIndex, Items.Num(),
                                        *FString::Join(ItemNames, TEXT(", ")));
    }
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopRootSignature
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    int32 BeatsPerMinute = 120;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float LoopDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float BeatDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 TotalBeatsPerLoop = 0;
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite,
              meta = (TitleProperty = "DisplayString", ShowOnlyInnerProperties))
    TArray<FLoopBeat> Beats;
};

USTRUCT(BlueprintType, Category = "Cadence|Loop")
struct FLoopInstance
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLoopRootSignature Signature;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsMuted = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ShowOnlyInnerProperties))
    TArray<FIntPoint> History;  // X = BeatInLoop, Y = OrderInBeat

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLoopData Data;
};
