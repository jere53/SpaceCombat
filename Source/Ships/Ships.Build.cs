// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ships : ModuleRules
{
	public Ships(ReadOnlyTargetRules Target) : base(Target)
	{ 
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
	}
}
