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


	UPROPERTY()
		FVector Position;

	UPROPERTY()
		FVector Velocity;

public:
	// Sets default values for this pawn's properties
	AShipPawn();


	UPROPERTY()
		float MaxVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float GetMaxSpeed() override;
	virtual FVector GetVelocity() override;
	virtual FVector GetPosition() override;
	virtual float GetMaxTurnSpeed() override;

	UPROPERTY(EditAnywhere)
		float MaxSpeed;


	UPROPERTY(EditAnywhere)
		float TurnSpeed;
};
