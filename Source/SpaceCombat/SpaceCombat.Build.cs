// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceCombat : ModuleRules
{
	public SpaceCombat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Ships", "Weapons" });
	}
}
