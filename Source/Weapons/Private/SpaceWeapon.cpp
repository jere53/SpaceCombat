// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceWeapon.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
// Sets default values
ASpaceWeapon::ASpaceWeapon()
{
	WeaponFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponFirePoint"));
	RootComponent = WeaponFirePoint;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpaceWeapon::FireWeapon()
{
	if (!IsValidLowLevel())
	{
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Called FireWeapon")));
	}

	//spawn a projectile at weapon and tell it to fire
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.bNoFail = true;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Set Params")));
	}

	//FVector FireFromLocation = GetActorLocation();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Set Location")));
	}

	AProjectile* WeaponProjectile = (AProjectile*) GetWorld()->SpawnActor<AProjectile>(ProjectileType, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

	if (WeaponProjectile == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failed to spawn Projectile"));

		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Just Before Fire")));
	}


	WeaponProjectile->ProjectileFire(ProjectileSpeed, WeaponDamage, WeaponRange / ProjectileSpeed);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Fired")));
	}

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

