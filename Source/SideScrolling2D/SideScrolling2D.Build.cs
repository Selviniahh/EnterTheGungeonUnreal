// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SideScrolling2D : ModuleRules
{
	public SideScrolling2D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PaperZD", "PaperZDEditor", "Paper2D", "EnhancedInput", "UMG", "Blutility", "ProceduralMapGeneration"});

		PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
