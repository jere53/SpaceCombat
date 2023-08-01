// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAIController.h"
#include "NavigationSystem.h"
#include "BoidInterface.h"

AShipAIController::AShipAIController()
{
    // Initialize the TargetLocation to a default value
    TargetLocation = FVector::ZeroVector;
}

void AShipAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Cast the possessed pawn to the spaceship class
    ControlledSpaceship = Cast<IBoidInterface>(InPawn);

    // Start the Seek behavior (you can trigger this behavior based on game events)
    // For this example, let's set the target location to (1000, 0, 0)
    TargetLocation = FVector(1000.0f, 0.0f, 0.0f);
}

void AShipAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ControlledSpaceship)
    {
        // Implement Seek behavior and get the acceleration vector
        FVector Acceleration = Seek(TargetLocation);

        // Apply the acceleration vector to the spaceship
        ControlledSpaceship->AccelerateTowardDirection(Acceleration);
    }
}

FVector AShipAIController::Seek(const FVector& Target)
{
    // Get the current position of the spaceship
    FVector CurrentLocation = ControlledSpaceship->Actor->GetActorLocation();

    // Calculate the desired velocity (direction towards the target)
    FVector DesiredVelocity = (Target - CurrentLocation).GetSafeNormal() * ControlledSpaceship->GetMaxSpeed();

    // Calculate the acceleration needed to reach the desired velocity
    FVector Acceleration = DesiredVelocity - ControlledSpaceship->GetVelocity();

    // Return the acceleration vector
    return Acceleration;
}