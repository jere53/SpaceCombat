// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/FloatingPawnMovement.h"
#include "ShipPawn.h"

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	FloatingMovementComponent->UpdatedComponent = RootComponent;
	FloatingMovementComponent->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	Actor = GetOwner();
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	((UPrimitiveComponent*)RootComponent)->AddForce(GetActorForwardVector() * GetMaxSpeed(), NAME_None, true);
	return;
}

// Called to bind functionality to input
void AShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind functions to handle player input
	PlayerInputComponent->BindAxis("MoveForward", this, &AShipPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShipPawn::MoveRight);

}

void AShipPawn::MoveForward(float AxisValue)
{
	// Handle forward movement input
	CurrentForwardSpeed = AxisValue;
}

void AShipPawn::MoveRight(float AxisValue)
{
	// Handle right movement input
	CurrentRightSpeed = AxisValue;
}

void AShipPawn::AccelerateTowardsDirection(FVector Direction)
{ 
	
	// Calculate the rotation needed to face the desired direction
	FVector CurrentForwardVector = GetActorForwardVector();
	FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), .5f);
	/*
	// Apply the new rotation to the spaceship
	SetActorRotation(NewRotation);

	// Accelerate the spaceship forward
	CurrentForwardSpeed = 1.0f; // Set the desired forward speed here

	FVector MovementDirection = (CurrentForwardVector * CurrentForwardSpeed);
	FloatingMovementComponent->AddInputVector(Direction);
	GetController()->SetControlRotation(NewRotation);
	//FloatingMovementComponent->MoveUpdatedComponent(MovementDirection, TargetRotation, true);
	*/

	//((UPrimitiveComponent*)RootComponent)->SetAllPhysicsRotation(NewRotation);
	((UPrimitiveComponent*)RootComponent)->AddForce(Direction, NAME_None, true);
}

float AShipPawn::GetMaxSpeed()
{
	return FloatingMovementComponent->MaxSpeed;
}

void AShipPawn::AccelerateTowardDirection(FVector D)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("ACCELERATE")));
	}
	AccelerateTowardsDirection(D);
}

FVector AShipPawn::GetVelocity()
{
	return ((UPrimitiveComponent*)RootComponent)->GetPhysicsLinearVelocity();
}

