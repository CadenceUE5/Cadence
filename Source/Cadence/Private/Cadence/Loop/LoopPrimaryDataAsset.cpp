// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopPrimaryDataAsset.h"

#include "Cadence/Loop/LoopFunctionLibrary.h"

ULoopPrimaryDataAssetBase::ULoopPrimaryDataAssetBase()
{
    LoopData.Beats.SetNum(12);
}

K8_GENERATED_FUNCTION_SOURCE(ULoopPrimaryDataAssetBase::UpdateDataDisplayStrings, void, ())
{
    for (int32 i = 0; i < LoopData.Beats.Num(); ++i)
    {
        FLoopBeat& Beat = LoopData.Beats[i];
        for (FLoopItem& Item : Beat.Items)
        {
            Item.UpdateDisplayString();
        }
        Beat.UpdateDisplayString(i);
    }
}

#if WITH_EDITOR
void ULoopPrimaryDataAssetBase::PostLoad()
{
    UPrimaryDataAsset::PostLoad();

    UpdateDataDisplayStrings();
}
void ULoopPrimaryDataAssetBase::PostEditChangeProperty(FPropertyChangedEvent& Event)
{
    UPrimaryDataAsset::PostEditChangeProperty(Event);

    UpdateDataDisplayStrings();
}
#endif

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

    // get beat duration in seconds by dividing BPM by 60, i.e. seconds in a beat.
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
    float VolumeMultiplier, bool IsMuted) const
{
    FLoopData DataCopy = LoopData;

    ULoopFunctionLibrary::FindContextForLoopItems(DataCopy, VolumeMultiplier,
                                                  GrabbableMaterialDataTable);

    DataCopy.Beats.SetNum(Signature.TotalBeatsPerLoop);

    return { .Signature = Signature, .bIsMuted = IsMuted, .History = {}, .Data = DataCopy };
}

void UGoalLoopPrimaryDataAsset::FindColorForAssetLoopItems(
    float VolumeMultiplier, UDataTable const* GrabbableMaterialDataTable)
{
    UDataTable const* DataTablePtr = GrabbableMaterialDataTable;

    if (!GrabbableMaterialDataTable)
    {
        DataTablePtr = mGrabbableMaterialDataTable;
    }

    ULoopFunctionLibrary::FindContextForLoopItems(LoopData, VolumeMultiplier, DataTablePtr);
}
