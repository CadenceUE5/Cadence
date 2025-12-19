// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/MVVMViewModelContext.h"
#include <MVVMViewModelBase.h>

#include "Cadence/UI/UIDataTypes.h"

#include "UIFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class CADENCE_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|UI")
    static TMap<ELoopType, UWidgetListObject*> MakeLoopTypeToWidgetListObjectMap(UObject* Outer);

    UFUNCTION(BlueprintCallable, Category = "Cadence|Statics|UI")
    static FMVVMViewModelContext MakeViewModelContext(TSubclassOf<UMVVMViewModelBase> ViewModelClass);
};
