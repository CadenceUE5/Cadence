// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "AGestureRecorder.generated.h"

USTRUCT(BlueprintType) struct FGestureData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GestureName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> Points;
};

USTRUCT(BlueprintType)

struct FGestureDatabaseStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGestureData> Gestures;
};

UCLASS(BlueprintType) class UGestureDatabaseAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGestureDatabaseStruct Database;
};

UCLASS() class CADENCE_API AAGestureRecorder : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FileIO")
    FString m_DatabaseFilePath;

    // Sets default values for this actor's properties
    AAGestureRecorder();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "FileIO")
    bool LoadGestureDatabaseFromJson(const FString& FilePath, UGestureDatabaseAsset*& OutDB);

    UFUNCTION(BlueprintCallable, Category = "FileIO")
    bool AppendGestureToDatabase(const FString& FilePath, const FGestureData& Gesture);

    UFUNCTION(BlueprintCallable, Category = "FileIO")
    bool ExportGestureDatabaseToJson(const FString& FilePath, UGestureDatabaseAsset* DB);

public:
    UFUNCTION(BlueprintCallable, Category = "GestureUtility")
    int32 GetGestureCount();

    UFUNCTION(BlueprintCallable, Category = "GestureUtility")
    TArray<FGestureData> GetAllGestures();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY()
    UGestureDatabaseAsset* m_GestureDB;
};
