// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::ResetLocation()
{
	SetActorLocation(StartLocation);
}

