// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralMapGeneration.h"

#include "ContentBrowserModule.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralMapGeneration/Slate Widget/GlobalInputListener.h"
#include "ProceduralMapGeneration/Slate Widget/ProGenWidget.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FProceduralMapGenerationModule"

void FProceduralMapGenerationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterWindow();
	InitCBMenuExtension();
	// FSlateApplication::Get().RegisterInputPreProcessor(TSharedPtr<IInputProcessor>(MakeShareable<new FMyInputProcessor()>));
	TSharedPtr<IInputProcessor> InputProcessor = MakeShared<FMyInputProcessor>();
	FSlateApplication::Get().RegisterInputPreProcessor(InputProcessor);
}

void FProceduralMapGenerationModule::ShutdownModule()
{
}

//Bind your own custom delegate to content browser module. 
void FProceduralMapGenerationModule::InitCBMenuExtension()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	//Retrieve all the custom menu extenders from the content browser module
	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserModuleMenuExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();

	//Bind your own custom delegate to content browser module. 
	ContentBrowserModuleMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FProceduralMapGenerationModule::CustomCBMenuExtender));
}

//Will be invoked when right clicked to content browser. From upper function, we already bound to content browser. This function won't create the menu itself.
//Instead it will just specify where the entity should be placed. After this function returned, the bound delegate will be invoked right away and that bound function will
//Specify exactly what the entity should be.
TSharedRef<FExtender> FProceduralMapGenerationModule::CustomCBMenuExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender = MakeShared<FExtender>();

	MenuExtender->AddMenuExtension(FName("Delete"), EExtensionHook::After, TSharedPtr<FUICommandList>(),
	                               FMenuExtensionDelegate::CreateRaw(this, &FProceduralMapGenerationModule::AddCBMenuEntry));
	return MenuExtender;
}

//Will be invoked right away after upper function returned. This function will create the actual menu itself.
void FProceduralMapGenerationModule::AddCBMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Make very cool Procedural Map label")),
		FText::FromString(TEXT("Make very cool Procedural Map for tool tip")),
		FSlateIcon(), FExecuteAction::CreateRaw(this, &FProceduralMapGenerationModule::OnProGenButtonClicked)
	);
}

//Will be invoked when the option itself is clicked. This function will just invoke the given name tab. But before trying to invoke, registering that tab is required. Below the function
void FProceduralMapGenerationModule::OnProGenButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FName("ProGen"));
}


//Register the window tab with given TabId. The bound delegate itself will be finally actual content of the window. 

void FProceduralMapGenerationModule::RegisterWindow()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName("ProGen"),
	FOnSpawnTab::CreateRaw(this, &FProceduralMapGenerationModule::OnSpawnProGenTab)).
	SetDisplayName(FText::FromString(TEXT("Procedural Map Generation")));
}

//Finally the actual slate. 

TSharedRef<SDockTab> FProceduralMapGenerationModule::OnSpawnProGenTab(const FSpawnTabArgs& SpawnTabArgs)
{
	
	TSharedRef<SProGenWidget> ProGenWidget = SNew(SProGenWidget)
		.Material(LoadMaterialFromPath(TEXT("/ProceduralMapGeneration/RenderTarget/M_UIRender.M_UIRender")))
		.SceneCapActor(GetSceneCapActor(TEXT("Blueprint'/ProceduralMapGeneration/RenderTarget/BP_RenderView.BP_RenderView_C'")));
	
	// Add the widget to the tab
	TSharedRef<SDockTab> NewTab = SNew(SDockTab)
		.TabRole(NomadTab)
		.OnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &FProceduralMapGenerationModule::OnTabClosed))
		.ContentPadding(30)
		[
			ProGenWidget
		];

	// Delay setting focus
		FSlateApplication::Get().SetUserFocus(0, ProGenWidget);

	return NewTab;
}

UMaterial* FProceduralMapGenerationModule::LoadMaterialFromPath(const FName& Path)
{
	if (Path == NAME_None) return nullptr;

	return Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, *Path.ToString()));
}

AActor* FProceduralMapGenerationModule::GetSceneCapActor(const FName& Path)
{
	if (Path == NAME_None) return nullptr;

	// Load the object as a UClass, not a UBlueprint
	UClass* ObjectClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *Path.ToString()));
	if (!ObjectClass) return nullptr;

	// Check if this class is a subclass of AActor
	if (!ObjectClass->IsChildOf(AActor::StaticClass())) return nullptr;

	// Spawn an instance of this actor class
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World) return nullptr;

	TArray<AActor*> SceneCapActors;
	UGameplayStatics::GetAllActorsOfClass(World,ObjectClass,SceneCapActors);
	if (SceneCapActors.IsEmpty())
	{
		return World->SpawnActor<AActor>(ObjectClass, FVector(0,0,1848), FRotator(-90,0,0));
	}
	else
	{
		return SceneCapActors[0];
	}
 }

void FProceduralMapGenerationModule::OnTabClosed(const TSharedRef<SDockTab> Tab)
{
	if (ShouldRemoveSceneCapActor)
	{
		GetSceneCapActor(TEXT("Blueprint'/ProceduralMapGeneration/RenderTarget/BP_RenderView.BP_RenderView_C'"))->Destroy();
	}
	UE_LOG(LogTemp, Display, TEXT("Tab closed"));
}
#undef LOCTEXT_NAMESPACE


IMPLEMENT_MODULE(FProceduralMapGenerationModule, ProceduralMapGeneration)