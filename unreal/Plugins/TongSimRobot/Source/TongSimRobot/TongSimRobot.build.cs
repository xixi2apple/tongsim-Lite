using UnrealBuildTool;

public class TongSimRobot : ModuleRules
{
    public TongSimRobot(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        CppStandard = CppStandardVersion.Cpp17;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] {  });
    }
}
