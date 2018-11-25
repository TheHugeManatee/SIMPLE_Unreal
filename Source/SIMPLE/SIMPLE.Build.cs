using System.IO;
using UnrealBuildTool;

public class SIMPLE : ModuleRules
{
	public SIMPLE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public"),
            }
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private"),
            }
            );


        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "InputCore",
                "RHI",
                "RenderCore",
                "OpenCV"
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

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



            //Delay - load the DLL, so we can load it from the right place first
            //PublicDelayLoadDLLs.Add("simple.dll");

            // Add a Runtime Dependency so the DLLs will be packaged correctly
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "SIMPLE", "bin", "simple.dll"));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "zeromq", "bin", "libzmq-mt-4_3_1.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            //PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "SIMPLE_world341.dylib"));
        }
    }
}
