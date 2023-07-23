// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyProjectile.h"

void AEnergyProjectile::ProjectileMove(float DeltaTime)
{
	//move the energy projectile forward according to its speed

	const FVector LocalMove = FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);
}