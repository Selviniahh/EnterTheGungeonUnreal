// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CorrScenarioManagerHandler.generated.h"

class UPluginSettings;
class ARoomActor;
/**
 * 
 */
UCLASS()
class PROCEDURALMAPGENERATION_API UCorrScenarioManagerHandler : public UObject
{
	GENERATED_BODY()
	bool HandleTileSelection(ARoomActor* RoomToIgnore);
	void Initialize();
	AActor* MakeRayCast(AActor* RoomToIgnore);
	ARoomActor* SpawnAndVisualizeRoom(ARoomActor* Room, const FVector& SpawnLoc);


	//For tile selection
	UMaterialInterface* TileHoverMat;
	UMaterialInterface* TileUnhoverMat;
	UMaterialInterface* TileSelectMat;
	AActor* LastHitTile;
	TArray<AActor*> SelectedTiles;
	AActor* SceneCapInst;
	FVector RayCastEndLoc;
	UWorld* World;
	TArray<ARoomActor*> SpawnedRooms;
	const UPluginSettings* PlugSetting;
	ARoomActor* FirstRoom;
	ARoomActor* SecondRoom;
};
