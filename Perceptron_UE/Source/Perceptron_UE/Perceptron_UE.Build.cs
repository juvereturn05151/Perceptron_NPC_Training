// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Perceptron_UE : ModuleRules
{
	public Perceptron_UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
