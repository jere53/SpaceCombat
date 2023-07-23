// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWeapon.h"
#include "Projectile.h"

// Sets default values
ASpaceWeapon::ASpaceWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpaceWeapon::FireWeapon()
{
	//spawn a projectile at weapon and tell it to fire
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	//placeholder, well add an actual spawn location later
	FVector BarrelLocation = GetActorLocation() + FVector(10, 0, 0);
	AProjectile* WeaponProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, BarrelLocation, FRotator::ZeroRotator, SpawnParams);

	WeaponProjectile->ProjectileFire(ProjectileSpeed, WeaponDamage, WeaponRange / ProjectileSpeed);
}

// Called when the game starts or when spawned
void ASpaceWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

