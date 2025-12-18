// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Cadence/K8_UtilityCore.h"
#include "Cadence/Grabbable/GrabbableDataTypes.h"

#include "GrabbableFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class CADENCE_API UGrabbableFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Cadence|Statics|Grabbable")
    static FName MakeGrabbableMaterialPairRowName(EGrabbableMaterialType A,
                                                  EGrabbableMaterialType B);

    UFUNCTION(BlueprintPure, Category = "Cadence|Statics|Misc")
    static bool IsGuidGreaterThan(const FGuid A, const FGuid B);

    template<typename TEnum>
    UFUNCTION(BlueprintPure, Category = "Cadence|Statics|Misc")
    static FORCEINLINE FString GetEnumDisplayName(TEnum Value)
    {
        static_assert(TIsEnum<TEnum>::Value, "GetEnumDisplayName requires an enum type");

        const UEnum* Enum = StaticEnum<TEnum>();
        if (!Enum)
        {
            return TEXT("");
        }

        return Enum->GetDisplayNameTextByValue(static_cast<int64>(Value)).ToString();
    }
};
