// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlatformPawn.generated.h"

UCLASS()
class PINGPONG_API APlatformPawn : public APawn
{
	GENERATED_BODY()

public:
	APlatformPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="PlatformYLimit")
	float Limit;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Unreliable)
	void MovePlatform(FVector MouseLocation);

};
