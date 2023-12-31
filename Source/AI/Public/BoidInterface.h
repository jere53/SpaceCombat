// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BoidInterface.generated.h"
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBoidInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AI_API IBoidInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	static UClass* StaticClass();
	virtual FVector GetVelocity() const;
	virtual float GetMaxSpeed() const;
	virtual FVector GetPosition() const;
	virtual float GetMaxAcceleration() const;
	virtual AActor* GetTarget() const;
	virtual AActor* GetFleeTarget() const;

	virtual void SetVelocity(FVector NewValue);
	virtual void SetPosition(FVector NewValue);
};
