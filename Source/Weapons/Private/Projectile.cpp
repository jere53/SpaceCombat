// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// We dont want to start with tick enabled.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OverlapBegin);

}

void AProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = DamageType;
	OtherActor->TakeDamage(ProjectileDamage, DamageEvent, nullptr, this);
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileLifetime > 0)
	{
		ProjectileLifetime -= DeltaTime;
		ProjectileMove(DeltaTime);
	}
	else
	{
		Destroy();
	}

}

void AProjectile::ProjectileFire(float Speed, float Damage, float Lifetime)
{
	ProjectileSpeed = Speed;
	ProjectileDamage = Damage;
	ProjectileLifetime = Lifetime;
	//start ticking
	PrimaryActorTick.bCanEverTick = true;
}

