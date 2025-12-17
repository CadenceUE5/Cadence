// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "UObject/ObjectMacros.h"

#include "Cadence/Grabbable/GrabbablePrimaryDataAsset.h"

#include "GrabbableThumbnailRenderer.generated.h"

class FCanvas;
class FRenderTarget;

/**
 *
 */
UCLASS()
class CADENCEEDITOR_API UGrabbableThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
    GENERATED_BODY()

public:
    UGrabbableThumbnailRenderer(const FObjectInitializer& ObjectInitializer);

    virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height,
                      FRenderTarget* RenderTarget, FCanvas* Canvas,
                      bool bAdditionalViewFamily) override;

    virtual void BeginDestroy() override;

private:
    class FStaticMeshThumbnailScene* ThumbnailScene = nullptr;

    void DrawGrabbableMaterialType2D(FCanvas* Canvas, int32 X, int32 Y, uint32 Width, uint32 Height,
                                     const UGrabbablePrimaryDataAsset* DataAsset);
};
