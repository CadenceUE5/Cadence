#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"

#include "Cadence/K8_UtilityCore.h"

#include "GrabbableDataTypes.generated.h"

UENUM(BlueprintType, Category = "Cadence|Grabbable")
enum class EGrabbableMaterialType : uint8
{
    Metal UMETA(DisplayName = "Metal"),
    Wood UMETA(DisplayName = "Wood"),
    Plastic UMETA(DisplayName = "Plastic"),
    China UMETA(DisplayName = "China"),
    Stone UMETA(DisplayName = "Stone"),
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType, Category = "Cadence|Grabbable")
struct FGrabbableMaterialPair : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterialType MaterialA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterialType MaterialB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* Sound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color = FColor::White;
};
