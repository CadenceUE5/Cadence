// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Loop/LoopSoundDataLibrary.h"

void ULoopSoundDataLibrary::ComputeLoopDescriptorVariables(FLoopSoundData& Loop)
{
    if (Loop.kBeatsPerMinute <= 0)
    {
        Loop.mBeatDuration = 0.f;
        Loop.mTotalBeatsPerLoop = 0;
        Loop.gLoopSounds.Reset();
        return;
    }

    Loop.mBeatDuration = 60.f / Loop.kBeatsPerMinute;

    Loop.mTotalBeatsPerLoop = FMath::CeilToInt(Loop.mLoopDuration / Loop.mBeatDuration);

    Loop.gLoopSounds.SetNum(Loop.mTotalBeatsPerLoop);
}

float ULoopSoundDataLibrary::ComputeLoopSoundsSimilarityScore(const FLoopSoundData& A,
                                                              const FLoopSoundData& B)
{
    return 0.5f;
}

int32 ULoopSoundDataLibrary::RoundTimeInLoopToNearestBeat(const FLoopSoundData& Loop,
                                                          float TimeInLoop)
{
    return int32();
}
