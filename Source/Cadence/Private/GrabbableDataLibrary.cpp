// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Grabbable/GrabbableDataLibrary.h"

FName UGrabbableDataLibrary::MakeGrabbableMaterialPairRowName(EGrabbableMaterial A,
                                                              EGrabbableMaterial B)
{
    const uint8 Min = FMath::Min((uint8)A, (uint8)B);
    const uint8 Max = FMath::Max((uint8)A, (uint8)B);

    const UEnum* Enum = StaticEnum<EGrabbableMaterial>();
    check(Enum);

    const FString NameA = Enum->GetNameStringByValue(Min).ToLower();
    const FString NameB = Enum->GetNameStringByValue(Max).ToLower();

    return FName(*FString::Printf(TEXT("%s_%s"), *NameA, *NameB));
}
