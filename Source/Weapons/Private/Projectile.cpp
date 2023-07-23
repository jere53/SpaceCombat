// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"


// Sets default values
AProjectile::AProjectile()
{

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionCapsule->InitCapsuleSize(1.f, 2.f);
	CollisionCapsule->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionCapsule->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	RootComponent = CollisionCapsule;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionCapsule->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = DamageType;
	OtherActor->TakeDamage(ProjectileDamage, DamageEvent, GetInstigatorController(), GetInstigator());
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
	SetActorTickEnabled(true);
}

