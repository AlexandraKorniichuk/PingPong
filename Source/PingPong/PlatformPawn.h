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

	UFUNCTION()
	void OnRep_MeshLocation();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TryMovePlatform(FVector MouseLocation);
	
	UFUNCTION(Server, Reliable)
	void ServerMovePlatform(FVector MouseLocation);

	UPROPERTY(ReplicatedUsing = OnRep_MeshLocation)
	FVector MeshLocation;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	bool IsInverted;

	float GetYLocation(float MouseY);
};
