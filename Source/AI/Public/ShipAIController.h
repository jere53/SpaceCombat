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

    FVector Seek(const FVector& TargetLocation, int SlowdownRadius) const;

    FVector Flee(const FVector& TargetLocation, float DesiredMinDistance) const;

	FVector Wander();

    // Called every frame
    virtual void Tick(float DeltaTime) override;


    UPROPERTY(EditAnywhere)
        float MaxForceMagnitude;

private:
    // Reference to the spaceship controlled by this AI
    class IBoidInterface* ControlledSpaceship;

	float AngleChange = 5.f;
	const float CircleDistance = 1.f;
	const float CircleRadios = 2.f;
	float WanderAngle = 0.f;

	static void SetAngle(FVector& vector, float angle);
	
};
