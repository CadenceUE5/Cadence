// Fill out your copyright notice in the Description page of Project Settings.


#include "AGestureRecorder.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
AAGestureRecorder::AAGestureRecorder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAGestureRecorder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAGestureRecorder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAGestureRecorder::ConvertRenderTargetToDataPoints(UTextureRenderTarget2D* RT, TArray<FVector2D>& OutPoints)
{
    OutPoints.Empty();
    if (!RT) return;

    FTextureRenderTargetResource* Res = RT->GameThread_GetRenderTargetResource();
    int32 Width = RT->SizeX;
    int32 Height = RT->SizeY;

    TArray<FColor> Pixels;
    Pixels.AddUninitialized(Width * Height);
    Res->ReadPixels(Pixels);

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            const FColor& C = Pixels[y * Width + x];

            // White = 255/255/255, allow small tolerance
            bool bIsWhite = (C.R > 250 && C.G > 250 && C.B > 250);

            if (!bIsWhite)
            {
                OutPoints.Add(FVector2D(x, y));
            }
        }
    }
}

