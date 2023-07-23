// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "EnergyProjectile.generated.h"

/**
 *
 */
UCLASS()
class AEnergyProjectile : public AProjectile
{
	GENERATED_BODY()

protected:

		virtual void ProjectileMove(float DeltaTime) override;
};
