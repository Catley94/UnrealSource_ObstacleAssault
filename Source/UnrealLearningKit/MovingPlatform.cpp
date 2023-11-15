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

	const FString Name = GetName();
	
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
	
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if(ShouldPlatformReturn())
	{
		const FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartPosition = StartPosition + MovedDistanced * MoveDirection;
		SetActorLocation(StartPosition);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation += (PlatformVelocity * DeltaTime);

		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}



bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistanced;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartPosition, GetActorLocation());
}
