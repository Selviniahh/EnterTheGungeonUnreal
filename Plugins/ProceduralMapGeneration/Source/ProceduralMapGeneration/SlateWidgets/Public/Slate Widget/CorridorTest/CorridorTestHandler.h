// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"
#include "UObject/Object.h"
#include "CorridorTestHandler.generated.h"

class UPluginSettings;
class ARoomActor;
/**
 * 
 */
UCLASS()
class PROCEDURALMAPGENERATION_API UCorridorTestHandler : public UObject
{
	GENERATED_BODY()
public:
	UCorridorTestHandler();
	void Initialize(ARoomActor* FirstSelectedRoom, ARoomActor* SecondSelectedRoom);
	void Start();
	void InitWorldChunks(TArray<TArray<FIntPoint>>& AllScenarios);

	UPROPERTY()
	const UPluginSettings* Setting;
	
	TArray<FIntPoint> VerticalUpToVerticalUp = {FIntPoint(0,-1),FIntPoint(0,-1), FIntPoint(0,-1), FIntPoint(0,-1),
		FIntPoint(0,-1), FIntPoint(0,-1), FIntPoint(0,-1),FIntPoint(0,-1), FIntPoint(0,-1), FIntPoint(0,-1)};

	TArray<FIntPoint> DownDown = {FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)};

	TArray<FIntPoint> DownDown2 = {FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)};

	TArray<FIntPoint> DownDown3 = {FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)
	,FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1),FIntPoint(0,1)};

	TArray<FIntPoint> VerticalUpTurnRightToVerticalUp = {FIntPoint(0,-1),FIntPoint(1,0),FIntPoint(1,0),FIntPoint(1,0)
	,FIntPoint(0,-1),FIntPoint(0,-1),FIntPoint(0,-1),FIntPoint(1,0),FIntPoint(1,0),FIntPoint(1,0),FIntPoint(1,0),FIntPoint(0,-1),
		FIntPoint(0,-1),FIntPoint(0,-1)};

	TArray<FIntPoint> VerticalUpTurnLeftToVerticalUp = {FIntPoint(0,-1),FIntPoint(0,-1),FIntPoint(-1,0),FIntPoint(-1,0),FIntPoint(-1,0),FIntPoint(0,-1),
	FIntPoint(0,-1),FIntPoint(0,-1),FIntPoint(-1,0),FIntPoint(-1,0),FIntPoint(-1,0),FIntPoint(-1,0),FIntPoint(0,-1),FIntPoint(0,-1),FIntPoint(0,-1)};

	
	UPROPERTY()
	ARoomActor* FirstRoom;
	UPROPERTY()
	ARoomActor* SecondRoom;

	UPROPERTY()
	TArray<ARoomActor*> FirstSecRoom;

	TArray<FVector> CenterOfEachChunk;
	TArray<FVector> CurrChunkActorLocs;
	FIntPoint LargestExtends = FIntPoint(0,0);

	UPROPERTY()
	UWorld* World;

	void MakePathScenario(const FVector& FirstRoomLoc, FVector& NextRoomLocation, TArray<FIntPoint>& CurrentPattern);
	void SpawnSecondRoom(const FVector& NextRoomLocation, ARoomActor*& NextRoom);
	void SpawnFirstRoom(const FVector& FirstRoomLoc);
	bool MakeGivenPathFinding(TArray<FIntPoint>& CurrentPattern, ARoomActor* NextRoom, const FVector& NextRoomLoc, const FVector& FirstRoomLoc);
	FTileStruct* FillGivenCorrPattern(TArray<FTileStruct*>& RoomList, TArray<FIntPoint>& CurrentPattern);


	FVector RoundBoxExtentToNearestTileSize(const FIntPoint& BoxExtent)
	{
		int X = FMath::RoundToInt(static_cast<float>(BoxExtent.X * 2) / Setting->ProGenInst->TileSizeX) * Setting->ProGenInst->TileSizeX;
		int Y = FMath::RoundToInt(static_cast<float>(BoxExtent.Y * 2) / Setting->ProGenInst->TileSizeY) * Setting->ProGenInst->TileSizeY;
		return FVector(X, Y, 0);
	}

	void RoundNearestTilePos(FVector& VectorToRound)
	{
		int X = FMath::RoundToInt(static_cast<float>(VectorToRound.X) / Setting->ProGenInst->TileSizeX) * Setting->ProGenInst->TileSizeX;
		int Y = FMath::RoundToInt(static_cast<float>(VectorToRound.Y) / Setting->ProGenInst->TileSizeY) * Setting->ProGenInst->TileSizeY;
		VectorToRound = FVector(X, Y, 0);
	}
};
