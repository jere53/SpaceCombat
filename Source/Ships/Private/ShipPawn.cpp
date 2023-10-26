// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipPawn.h"

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 1000.f;
	MaxAcceleration = 200.f;
	Target = nullptr;
	Velocity = FVector(50, 0, 0);
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

float AShipPawn::GetMaxAcceleration()
{
	return MaxAcceleration;
}

void AShipPawn::SetVelocity(FVector NewValue)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), NewValue, FColor::Yellow);
	Velocity = NewValue;
}

void AShipPawn::SetPosition(FVector NewValue)
{
	SetActorLocation(NewValue);
}

FVector AShipPawn::GetTarget()
{
	if(!Target->IsValidLowLevel()) return IBoidInterface::GetTarget();
	return Target->GetActorLocation();
}

