// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AProjectile::ProjectileMove(float DeltaTime)
{
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

