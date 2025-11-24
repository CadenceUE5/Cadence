// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGestureRecorder.generated.h"

UCLASS()
class CADENCE_API AAGestureRecorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGestureRecorder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "RenderTarget")
	void ConvertRenderTargetToDataPoints(UTextureRenderTarget2D* RT, TArray<FVector2D>& OutPoints);
};
