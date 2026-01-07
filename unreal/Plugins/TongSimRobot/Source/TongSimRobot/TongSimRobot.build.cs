using System;
using System.IO;
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
        
        string PluginRootDir = Directory.GetParent(ModuleDirectory).Parent.FullName;
        string ThirdPartyRoot = Path.Combine(PluginRootDir, "ThirdParty");
        string MujocoLibIncludePath = Path.Combine(ThirdPartyRoot, "MujocoLib", "Include");
        string MujocoLibLibPath = Path.Combine(ThirdPartyRoot, "MujocoLib", "Lib");
        
        // System.Console.WriteLine($"ModuleDirectory: {PluginRootDir}");
        // System.Console.WriteLine($"ThirdPartyRoot: {ThirdPartyRoot}");
        // System.Console.WriteLine($"MujocoLibIncludePath: {MujocoLibIncludePath}");
        // System.Console.WriteLine($"MujocoLibLibPath: {MujocoLibLibPath}");
        
        PublicIncludePaths.Add(MujocoLibIncludePath);
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Find the 3rd Party DLL
            PublicAdditionalLibraries.Add(Path.Combine(MujocoLibLibPath, "Win64/mujoco.lib"));
            string DLLTargetPath = Path.Combine(MujocoLibLibPath, "Win64/mujoco.dll");
            
            System.Console.WriteLine($"DLLTargetPath: {DLLTargetPath}");
            
            RuntimeDependencies.Add(DLLTargetPath);     // Add a dependancy on the DLL
            PublicDelayLoadDLLs.Add("mujoco.dll");
        }
        // Libraries and SO for linux platform
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            string SoTargetPath = Path.Combine(MujocoLibLibPath, "Linux/libmujoco.so");
            PublicAdditionalLibraries.Add(SoTargetPath);
            System.Console.WriteLine($"SoTargetPath: {SoTargetPath}");
            RuntimeDependencies.Add(SoTargetPath); 
            PublicDelayLoadDLLs.Add("libmujoco.so");
        }
    }
}
