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
	FleeTarget = nullptr;
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


float AShipPawn::GetMaxSpeed() const
{
	return MaxSpeed;
}


FVector AShipPawn::GetVelocity() const
{
	return Velocity;
}

FVector AShipPawn::GetPosition() const
{
	return GetActorLocation();
}

float AShipPawn::GetMaxAcceleration() const
{
	return MaxAcceleration;
}

void AShipPawn::SetVelocity(FVector NewValue)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), NewValue, FColor::Yellow);
	Velocity = NewValue;
	const FRotator NewRot = (Velocity - GetActorForwardVector()).Rotation();
	SetActorRotation(NewRot);
}

void AShipPawn::SetPosition(FVector NewValue)
{
	SetActorLocation(NewValue);
}

AActor* AShipPawn::GetTarget() const
{
	if(!Target->IsValidLowLevel()) return nullptr;
	return Target;
}

AActor* AShipPawn::GetFleeTarget() const
{
	return FleeTarget;
}

