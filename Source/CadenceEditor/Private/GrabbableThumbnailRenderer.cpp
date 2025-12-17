// Fill out your copyright notice in the Description page of Project Settings.

#include "CadenceEditor/Grabbable/GrabbableThumbnailRenderer.h"

#include "ShowFlags.h"
#include "SceneInterface.h"
#include "SceneView.h"
#include "ThumbnailHelpers.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Engine/Font.h"
#include "Engine/Engine.h"

#include "Cadence/Grabbable/GrabbableFunctionLibrary.h"

UGrabbableThumbnailRenderer::UGrabbableThumbnailRenderer(const FObjectInitializer& ObjectInitializer)
    : UDefaultSizedThumbnailRenderer(ObjectInitializer)
{
    ThumbnailScene = nullptr;
}

void UGrabbableThumbnailRenderer::Draw(UObject* Object, int32 X, int32 Y, uint32 Width,
                                       uint32 Height, FRenderTarget* RenderTarget, FCanvas* Canvas,
                                       bool bAdditionalViewFamily)
{
    const UGrabbablePrimaryDataAsset* DataAsset = Cast<UGrabbablePrimaryDataAsset>(Object);

    if (!DataAsset || !DataAsset->Mesh)
    {
        return;
    }

    if (ThumbnailScene == nullptr || ensure(ThumbnailScene->GetWorld() != nullptr) == false)
    {
        if (ThumbnailScene)
        {
            FlushRenderingCommands();
            delete ThumbnailScene;
        }
        ThumbnailScene = new FStaticMeshThumbnailScene();
    }

    ThumbnailScene->SetStaticMesh(DataAsset->Mesh);
    ThumbnailScene->GetScene()->UpdateSpeedTreeWind(0.0);

    FSceneViewFamilyContext ViewFamily(
        FSceneViewFamily::ConstructionValues(RenderTarget, ThumbnailScene->GetScene(),
                                             FEngineShowFlags(ESFIM_Game))
            .SetTime(UThumbnailRenderer::GetTime())
            .SetAdditionalViewFamily(bAdditionalViewFamily));

    ViewFamily.EngineShowFlags.DisableAdvancedFeatures();
    ViewFamily.EngineShowFlags.MotionBlur = 0;
    ViewFamily.EngineShowFlags.LOD = 0;

    RenderViewFamily(Canvas, &ViewFamily,
                     ThumbnailScene->CreateView(&ViewFamily, X, Y, Width, Height));

    DrawGrabbableMaterialType2D(Canvas, X, Y, Width, Height, DataAsset);

    ThumbnailScene->SetStaticMesh(nullptr);
}

void UGrabbableThumbnailRenderer::DrawGrabbableMaterialType2D(
    FCanvas* Canvas, int32 X, int32 Y, uint32 Width, uint32 Height,
    const UGrabbablePrimaryDataAsset* DataAsset)
{
    const FString Label = UGrabbableFunctionLibrary::GetEnumDisplayName<EGrabbableMaterialType>(
        DataAsset->MaterialType);

    if (!Label.IsEmpty() && Canvas)
    {
        UFont* Font = GEngine->GetSubtitleFont();

        FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::FromString(Label), Font,
                                 FLinearColor::White);

        const float Scale = FMath::Clamp(Width / 128.0f, 1.5f, 3.5f);
        TextItem.Scale = FVector2D(Scale, Scale);

        TextItem.bCentreX = true;
        TextItem.bCentreY = true;
        TextItem.EnableShadow(FLinearColor::Black);

        const FVector2D Center(X + Width * 0.5f, Y + Height * 0.5f);

        Canvas->DrawItem(TextItem, Center);
    }
}

void UGrabbableThumbnailRenderer::BeginDestroy()
{
    if (ThumbnailScene != nullptr)
    {
        delete ThumbnailScene;
        ThumbnailScene = nullptr;
    }

    Super::BeginDestroy();
}
