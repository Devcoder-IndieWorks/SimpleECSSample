// Copyright Devcoder.
using UnrealBuildTool;

public class SimpleECSSample : ModuleRules
{
	public SimpleECSSample( ReadOnlyTargetRules Target ) : base( Target )
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;
		bLegacyPublicIncludePaths = false;
		CppStandard = CppStandardVersion.Cpp17;
		//PrivatePCHHeaderFile = "Private/SimpleECSSamplePCH.h";
		
		PrivateIncludePaths.AddRange(
		    new string[] {
				"SimpleECSSample/Private"
			} );
			
		// Unreal Engine Modules
		PublicDependencyModuleNames.AddRange(
		    new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore"
			} );
			
        // Project Plugin Modules
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "SimpleECS"
            } );

		PrivateDependencyModuleNames.AddRange( new string[] {} );
	}
}