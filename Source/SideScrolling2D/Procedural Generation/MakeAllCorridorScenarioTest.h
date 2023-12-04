// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralGen.h"
#include "ProceduralGeneration.h"
#include "UObject/Object.h"
#include "MakeAllCorridorScenarioTest.generated.h"

class AProceduralGen;
class ARoomActor;
/**
 * 
 */
UCLASS()
class SIDESCROLLING2D_API UMakeAllCorridorScenarioTest : public UObject
{
	GENERATED_BODY()
public:
	UMakeAllCorridorScenarioTest();
	void Initialize(AProceduralGen* InProceduralGenInstance, TArray<TSubclassOf<ARoomActor>> FixedTwoRoomActors);
	void Start();
	void SpawnSecondRoom(const FVector& NextRoomLocation, ARoomActor*& NextRoom);
	void SpawnFirstRoom(const FVector& FirstRoomLoc);
	FTileStruct* FillGivenCorrPattern(TArray<FTileStruct*>& RoomList, TArray<FIntPoint>& CurrentPattern);
	void MakePathScenario(const FVector& FirstRoomLoc, const FVector& NextRoomLocation, TArray<FIntPoint>& CurrentPattern);
	bool MakeGivenPathFinding(TArray<FIntPoint>& CurrentPattern, ARoomActor* NextRoom);

	FVector RoundVectorToTilePos(const FIntPoint& BoxExtent)
	{
		
		int X = FMath::RoundToInt(static_cast<float>(BoxExtent.X * 2) / ProGen->TileSizeX) * ProGen->TileSizeX;
		int Y = FMath::RoundToInt(static_cast<float>(BoxExtent.Y * 2) / ProGen->TileSizeY) * ProGen->TileSizeY;
		return FVector(X, Y, 0);
	}

	UPROPERTY()
	AProceduralGen* ProGen;

	UPROPERTY()
	TArray<ARoomActor*> FixedRoomActor;

	FIntPoint LargestExtends = FIntPoint(0,0); 
};



