// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Web : ModuleRules
{
	public Web(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemUtils" });
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
	}
}
