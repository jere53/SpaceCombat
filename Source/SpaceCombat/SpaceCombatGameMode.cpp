// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceCombatGameMode.h"
#include "Ships/Public/SpaceCombatPawn.h"

ASpaceCombatGameMode::ASpaceCombatGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ASpaceCombatPawn::StaticClass();
}
