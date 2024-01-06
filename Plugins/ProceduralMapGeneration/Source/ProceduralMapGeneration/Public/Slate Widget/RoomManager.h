// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UPluginSettings;
class UProGenWidgetTests;
class UMakeAllCorridorScenarioTest;
class ARoomActor;
/**
 * 
 */
class PROCEDURALMAPGENERATION_API SRoomManager : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRoomManager){}
	SLATE_ARGUMENT(ARoomActor*, RoomFirst)
	SLATE_ARGUMENT(ARoomActor*, RoomSecond)
	SLATE_END_ARGS()


	ARoomActor* FirstRoom;
	ARoomActor* SecondRoom;
	AActor* SceneCapInst;
	FVector CurrentVelocity; // Member variable to store current velocity


	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedRef<STextBlock> ConstructTextBlock(FSlateFontInfo FontInfo, FText Text);
	FReply OnButtonClicked();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	TSharedPtr<STextBlock> TextBlock;
	TSharedPtr<FSlateBrush> SceneCapImgBrush;
	UMakeAllCorridorScenarioTest* CorridorTest;
	UProGenWidgetTests* AllTests;
	int Multiplayer = 444;
	const UPluginSettings* PluginSetting;

#pragma region OverlapVisual
	void OnHovered();
	void OnUnHovered();
	void OnPressed();
#pragma endregion 
	TSharedPtr<FButtonStyle> ButtonStyle;

};
