// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAIController.h"
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
    
}

void AShipAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (ControlledSpaceship)
    {
        FVector Position = ControlledSpaceship->GetPosition();
        FVector Velocity = ControlledSpaceship->GetVelocity();
        TargetLocation = FVector(100000.0f, 100000.f, 3000040.f);

        DrawDebugLine(GetWorld(), Position, TargetLocation, FColor::Blue);
        
        FVector Steering = Seek(TargetLocation, 100);

        DrawDebugLine(GetWorld(), Position, Steering, FColor::Green);

        FVector EffectiveSteering = FMath::VInterpNormalRotationTo(GetPawn()->GetActorForwardVector(), Steering.GetSafeNormal(), DeltaTime, ControlledSpaceship->GetMaxTurnSpeed());

        DrawDebugLine(GetWorld(), Position, EffectiveSteering, FColor::Red);
        
        Velocity += (EffectiveSteering);

        ControlledSpaceship->SetVelocity(Velocity * 1000);
    }
    else
    {
         UE_LOG(LogTemp, Error, TEXT("AI Controller controls no valid pawn!"));
    }
}

FVector AShipAIController::Seek(const FVector& Target, int SlowdownRadius)
{
    // Get the current position of the spaceship
    FVector CurrentLocation = ControlledSpaceship->GetPosition();

    // Calculate the distance to the target
    float DistanceToTarget = FVector::Distance(CurrentLocation, Target);

    FVector DesiredVelocity;
    if (DistanceToTarget > SlowdownRadius)
    {
        DesiredVelocity = (Target - CurrentLocation).GetSafeNormal() * ControlledSpaceship->GetMaxSpeed();
    }
    else
    {
        // Gradually slow down within the slowdown radius
        float SpeedFactor = DistanceToTarget / SlowdownRadius;
        DesiredVelocity = (Target - CurrentLocation).GetSafeNormal() * ControlledSpaceship->GetMaxSpeed() * SpeedFactor;
    }
    // Calculate the acceleration needed to reach the desired velocity
    FVector Steering = DesiredVelocity - ControlledSpaceship->GetVelocity();

    // Return the steering vector
    return Steering;
}