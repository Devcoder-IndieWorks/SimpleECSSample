// Copyright Devcoder.
using UnrealBuildTool;
using System.Collections.Generic;

public class SimpleECSSampleTarget : TargetRules
{
	public SimpleECSSampleTarget( TargetInfo Target ) : base( Target )
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SimpleECSSample" } );
	}
}
