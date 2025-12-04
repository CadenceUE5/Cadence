// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundIDBank.h"
#include "CollisionSoundLibrary.generated.h"


/**
 * 
 */
UCLASS()
class CADENCE_API UCollisionSoundLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Collision Sounds")
    static void LoadCollisionSounds(USoundIDBank* Bank);

	UFUNCTION(BlueprintCallable, Category = "Collision Sounds")
    static USoundBase* GetCollisionSound(
		FName MaterialA, 
		FName MaterialB,
		float Velocity
	);
};
