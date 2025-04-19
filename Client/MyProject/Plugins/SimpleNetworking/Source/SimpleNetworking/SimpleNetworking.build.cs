using UnrealBuildTool;

public class SimpleNetworking : ModuleRules
{
    public SimpleNetworking(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicIncludePaths.AddRange(
            new string[] {
                // ... 필요한 경로 추가
            }
        );
        
        PrivateIncludePaths.AddRange(
            new string[] {
                // ... 필요한 경로 추가
            }
        );
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Sockets",
                "Networking",
                "UMG"
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