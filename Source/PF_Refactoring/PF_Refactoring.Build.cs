// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PF_Refactoring : ModuleRules
{
	public PF_Refactoring(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AnimGraphRuntime" });
        PublicIncludePaths.Add(ModuleDirectory);
    }
}
