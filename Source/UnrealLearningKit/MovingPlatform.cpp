// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += (PlatformVelocity * DeltaTime);

	SetActorLocation(CurrentLocation);

	DistanceBetweenPoints = FVector::Distance(StartPosition, CurrentLocation);

	if(DistanceBetweenPoints > MovedDistanced)
	{
		const FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartPosition = StartPosition + MovedDistanced * MoveDirection;
		SetActorLocation(StartPosition);
		PlatformVelocity = -PlatformVelocity;
	}
	
}

