// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "FreePlayerStart.h"
#include "Gate.h"
#include "Kismet/GameplayStatics.h"

void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

AActor* APingPongGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> FoundStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFreePlayerStart::StaticClass(), FoundStarts);
	for (auto Start : FoundStarts)
	{
		AFreePlayerStart* FreeStart = Cast<AFreePlayerStart>(Start);
		if (FreeStart->IsFree)
		{
			FreeStart->IsFree = false;
			return FreeStart;
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void APingPongGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	APlatformController* Controller = Cast<APlatformController>(NewPlayer);
	Players.Add(Controller);
	
	TakeFreeGate(Controller);

	if (Players.Num() == 2)
	{
		UpdatePLayersUI();
	}
}

void APingPongGameModeBase::TakeFreeGate(APlatformController* Controller)
{
	TArray<AActor*> FoundGates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGate::StaticClass(), FoundGates);
	for (int i = FoundGates.Num() - 1; i >= 0; i--)
	{
		AGate* FreeGate = Cast<AGate>(FoundGates[i]);
		if (FreeGate->PlayerController == nullptr)
		{
			FreeGate->PlayerController = Controller;
			break;
		}
	}
}

void APingPongGameModeBase::UpdatePLayersUI()
{
	for(auto Player : Players)
	{
		Player->UpdateUI();
	}
}
