#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"

#include "GrabbableMaterialLibrary.generated.h"

UENUM(BlueprintType)
enum class EGrabbableMaterial : uint8
{
    Metal UMETA(DisplayName = "Metal"),
    Wood UMETA(DisplayName = "Wood"),
    Plastic UMETA(DisplayName = "Plastic"),
    China UMETA(DisplayName = "China"),
    Stone UMETA(DisplayName = "Stone"),
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FGrabbableMaterialPair : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterial MaterialA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrabbableMaterial MaterialB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* Sound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color = FColor::White;
};

UCLASS()
class UGrabbableMaterialLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Grabbable Material")
    static FName MakeGrabbableMaterialPairRowName(EGrabbableMaterial A, EGrabbableMaterial B)
    {
        const uint8 Min = FMath::Min((uint8)A, (uint8)B);
        const uint8 Max = FMath::Max((uint8)A, (uint8)B);

        const UEnum* Enum = StaticEnum<EGrabbableMaterial>();
        check(Enum);

        const FString NameA = Enum->GetNameStringByValue(Min).ToLower();
        const FString NameB = Enum->GetNameStringByValue(Max).ToLower();

        return FName(*FString::Printf(TEXT("%s_%s"), *NameA, *NameB));
    }
};
