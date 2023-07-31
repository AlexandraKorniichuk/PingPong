// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformController.h"
#include "Net/UnrealNetwork.h"

APlatformController::APlatformController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformController::BeginPlay()
{
	Super::BeginPlay();

	Platform = Cast<APlatformPawn>(GetPawn());
}

void APlatformController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlatformController, Score);
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

void APlatformController::IncreaseScore()
{
	Score++;
	UpdateScore();
}

void APlatformController::UpdateScore_Implementation()
{
	OnScoreUpdated.Broadcast();
}

