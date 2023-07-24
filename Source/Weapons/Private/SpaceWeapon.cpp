// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWeapon.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
// Sets default values
ASpaceWeapon::ASpaceWeapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponFirePoint"));
	WeaponFirePoint->SetupAttachment(RootComponent);
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
	FVector FireFromLocation = WeaponFirePoint->GetComponentLocation();


	AProjectile* WeaponProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileType, FireFromLocation, FRotator::ZeroRotator, SpawnParams);

	if (WeaponProjectile == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failed to spawn Projectile"));

		return;
	}
	

	//move the projectile down a bit so its center is aligned with the canon

	FVector NewLocation = WeaponProjectile->GetActorLocation() - FVector(0, 0, WeaponProjectile->GetProjectileHalfHeight());
	WeaponProjectile->SetActorLocation(NewLocation);



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

