// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Grabbable/GrabbablePrimaryDataAsset.h"
#include <UObject/AssetRegistryTagsContext.h>

#if WITH_EDITOR
void UGrabbablePrimaryDataAsset::GetAssetRegistryTags(FAssetRegistryTagsContext Context) const
{
    UPrimaryDataAsset::GetAssetRegistryTags(Context);
    if (Mesh)
    {
        const FString MeshName = Mesh->GetName();
        Context.AddTag(
            FAssetRegistryTag(TEXT("Mesh"), MeshName, FAssetRegistryTag::TT_Alphabetical));
    }
}

#endif
