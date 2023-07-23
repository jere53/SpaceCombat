// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWeapon.generated.h"


class UCapsuleComponent;
class AProjectile;

UCLASS()
class WEAPONS_API ASpaceWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceWeapon();

protected:

	//the kind of projectile this weapon fires
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AProjectile> Projectile;

	//range in UE units
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float WeaponRange;

	//how fast the fired projectiles move
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ProjectileSpeed;

	//how many projectiles we can fire in a second
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RateOfFire;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};