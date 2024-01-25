// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "Widgets/SCompoundWidget.h"

class UPluginSettings;
/**
 * 
 */
class PROCEDURALMAPGENERATION_API SCorrScenarioManagerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCorrScenarioManagerWidget) {}
	SLATE_ARGUMENT(ARoomActor*, FirstRoom);
	SLATE_ARGUMENT(ARoomActor*, SecondRoom);
	SLATE_END_ARGS()


	//Variables
	ARoomActor* FirstRoom;
	ARoomActor* SecondRoom;
	const UPluginSettings* PlugSetting;
	TSharedPtr<FSlateBrush> SceneCapImgBrush;
	UWorld* World;
	FVector CurrentInputVelocity;
	AActor* SceneCapInst;
	USceneCaptureComponent2D* SceneCapComp;
	AActor* TileActor;

	//For tile selection
	UMaterialInterface* TileHoverMat;
	UMaterialInterface* TileUnhoverMat;
	UMaterialInterface* TileSelectMat;
	AActor* LastHitTile;
	TArray<AActor*> SelectedTiles;
	TArray<AActor*> SpawnedTiles;
	FVector RayCastEndLoc;
	TArray<FVector> SpawnedLocations;
	TArray<ARoomActor*> SpawnedRooms;

	//Declare 3x3 grid of tiles
	TArray<FIntPoint> SpawnTileOffsets = {FIntPoint(0,0), FIntPoint(0,1), FIntPoint(-1,1), FIntPoint(-1,0),
		FIntPoint(-1,-1), FIntPoint(-0,-1), FIntPoint(1,-1),FIntPoint(1,0), FIntPoint(1,-1)}; 

	virtual ~SCorrScenarioManagerWidget() override;
	TSharedRef<SWidget> ConstructTextBlock(FSlateFontInfo FontInfo, FText Text, const FSlateColor* Color = nullptr);
	TSharedRef<SButton> ConstructButton(const FText& Text, const TFunction<FReply()>& ButtonClick);
	TSharedRef<SHorizontalBox> HorizontalField(std::initializer_list<TSharedRef<SWidget>> Content);
	bool HandleTileSelection(ARoomActor* RoomToIgnore);
	ARoomActor* SpawnAndVisualizeRoom(ARoomActor* Room, const FVector& SpawnLoc);
	AActor* MakeRayCast(AActor* RoomToIgnore);


	
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
};




