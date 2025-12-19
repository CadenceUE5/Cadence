#include "Cadence/K8_UtilityCore.h"

/* Define a log category for our module */
DEFINE_LOG_CATEGORY(LogCadence);

#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"

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
