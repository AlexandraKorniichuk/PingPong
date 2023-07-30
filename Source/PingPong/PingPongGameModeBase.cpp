// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "FreePlayerStart.h"
#include "ToolBuilderUtil.h"
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
