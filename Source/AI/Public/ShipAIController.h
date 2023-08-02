// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShipAIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_API AShipAIController : public AAIController
{
	GENERATED_BODY()
public:
    // Sets default values for this controller's properties
    AShipAIController();

    // Called when the AI controller possesses a pawn
    virtual void OnPossess(APawn* InPawn) override;

    // Implement Seek behavior
    FVector Seek(const FVector& TargetLocation, int SlowdownRadius);

    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UPROPERTY(EditAnywhere)
        float MaxForceMagnitude;

private:
    // Reference to the spaceship controlled by this AI
    class IBoidInterface* ControlledSpaceship;

    // The target location to seek
    FVector TargetLocation;
};
