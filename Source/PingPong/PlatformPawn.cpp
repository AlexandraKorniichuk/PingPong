// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "Net/UnrealNetwork.h"

APlatformPawn::APlatformPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
	IsInverted = GetActorRotation().Yaw > 1;
}

void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlatformPawn::TryMovePlatform(FVector MouseLocation)
{
	float MouseY = MouseLocation.Y;
	if (MouseY >= -Limit && MouseY <= Limit)
	{
		FVector CurrentMeshLocation = Mesh->GetRelativeLocation();
		MeshLocation = FVector(CurrentMeshLocation.X, GetYLocation(MouseY), CurrentMeshLocation.Z);
		Mesh->SetRelativeLocation(MeshLocation);
	}
}

void APlatformPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlatformPawn, MeshLocation);
}

float APlatformPawn::GetYLocation(float MouseY)
{
	if (IsInverted)
	{
		return -MouseY * 100;
	}
	return MouseY * 100;
}


void APlatformPawn::ServerMovePlatform_Implementation(FVector MouseLocation)
{
	if (HasAuthority())
	{
		TryMovePlatform(MouseLocation);
	}
}

void APlatformPawn::OnRep_MeshLocation()
{
	if (Mesh)
	{
		Mesh->SetRelativeLocation(MeshLocation);
	}
}



