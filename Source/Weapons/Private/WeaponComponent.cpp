// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponFirePoint"));
	WeaponFirePoint->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::FireWeapon(AActor* Owner, APawn* Instigator)
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
	SpawnParams.Instigator = Instigator;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Instigator is %s"), *SpawnParams.Instigator->GetName()));
	}

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Set Params")));
	}

	AProjectile* WeaponProjectile = (AProjectile*)GetWorld()->SpawnActor<AProjectile>(ProjectileType, 
		WeaponFirePoint->GetComponentLocation(), WeaponFirePoint->GetComponentRotation(), SpawnParams);

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


