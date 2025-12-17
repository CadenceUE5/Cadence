#include "CadenceEditor.h"

#include "ThumbnailRendering/ThumbnailManager.h"

#include "Cadence/Grabbable/GrabbablePrimaryDataAsset.h"
#include "CadenceEditor/Grabbable/GrabbableThumbnailRenderer.h"

IMPLEMENT_MODULE(FCadenceEditor, CadenceEditor);

void FCadenceEditor::StartupModule()
{
    UThumbnailManager::Get().RegisterCustomRenderer(UGrabbablePrimaryDataAsset::StaticClass(),
                                                    UGrabbableThumbnailRenderer::StaticClass());
}

void FCadenceEditor::ShutdownModule() {}
