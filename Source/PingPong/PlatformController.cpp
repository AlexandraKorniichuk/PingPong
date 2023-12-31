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
		CreateWidgetIfNull();
	}
}

void APlatformController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlatformController, Score);
}

void APlatformController::CreateWidgetIfNull()
{
	if (Widget == nullptr)
	{
		Widget = CreateWidget<UUserWidget>(this, WidgetClass);
		Widget->AddToViewport(0);
	}
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
	if (DoIncrease)
	{
		Score++;
	}
	ClientUpdateScore(Score, OtherScore);
}

void APlatformController::UpdateUI()
{
	ClientUpdateUI();
}

void APlatformController::ClientUpdateUI_Implementation()
{
	if(Widget == nullptr)
	{
		CreateWidgetIfNull();
	}
	OnStart.Broadcast();
}

void APlatformController::ClientUpdateScore_Implementation(int PlayerScore, int OtherScore)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Client s %d"), Score));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Client p %d"), PlayerScore));
	OnScoreUpdated.Broadcast(PlayerScore, OtherScore);
}

