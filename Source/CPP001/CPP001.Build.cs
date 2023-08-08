// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CPP001 : ModuleRules
{
	public CPP001(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "PhysicsCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.AddRange(new string[] 
		{
			"CPP001/Public/Player", 
			"CPP001/Public/Components", 
			"CPP001/Public/Dev", 
			"CPP001/Public/Weapon",
			"CPP001/Public/UI",
			"CPP001/Public/Animations",
			"CPP001/Public/Pickups",
			"CPP001/Public/Weapon/Components",
			"CPP001/Public/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
