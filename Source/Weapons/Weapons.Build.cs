// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Weapons : ModuleRules
{
	public Weapons(ReadOnlyTargetRules Target) : base(Target)
	{ 
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
	}
}
