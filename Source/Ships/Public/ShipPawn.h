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

	FVector Position;
	FVector Velocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float GetMaxSpeed() override;
	virtual FVector GetVelocity() override;
	virtual FVector GetPosition() override;
	virtual float GetMaxAcceleration() override;
	virtual void SetVelocity(FVector NewValue) override;
	virtual void SetPosition(FVector NewValue) override;
	virtual FVector GetTarget() override; 

	UPROPERTY(EditAnywhere)
		AActor* Target; 
	
	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
		float MaxAcceleration;
};
