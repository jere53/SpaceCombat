// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoidInterface.h"
#include "SteeringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class USteeringComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USteeringComponent();

protected:

	FVector SteeringForce;
	
	IBoidInterface* ControlledBoid;

	// Called when the game starts
	virtual void BeginPlay() override;

	FVector DoSeek(FVector Target, int SlowingRadius);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Seek(FVector Target, int SlowingRadius);

	//apply steering forces
	void ApplySteering();
		
};
