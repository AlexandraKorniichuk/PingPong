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
	if (GetLocalPlayer())
	{
		if (Widget == nullptr)
		{
			Widget = CreateWidget<UUserWidget>(this, WidgetClass);
			Widget->AddToViewport(0);
		}
	}
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

int APlatformController::GetScore() const
{
	return Score;
}

void APlatformController::UpdateScore(int OtherScore, bool DoIncrease)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString::Printf(TEXT("Increase %d"), Score));
	if (DoIncrease)
	{
		Score++;
	}
	ServerUpdateScore(OtherScore);
}

void APlatformController::ServerUpdateScore_Implementation(int OtherScore)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, FString::Printf(TEXT("Update %d"), Score));
	OnScoreUpdated.Broadcast(Score, OtherScore);
}

