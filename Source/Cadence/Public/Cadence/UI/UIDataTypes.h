#pragma once

#include "CoreMinimal.h"

#include "UIDataTypes.generated.h"

UCLASS(BlueprintType, Category = "Cadence|UI")
class UWidgetListObject : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, meta = (ShowOnlyInnerProperties))
    TSet<UUserWidget*> Widgets;
};
