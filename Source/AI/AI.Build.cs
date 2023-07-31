// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI : ModuleRules
{
	public AI(ReadOnlyTargetRules Target) : base(Target)
	{ 
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "AIModule"});
	}
}
