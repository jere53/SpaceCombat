// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipAIController.h"
#include "BoidInterface.h"

AShipAIController::AShipAIController()
{
    MaxForceMagnitude = 0;
    ControlledSpaceship = nullptr;
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
        const FVector& Position = ControlledSpaceship->GetPosition();
        const FVector& Target = ControlledSpaceship->GetTarget();
        FVector Velocity = ControlledSpaceship->GetVelocity();

        DrawDebugLine(GetWorld(), Position, Target, FColor::Blue);
        
        const FVector& SteeringForce = Seek(Target, 100);
        const FVector& Acceleration = SteeringForce; //we could divide by mass if we want;
        
        //const FVector& EffectiveSteering = FMath::VInterpNormalRotationTo(GetPawn()->GetActorForwardVector(), Steering.GetSafeNormal(), DeltaTime, ControlledSpaceship->GetMaxForce());

        DrawDebugLine(GetWorld(), Position, Acceleration, FColor::Red);
        
        Velocity += Acceleration * DeltaTime;
        
        Velocity.GetClampedToMaxSize(ControlledSpaceship->GetMaxSpeed());
        

        ControlledSpaceship->SetVelocity(Velocity);
        ControlledSpaceship->SetPosition(Position + Velocity);
    }
    else
    {
         UE_LOG(LogTemp, Error, TEXT("AI Controller controls no valid pawn!"));
    }
}

void AShipAIController::SetAngle(FVector& vector, float Angle)
{
    const float Len = vector.Length();  
    const FVector Angled = FVector(cos(Angle), 1, sin(Angle)) * Len;
    vector = Angled;
}

FVector AShipAIController::Seek(const FVector& Target, int SlowdownRadius) const
{
    // Get the current position of the spaceship
    const FVector& CurrentLocation = ControlledSpaceship->GetPosition();

    // Calculate the distance to the target
    const float& DistanceToTarget = FVector::Distance(CurrentLocation, Target);

    FVector DesiredVelocity;
    if (DistanceToTarget > SlowdownRadius)
    {
        DesiredVelocity = (Target - CurrentLocation).GetUnsafeNormal() * ControlledSpaceship->GetMaxSpeed();
    }
    else
    {
        // Gradually slow down within the slowdown radius
        const float SlowedSpeed = DistanceToTarget / SlowdownRadius;
        const float& SpeedFactor = SlowedSpeed > 1 ? SlowedSpeed : 0 ;
        DesiredVelocity = (Target - CurrentLocation).GetUnsafeNormal() * ControlledSpaceship->GetMaxSpeed() * SpeedFactor;
    }
    // Calculate the acceleration needed to reach the desired velocity
    const FVector& Steering = DesiredVelocity - ControlledSpaceship->GetVelocity();

    
    UE_LOG(LogTemp, Log, TEXT("SPEED TGT: %f %f %f"), Steering.X, Steering.Y, Steering.Z);

    DrawDebugLine(GetWorld(), ControlledSpaceship->GetPosition(), Steering, FColor::Green);

    // Return the steering vector
    return Steering.GetClampedToMaxSize(ControlledSpaceship->GetMaxAcceleration());
}

FVector AShipAIController::Flee(const FVector& TargetLocation, float DesiredMinDistance) const
{
    if(!ControlledSpaceship) return FVector::Zero();
    if(FVector::Distance(TargetLocation, ControlledSpaceship->GetPosition()) > DesiredMinDistance) return FVector::Zero(); 
    return -1 * Seek(TargetLocation, 0);
}

FVector AShipAIController::Wander()
{
    if(!ControlledSpaceship) return  FVector::Zero();
    const FVector CircleCenter = ControlledSpaceship->GetVelocity().GetUnsafeNormal() * CircleDistance;
    FVector DisplacementAcc = FVector(0,1,0) * CircleRadios;

    WanderAngle += FMath::RandRange(0.f, AngleChange) - AngleChange/2;
    SetAngle(DisplacementAcc, WanderAngle);
    return (CircleCenter + DisplacementAcc);
}
