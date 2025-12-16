// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "LoopDataTypes.generated.h"

UENUM(BlueprintType)
enum class ELoopType : uint8
{
    USER UMETA(DisplayName = "User"),
    GOAL UMETA(DisplayName = "Goal"),
    TEMPLATE UMETA(DisplayName = "Template"),
    _MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ELoopItemPlaybackMode : uint8
{
    FLAT,
    SPATIAL
};

USTRUCT(BlueprintType)
struct FLoopItem
{
    GENERATED_BODY()

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
};

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
struct FLoopBeat
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLoopItem> Items;
};

USTRUCT(BlueprintType)
struct FLoopRootSignature
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 BeatsPerMinute = 120;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float LoopDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float BeatDuration = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 TotalBeatsPerLoop = 0;
};

USTRUCT(BlueprintType)
struct FLoopData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLoopBeat> Beats;
};

USTRUCT(BlueprintType)
struct FLoopInstance
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLoopRootSignature Signature;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsMuted = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FIntPoint> History;  // X = BeatInLoop, Y = OrderInBeat

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLoopData Data;
};

UCLASS(BlueprintType)
class UWidgetListObject : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    TSet<UUserWidget*> Widgets;
};
