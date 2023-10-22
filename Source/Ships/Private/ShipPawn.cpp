// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipPawn.h"

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxSpeed = 1000.f;
	TurnSpeed = 200.f;

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
	return RootComponent->ComponentVelocity;
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
	Cast<UPrimitiveComponent>(RootComponent)->SetPhysicsLinearVelocity(NewValue*100000);
	
}

void AShipPawn::SetPosition(FVector NewValue)
{
	SetActorLocation(NewValue);
}

