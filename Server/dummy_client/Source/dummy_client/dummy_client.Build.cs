// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class dummy_client : ModuleRules
{
	public dummy_client(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Sockets", "Networking" });
	}
}
