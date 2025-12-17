// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Grabbable/GrabbableFunctionLibrary.h"

FName UGrabbableFunctionLibrary::MakeGrabbableMaterialPairRowName(EGrabbableMaterialType A,
                                                                  EGrabbableMaterialType B)
{
    const uint8 Min = FMath::Min((uint8)A, (uint8)B);
    const uint8 Max = FMath::Max((uint8)A, (uint8)B);

    const UEnum* Enum = StaticEnum<EGrabbableMaterialType>();
    check(Enum);

    const FString NameA = Enum->GetNameStringByValue(Min).ToLower();
    const FString NameB = Enum->GetNameStringByValue(Max).ToLower();

    return FName(*FString::Printf(TEXT("%s_%s"), *NameA, *NameB));
}

bool UGrabbableFunctionLibrary::IsGuidGreaterThan(const FGuid A, const FGuid B)
{
    return A < B;
}
