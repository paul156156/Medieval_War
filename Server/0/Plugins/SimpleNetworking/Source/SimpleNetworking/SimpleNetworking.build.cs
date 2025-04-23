using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class SimpleNetworking : ModuleRules
{
    public SimpleNetworking(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "Sockets",
                "Networking"
            }
        );
        
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // ... 필요한 모듈 추가
            }
        );
    }
}