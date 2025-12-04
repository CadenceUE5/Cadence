// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionSoundLibrary.h"

static TMap<FString, TMap<FString, TArray<FString>>> SoundTable;
static TMap<FString, USoundBase*> LoadedSounds;

void UCollisionSoundLibrary::LoadCollisionSounds()
{
    // Will load the sound table from a json file
    // For simplicity, hardcoded some values here for now
    /*SoundTable.Add("Metal", {
        {"Metal", {"Metal_Metal_Hit1", "Metal_Metal_Hit2"}},
        {"Wood", {"Metal_Wood_Hit1", "Metal_Wood_Hit2"}}
    });
    SoundTable.Add("Wood", {
        {"Wood", {"Wood_Wood_Hit1", "Wood_Wood_Hit2"}},
        {"Metal", {"Wood_Metal_Hit1", "Wood_Metal_Hit2"}}
    });*/
    // Preload sounds into LoadedSounds map
    /*for (const auto& MaterialAEntry : SoundTable)
    {
        for (const auto& MaterialBEntry : MaterialAEntry.Value)
        {
            for (const FString& SoundName : MaterialBEntry.Value)
            {
                if (!LoadedSounds.Contains(SoundName))
                {
                    USoundBase* Sound = LoadObject<USoundBase>(nullptr,
    *FString::Printf(TEXT("/Game/Sounds/%s.%s"), *SoundName, *SoundName)); if (Sound)
                    {
                        LoadedSounds.Add(SoundName, Sound);
                    }
                }
            }
        }
    }*/
    FString JsonPath = FPaths::ProjectContentDir() + "Source/CollisionSounds.json";
    FString JsonRaw;

    FFileHelper::LoadFileToString(JsonRaw, *JsonPath);

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonRaw);
    FJsonSerializer::Deserialize(Reader, Root);

    for (auto& MatPair : Root->Values)
    {
        FString MatA = MatPair.Key;
        auto Combos = MatPair.Value->AsObject();

        for (auto& ComboPair : Combos->Values)
        {
            FString MatB = ComboPair.Key;
            auto SoundArray = ComboPair.Value->AsArray();

            TArray<FString> IDs;
            for (auto& SoundValue : SoundArray)
            {
                IDs.Add(SoundValue->AsString());
            }

            SoundTable.FindOrAdd(MatA).Add(MatB, IDs);
        }
    }
}

static int32 GetVelocityIndex(float Speed)
{
    if (Speed < 200)
    {
        return 0;
    }
    if (Speed < 600)
    {
        return 1;
    }
    return 2;
}

USoundBase* UCollisionSoundLibrary::GetCollisionSound(FName A, 
                                                     FName B,
                                                     float Velocity)
{
    FString KeyA = (A).ToString();
    FString KeyB = (B).ToString();

    if (!SoundTable.Contains(KeyA))
    {
        return nullptr;
    }
    if (!SoundTable[KeyA].Contains(KeyB))
    {
        return nullptr;
    }

    int32 Index = GetVelocityIndex(Velocity);
    FString SoundID = SoundTable[KeyA][KeyB][Index];

    return LoadedSounds.Contains(SoundID) ? LoadedSounds[SoundID] : nullptr;
}
