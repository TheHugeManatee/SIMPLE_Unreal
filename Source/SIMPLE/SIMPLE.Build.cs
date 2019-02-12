using System.IO;
using UnrealBuildTool;

public class SIMPLE : ModuleRules
{
	public SIMPLE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] { Path.Combine(ModuleDirectory, "Public"), });


        PrivateIncludePaths.AddRange(
            new string[] { Path.Combine(ModuleDirectory, "Private"), });


        PublicDependencyModuleNames.AddRange(
			new string[] { "Core", });
			
		PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "Projects",
            "InputCore",
            "RHI",
            "RenderCore",
            "OpenCV"
        });

        LoadSIMPLELib(Target);
    }

    public void LoadSIMPLELib(ReadOnlyTargetRules Target)
    {
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string SIMPLELibPath = Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "SIMPLE");

            //Add the import library
            PublicLibraryPaths.AddRange(
                new string[] {
                     Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "SIMPLE", "lib"),
                     Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "zeromq", "lib")
                });

            PublicAdditionalLibraries.Add("simple.lib");
            PublicAdditionalLibraries.Add("simple_msgs.lib");
            PublicAdditionalLibraries.Add("libzmq-mt-4_3_1.lib");
            PublicIncludePaths.AddRange(new string[] { 
                Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "SIMPLE", "include"),
                Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "zeromq", "include"),
                Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "flatbuffers", "include"),
            });


            // Add a Runtime Dependency so the DLLs will be packaged correctly
            // Note: SIMPLE cannot be delay-loaded due to the use of static variables, it seems. This means it has to be present
            // in the Binaries folder at Engine startup
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "Binaries", "Win64", "simple.dll"));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "Binaries", "Win64", "libzmq-mt-4_3_1.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            //PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "SIMPLE_world341.dylib"));
        }
    }
}
