// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/FloatingPawnMovement.h"
#include "ShipPawn.h"

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


float AShipPawn::GetMaxSpeed()
{
	return MaxSpeed;
}


FVector AShipPawn::GetVelocity()
{
	return Velocity;
}

FVector AShipPawn::GetPosition()
{
	return GetActorLocation();
}

float AShipPawn::GetMaxTurnSpeed()
{
	return TurnSpeed;
}

void AShipPawn::SetVelocity(FVector NewValue)
{
	Velocity = NewValue;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("New Velocity Values are: %f %f %f"), Velocity.X, Velocity.Y, Velocity.Z));
	}
}

void AShipPawn::SetPosition(FVector NewValue)
{
	SetActorLocation(NewValue);
	FVector NewPosition = GetActorLocation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("New Position Values are: %f %f %f"), NewPosition.X, NewPosition.Y, NewPosition.Z));
	}
}

