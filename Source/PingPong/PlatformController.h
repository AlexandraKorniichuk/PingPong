// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPawn.h"
#include "PlatformController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreEvent);

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

	UPROPERTY(Replicated)
	int Score;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	virtual void Tick(float DeltaTime) override;

	void IncreaseScore();
	
	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void UpdateScore();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Score events")
	FScoreEvent OnScoreUpdated;
	
};
