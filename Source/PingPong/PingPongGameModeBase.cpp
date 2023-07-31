// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "FreePlayerStart.h"
#include "Gate.h"
#include "Kismet/GameplayStatics.h"

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

	ConnectedAmount++;
	
	APlatformController* Controller = Cast<APlatformController>(NewPlayer);
	TakeFreeGate(Controller);

	if (ConnectedAmount == 2)
	{
		
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
