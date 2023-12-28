// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FProceduralMapGenerationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void RegisterWindow();
	void InitCBMenuExtension();
	TSharedRef<SDockTab> OnSpawnProGenTab(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<FExtender> CustomCBMenuExtender(const TArray<FString>& SelectedPaths);
	void AddCBMenuEntry(FMenuBuilder& MenuBuilder);
	void OnProGenButtonClicked();
	 void OnTabClosed(const TSharedRef<SDockTab> Tab);
	UMaterial* LoadMaterialFromPath(const FName& Path);
	/*If we don't have one spawn one and then return it's reference*/
	static AActor* GetSceneCapActor(const FName& Path);

	bool ShouldRemoveSceneCapActor = true;
	AActor* as = nullptr;

};
