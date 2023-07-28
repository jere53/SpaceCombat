// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"


// Sets default values
AProjectile::AProjectile()
{

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionCapsule->InitCapsuleSize(20.f, 20.f);

	RootComponent = CollisionCapsule;

	CollisionCapsule->BodyInstance.SetResponseToAllChannels(ECR_Overlap);
	
	DamageType = UDamageType::StaticClass();

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//dont collide with whoever fired the weapon
	CollisionCapsule->IgnoreActorWhenMoving(GetInstigator(), true);
	CollisionCapsule->IgnoreActorWhenMoving(GetOwner(), true);

	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if we hit ourselves or another projectile we fired, do nothing
	if (OtherActor == GetInstigator())
	{
		return;
	}

	if (OtherActor->GetInstigator() == GetInstigator())
	{
		return;
	}


	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Projectile Hit!!"));

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

float AProjectile::GetProjectileHalfHeight()
{
	return CollisionCapsule->GetUnscaledCapsuleHalfHeight();
}