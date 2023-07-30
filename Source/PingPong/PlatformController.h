// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPawn.h"
#include "PlatformController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APlatformController : public APlayerController
{
	GENERATED_BODY()

public:
	APlatformController();

protected:
	virtual void BeginPlay() override;

private:
	APlatformPawn* Platform;

public:	
	virtual void Tick(float DeltaTime) override;
	
};
