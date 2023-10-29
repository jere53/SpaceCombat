// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidInterface.h"

// Add default functionality here for any IBoidInterface functions that are not pure virtual.

FVector IBoidInterface::GetVelocity() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return FVector();
}

float IBoidInterface::GetMaxSpeed() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return 0.0f;
}

FVector IBoidInterface::GetPosition() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return FVector();
}

float IBoidInterface::GetMaxAcceleration() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return 0.0f;
}

AActor* IBoidInterface::GetTarget() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return nullptr;
}

AActor* IBoidInterface::GetFleeTarget() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Base Boid method called")));
	}
	return nullptr;
}

void IBoidInterface::SetVelocity(FVector NewValue)
{
	
}

void IBoidInterface::SetPosition(FVector NewValue)
{

}
