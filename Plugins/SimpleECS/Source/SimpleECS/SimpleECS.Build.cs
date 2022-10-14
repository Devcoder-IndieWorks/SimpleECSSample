// Copyright Devcoder.
using UnrealBuildTool;

public class SimpleECS : ModuleRules
{
	public SimpleECS( ReadOnlyTargetRules Target ) : base( Target )
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = false;
		bLegacyPublicIncludePaths = false;
		CppStandard = CppStandardVersion.Cpp17;
		PrivatePCHHeaderFile = "Private/SimpleECSPCH.h";
		
		PrivateIncludePaths.AddRange(
		    new string[] {
				"SimpleECS/Private"
			} );
			
		PrivateDependencyModuleNames.AddRange(
		    new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore"
			} );
	}
}
