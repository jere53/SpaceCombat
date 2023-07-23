// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceWeapon.generated.h"


class UCapsuleComponent;
class UArrowComponent;
class AProjectile;
class UStaticMeshComponent;

UCLASS()
class WEAPONS_API ASpaceWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceWeapon();

protected:


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UArrowComponent* WeaponFirePoint;

	//the kind of projectile this weapon fires
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AProjectile> ProjectileType;

	//range in UE units
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float WeaponRange;

	//projectile base damage
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float WeaponDamage;

	//how fast the fired projectiles move UEunits/Second
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ProjectileSpeed;

	//how many projectiles we can fire in a second
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RateOfFire;

	UFUNCTION(BlueprintCallable)
		void FireWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
