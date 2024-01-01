// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
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

};
