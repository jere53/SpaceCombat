// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS(abstract)
class AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:

	//projectile collision capsule
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UCapsuleComponent* CollisionCapsule;


	//projectile damage type class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UDamageType> DamageType;

	float ProjectileSpeed;
	float ProjectileLifetime;
	float ProjectileDamage;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void ProjectileMove(float DeltaTime) PURE_VIRTUAL(AProjectile::ProjectileMove, ;);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ProjectileFire(float Speed, float Damage, float Lifetime);
};
