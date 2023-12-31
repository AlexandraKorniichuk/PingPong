// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformPawn.h"
#include "Blueprint/UserWidget.h"
#include "PlatformController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreEvent, int, Score, int, OtherScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartEvent);

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
	int Score = 0;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CreateWidgetIfNull();

public:	
	virtual void Tick(float DeltaTime) override;

	int GetScore() const;
	
	void UpdateScore(int OtherScore, bool DoIncrease);
	
	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void ClientUpdateScore(int PlayerScore, int OtherScore);

	void UpdateUI();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void ClientUpdateUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Start events")
	FStartEvent OnStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable, Category="Score events")
	FScoreEvent OnScoreUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UUserWidget* Widget;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
};
