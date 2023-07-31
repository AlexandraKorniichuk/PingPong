// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlatformController.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"


UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void OnPostLogin(AController* NewPlayer) override;

	void TakeFreeGate(APlatformController* Controller);

	TArray<APlatformController*> Players;

	void UpdatePLayersUI();	
};
