// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "PlatformController.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Gate.generated.h"

UCLASS()
class PINGPONG_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	AGate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, Category="Collision")
	UBoxComponent* Trigger;

	APlatformController* PlayerController;

private:
	ABall* Ball;
};
