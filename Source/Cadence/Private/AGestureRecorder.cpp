// Fill out your copyright notice in the Description page of Project Settings.

#include "Cadence/Gesture/AGestureRecorder.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

// Sets default values
AAGestureRecorder::AAGestureRecorder()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if
    // you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAGestureRecorder::BeginPlay()
{
    Super::BeginPlay();

    LoadGestureDatabaseFromJson(m_DatabaseFilePath, m_GestureDB);
}

bool AAGestureRecorder::LoadGestureDatabaseFromJson(const FString& FilePath,
                                                    UGestureDatabaseAsset*& OutDB)
{
    OutDB = NewObject<UGestureDatabaseAsset>(this);

    if (!FPaths::FileExists(FilePath))
    {
        return true;
    }

    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        return false;
    }

    if (!FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &OutDB->Database, 0, 0))
    {
        return false;
    }
    return true;
}

bool AAGestureRecorder::ExportGestureDatabaseToJson(const FString& FilePath,
                                                    UGestureDatabaseAsset* DB)
{
    FString OutputJson;
    if (!FJsonObjectConverter::UStructToJsonObjectString(*DB, OutputJson))
    {
        return false;
    }

    return FFileHelper::SaveStringToFile(OutputJson, *FilePath);
}

bool AAGestureRecorder::AppendGestureToDatabase(const FString& FilePath, const FGestureData& Gesture)
{
    m_GestureDB->Database.Gestures.Add(Gesture);

    return this->ExportGestureDatabaseToJson(FilePath, m_GestureDB);
}

int32 AAGestureRecorder::GetGestureCount()
{
    if (!m_GestureDB)
    {
        LoadGestureDatabaseFromJson(m_DatabaseFilePath, m_GestureDB);
    }
    return (m_GestureDB ? m_GestureDB->Database.Gestures.Num() : 0);
}

TArray<FGestureData> AAGestureRecorder::GetAllGestures()
{
    if (!m_GestureDB)
    {
        LoadGestureDatabaseFromJson(m_DatabaseFilePath, m_GestureDB);
    }
    return m_GestureDB ? m_GestureDB->Database.Gestures : TArray<FGestureData>{};
}

// Called every frame
void AAGestureRecorder::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
