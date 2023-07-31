// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidInterface.h"

// Add default functionality here for any IBoidInterface functions that are not pure virtual.

FVector IBoidInterface::GetVelocity()
{
	return FVector();
}

float IBoidInterface::GetMaxSpeed()
{
	return 0.0f;
}

FVector IBoidInterface::GetPosition()
{
	return FVector();
}

float IBoidInterface::GetMaxTurnSpeed()
{
	return 0.0f;
}
