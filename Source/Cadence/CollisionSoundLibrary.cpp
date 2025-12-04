// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionSoundLibrary.h"
#include "SoundIDBank.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"

static TMap<FString, TMap<FString, TArray<FString>>> SoundTable;
static TMap<FString, USoundBase*> LoadedSounds;

void UCollisionSoundLibrary::LoadCollisionSounds(USoundIDBank* Bank)
{
    // LOAD SOUND BANK
    if (!Bank)
    {
        UE_LOG(LogTemp, Error, TEXT("SoundIDBank is NULL"));
        return;
    }

    // Load real sound assets into map LoadedSounds.Empty();
    for (const FSoundIDEntry& Entry : Bank->Sounds)
    {
        if (Entry.Sound)
        {
            LoadedSounds.Add(Entry.SoundID, Entry.Sound);
        }
    }

    // LOAD JSON
    FString JsonPath = FPaths::ProjectContentDir() + "Data/CollisionSounds.json";
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
