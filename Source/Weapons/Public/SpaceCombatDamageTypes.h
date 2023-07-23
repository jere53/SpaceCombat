#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "SpaceCombatDamageTypes.generated.h"

UCLASS(const, Blueprintable, BlueprintType)
class UIonDamageType : public UDamageType
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		int ShieldDamageModifyer;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		int HullDamageModifyer;
};

UCLASS(const, Blueprintable, BlueprintType)
class ULaserDamageType : public UDamageType
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		int ShieldDamageModifyer;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
		int HullDamageModifyer;

};