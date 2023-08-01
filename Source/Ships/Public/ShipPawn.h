// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AI/Public/BoidInterface.h"
#include "ShipPawn.generated.h"

UCLASS()
class SHIPS_API AShipPawn : public APawn, public IBoidInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class UFloatingPawnMovement* FloatingMovementComponent;

	// Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	// Movement variables
	float CurrentForwardSpeed;
	float CurrentRightSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Function to set the spaceship's desired direction and accelerate towards it
	UFUNCTION(BlueprintCallable)
		void AccelerateTowardsDirection(FVector Direction);


	virtual float GetMaxSpeed() override;
	virtual void AccelerateTowardDirection(FVector D) override;
	virtual FVector GetVelocity() override;
};
