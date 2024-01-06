// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ProceduralMapGeneration/Procedural Generation/ProceduralGen.h"
#include "UObject/SoftObjectPtr.h"
#include "PluginSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Procedural Map Generation"))
class PROCEDURALMAPGENERATION_API UPluginSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	FSoftObjectPath Up;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	FSoftObjectPath Down;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	FSoftObjectPath Right;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	FSoftObjectPath Left;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	FSoftObjectPath NoExit;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	TSoftObjectPtr<UMaterialInterface> SceneCapMaterial;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	TSoftClassPtr<AActor> SceneCapActor;

	UPROPERTY(Config, EditAnywhere, Category= "My Plugin")
	TSoftClassPtr<AProceduralGen> ProGenActor;

	UPROPERTY()
	mutable TWeakObjectPtr<AActor> SceneCapActorInst;



};
