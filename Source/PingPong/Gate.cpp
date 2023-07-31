// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"


AGate::AGate()
{
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

void AGate::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger)
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnOverlapBegin);
}

void AGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		Controller->IncreaseScore();
	}
}

void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

