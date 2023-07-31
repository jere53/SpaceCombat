// Fill out your copyright notice in the Description page of Project Settings.


#include "SteeringComponent.h"

// Sets default values for this component's properties
USteeringComponent::USteeringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USteeringComponent::BeginPlay()
{
	Super::BeginPlay();

	ControlledBoid = Cast<IBoidInterface>(GetOwner());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Owner is %s"), *GetOwner()->GetName()));
	}

	if (!ControlledBoid)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("bad ending")));
		}
		return;
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Good ending")));
		}
	}

	Seek(FVector(0, 0, 0), 20);



	ApplySteering();
	// ...

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Steering: %f, %f, %f"), SteeringForce.X, SteeringForce.Y, SteeringForce.Z));
	}
	
}

FVector USteeringComponent::DoSeek(FVector Target, int SlowingRadius)
{
	if (!ControlledBoid || !IsValidLowLevel()) return FVector(0, 0, 0);
	//get a vector pointing at the Target
	FVector DesiredVelocity = Target - (ControlledBoid->GetPosition());
	float DistanceToTarget = DesiredVelocity.Size();
	DesiredVelocity.Normalize();
	if (DistanceToTarget <= SlowingRadius)
	{
		//slow down when we approach the target
		DesiredVelocity *= ControlledBoid->GetMaxSpeed() * (DistanceToTarget / SlowingRadius);
	}
	else
	{
		//go to target at max speed
		DesiredVelocity *= (ControlledBoid)->GetMaxSpeed();
	}
	//the force we wish to apply to the boid in order to reach the target
	FVector TargetSteeringForce = DesiredVelocity - ControlledBoid->GetVelocity();
	return TargetSteeringForce;
}


// Called every frame
void USteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USteeringComponent::Seek(FVector Target, int SlowingRadius)
{
	SteeringForce += DoSeek(Target, SlowingRadius);
}

void USteeringComponent::ApplySteering()
{
	if (!((IBoidInterface*)GetOwner())) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("NO BOID ON  %s"), *GetOwner()->GetName()));
		}
	}

	FVector Velocity = (ControlledBoid)->GetVelocity();
	FVector Position = (ControlledBoid)->GetPosition();
	
	
	//get how fast we can actually turn by dividing how sharp the turn is (degrees) and what the max turn speed is (in degrees/second)
	//1 / (SteeringForce.CosineAngle2D(Velocity) / ControlledBoid->GetMaxTurnSpeed());
	float TurnRate = FMath::Clamp((ControlledBoid->GetMaxTurnSpeed() / SteeringForce.CosineAngle2D(Velocity)), 0.f, 1.f);

	//FVector Acceleration = SteeringForce *TurnRate;

	//Velocity += Acceleration;
	
	//Position += Velocity;

	UPrimitiveComponent* ActorRoot = ((UPrimitiveComponent*)GetOwner()->GetRootComponent());

	check(ActorRoot);

	ActorRoot->AddForce(SteeringForce);
	
}

