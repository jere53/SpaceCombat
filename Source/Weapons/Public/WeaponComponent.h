// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"


class UArrowComponent;
class AProjectile;
class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONS_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Fires the weapon by spawning a projectile. Parameters are used to set projectile SpawnParams**/
	UFUNCTION(BlueprintCallable)
		void FireWeapon(AActor* Owner, APawn* Instigator);
};
