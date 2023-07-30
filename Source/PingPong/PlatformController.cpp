// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformController.h"

APlatformController::APlatformController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformController::BeginPlay()
{
	Super::BeginPlay();

	Platform = Cast<APlatformPawn>(GetPawn());
}

void APlatformController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Platform)
	{
		FVector Location = FVector::Zero();
		FVector Direction = FVector::Zero();
		DeprojectMousePositionToWorld(Location, Direction);
		Platform->ServerMovePlatform(Location);
	}
}

