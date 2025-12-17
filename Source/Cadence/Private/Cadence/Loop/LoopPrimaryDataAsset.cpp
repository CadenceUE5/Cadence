// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopPrimaryDataAsset.h"

#include "Cadence/Loop/LoopFunctionLibrary.h"

FLoopInstance UTemplateLoopPrimaryDataAsset::MakeTemplateLoopInstance(int32 BeatsPerMinute,
                                                                      float VolumeMultiplier,
                                                                      bool IsMuted) const
{
    if (BeatsPerMinute <= 0)
    {
        return {};
    }

    FLoopData DataCopy = LoopData;

    ULoopFunctionLibrary::NormalizeLoopData(DataCopy, VolumeMultiplier);

    const float BeatDuration = 60.f / static_cast<float>(BeatsPerMinute);

    const float LoopDuration = ULoopFunctionLibrary::ComputeLoopDuration(DataCopy, BeatDuration);

    const int32 TotalBeatsPerLoop = FMath::CeilToInt(LoopDuration / BeatDuration);

    const float LoopDurationCeil = TotalBeatsPerLoop * BeatDuration;

    const FLoopRootSignature Signature = { .BeatsPerMinute = BeatsPerMinute,
                                           .LoopDuration = LoopDurationCeil,
                                           .BeatDuration = BeatDuration,
                                           .TotalBeatsPerLoop = TotalBeatsPerLoop };

    DataCopy.Beats.SetNum(Signature.TotalBeatsPerLoop);

    return { .Signature = Signature, .bIsMuted = IsMuted, .History = {}, .Data = DataCopy };
}

FLoopInstance UGoalLoopPrimaryDataAsset::MakeGoalLoopInstance(
    const FLoopRootSignature Signature, UDataTable const* GrabbableMaterialDataTable,
    bool IsMuted) const
{
    FLoopData DataCopy = LoopData;

    ULoopFunctionLibrary::FindContextForLoopItems(DataCopy, GrabbableMaterialDataTable);

    DataCopy.Beats.SetNum(Signature.TotalBeatsPerLoop);

    return { .Signature = Signature, .bIsMuted = IsMuted, .History = {}, .Data = DataCopy };
}

void UGoalLoopPrimaryDataAsset::FindColorForAssetLoopItems(
    UDataTable const* GrabbableMaterialDataTable)
{
    UDataTable const* DataTablePtr = GrabbableMaterialDataTable;

    if (!GrabbableMaterialDataTable)
    {
        DataTablePtr = mGrabbableMaterialDataTable;
    }

    ULoopFunctionLibrary::FindContextForLoopItems(LoopData, DataTablePtr);
}
