// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "Engine/Engine.h"

APlatformPawn::APlatformPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlatformPawn::MovePlatform_Implementation(FVector MouseLocation)
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Purple,FString::Printf(TEXT("Hello %s"),*MouseLocation.ToString()));
	float MouseY = MouseLocation.Y;
	if (MouseY >= -Limit && MouseY <= Limit)
	{
		//FVector MeshLocation = Mesh->GetRelativeLocation();
		//Mesh->SetRelativeLocation(FVector(MeshLocation.X, MouseY * 100, MeshLocation.Z));
		FVector ActorLocation = GetActorLocation();
		SetActorLocation(FVector(ActorLocation.X, MouseY * 100, ActorLocation.Z));
	}
	if(GetLocalRole())
	{
		
	}
}



