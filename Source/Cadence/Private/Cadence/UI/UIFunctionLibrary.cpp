// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/UI/UIFunctionLibrary.h"

#include "Cadence/Loop/LoopDataTypes.h"

TMap<ELoopType, UWidgetListObject*> UUIFunctionLibrary::MakeLoopTypeToWidgetListObjectMap(
    UObject* Outer)
{
    check(Outer);

    TMap<ELoopType, UWidgetListObject*> Result;

    Result.Add(ELoopType::USER, NewObject<UWidgetListObject>(Outer));

    Result.Add(ELoopType::GOAL, NewObject<UWidgetListObject>(Outer));

    Result.Add(ELoopType::TEMPLATE, NewObject<UWidgetListObject>(Outer));

    return Result;
}

FMVVMViewModelContext UUIFunctionLibrary::MakeViewModelContext(
    TSubclassOf<UMVVMViewModelBase> ViewModelClass)
{
    return { .ContextClass = ViewModelClass, .ContextName = FName(GetNameSafe(ViewModelClass)) };
}
