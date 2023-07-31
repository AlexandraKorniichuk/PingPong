// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"

#include "Kismet/GameplayStatics.h"


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

	AActor* FoundBall = UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass());
	Ball = Cast<ABall>(FoundBall);
}

void AGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Ball)
	{
		Ball->ResetLocation();
	}
	
	if (GetLocalRole() == ROLE_Authority)
	{
		TArray<AActor*> FoundControllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlatformController::StaticClass(), FoundControllers);
		APlatformController* OtherController = PlayerController;
		for (int i = 0; i < FoundControllers.Num(); i++)
		{
			OtherController = Cast<APlatformController>(FoundControllers[i]);
			if (OtherController != PlayerController)
			{
				break;
			}
		}
		OtherController->UpdateScore(PlayerController->GetScore(), true);
		PlayerController->UpdateScore(OtherController->GetScore(), false);
	}
}

void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

