using UnrealBuildTool;

public class TongSimRobotEditor : ModuleRules
{
    public TongSimRobotEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp17;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine",
            "TongSimRobot"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { 
            "UnrealEd",
            "Slate",
            "SlateCore" 
        });
    }
}
