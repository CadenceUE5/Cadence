#include "Cadence/K8_UtilityCore.h"

/* Define a log category for our module */
DEFINE_LOG_CATEGORY(LogCadence);

#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"
#include "AssetRegistry/AssetData.h"

UObject* K8::Utility::FindAssetByClass(UClass* AssetClass)
{
    if (!AssetClass)
    {
        return nullptr;
    }

    FAssetRegistryModule& AssetRegistryModule
        = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

    FARFilter Filter;
    Filter.ClassPaths.Add(AssetClass->GetClassPathName());
    Filter.bRecursiveClasses = true;

    TArray<FAssetData> Assets;
    AssetRegistryModule.Get().GetAssets(Filter, Assets);

    if (Assets.Num() == 0)
    {
        return nullptr;
    }

    return Assets[0].GetAsset();
}

void K8::Utility::GetAssetDataOfClass(UClass* AssetClass, TArray<FAssetData>& OutAssets)
{
    OutAssets.Reset();

    if (!AssetClass)
    {
        return;
    }

    IAssetRegistry& AssetRegistry
        = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

    AssetRegistry.GetAssetsByClass(AssetClass->GetClassPathName(), OutAssets, true);
}

int32 K8::Utility::FindAssetIndexByObjectPath(const TArray<FAssetData>& Assets,
                                              const FSoftObjectPath& TargetPath)
{
    for (int32 Index = 0; Index < Assets.Num(); Index++)
    {
        if (Assets[Index].GetSoftObjectPath() == TargetPath)
        {
            return Index;
        }
    }

    return INDEX_NONE;
}

int32 K8::Utility::FindAssetIndexByDisplayText(const TArray<FAssetData>& Assets, const FText& Text)
{
    const FString Target = Text.ToString();

    for (int32 Index = 0; Index < Assets.Num(); ++Index)
    {
        if (Assets[Index].AssetName.ToString() == Target)
        {
            return Index;
        }
    }

    return INDEX_NONE;
}
