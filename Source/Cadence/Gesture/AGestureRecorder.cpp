// Fill out your copyright notice in the Description page of Project Settings.

#include "AGestureRecorder.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
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

    return FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, OutDB, 0, 0);
}

bool AAGestureRecorder::ExportGestureDatabaseToJson(const FString& FilePath,
                                                    const UGestureDatabaseAsset* DB)
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
    m_GestureDB->Gestures.Add(Gesture);

    return this->ExportGestureDatabaseToJson(FilePath, m_GestureDB);
}

int32 AAGestureRecorder::GetGestureCount() const
{
    return (m_GestureDB ? m_GestureDB->Gestures.Num() : 0);
}

TArray<FGestureData> AAGestureRecorder::GetAllGestures() const
{
    if (m_GestureDB)
    {
        return m_GestureDB->Gestures;
    }

    return {};
}

// Called every frame
void AAGestureRecorder::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
