// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/HandleTileSelection/BlockRoomWidget.h"
#include "SlateMaterialBrush.h"
#include "SlateOptMacros.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture2D.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/ProGenWidget.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/HandleTileSelection/BlockRoomWidgetHandler.h"
#include "UObject/UObjectGlobals.h"
#include "Widgets/SViewport.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/GlobalInputListener.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBlockRoomWidget::Construct(const FArguments& InArgs)
{
	FirstRoom = InArgs._FirstRoom;
	PluginSetting = GetDefault<UPluginSettings>();
	
	if (UMaterialInterface* Material = PluginSetting->SceneCapMaterial.Get())
		SceneCapImgBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable

	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	PropertyTextFont.Size = 12;

	TSharedPtr<STextBlock> LocalTextBlock;

	BlockRoomWidgetHandler = NewObject<UBlockRoomWidgetHandler>(GetTransientPackage());
	BlockRoomWidgetHandler->Initialize();

	ConstructButtonAndItsTextBox(PropertyTextFont, "If box component extends are incorrect", "Open " + FirstRoom->GetName(), [this]() mutable -> FReply
	{
		BlockRoomWidgetHandler->OpenSelectedRoomBP(FirstRoom);
		return FReply::Handled();
	});

	ChildSlot
	[
		// Parent Horizontal Box
		SNew(SHorizontalBox)

		// Image Slot
		+ SHorizontalBox::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .FillWidth(1.0)
		[
			SNew(SImage)
			.Image(SceneCapImgBrush.Get()) // Initialize member variable
		]

		// Vertical Box Slot for Buttons and TextBoxes
		+ SHorizontalBox::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .FillWidth(1.0)
		[
			SNew(SVerticalBox) // This Vertical Box will contain all the buttons and textboxes

			// First Button and TextBox
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			  .Padding(FMargin(0, 15, 0, 0))
			[
				ConstructButtonAndItsTextBox(PropertyTextFont, "If box component extends are incorrect", "Open " + FirstRoom->GetName(), [this]() -> FReply
				{
					return OpenSelectedRoom();
				})
			]

			// Second Button and TextBox
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			  .Padding(FMargin(0, 15, 0, 0))
			[
				ConstructButtonAndItsTextBox(PropertyTextFont, "Start exclusion", "Click me", [this]() -> FReply
				{
					return BlockRoomWidgetHandler->SpawnAllTiles(FirstRoom);
				})
			]

			// Third Button and TextBox
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			  .Padding(FMargin(0, 15, 0, 0))
			[
				ConstructButtonAndItsTextBox(PropertyTextFont, "Save exclusions", "Click me", [this]() -> FReply
				{
					//If tile not selected, warn the user  
					if (BlockRoomWidgetHandler->SelectedActors.IsEmpty())
					{
						FMessageDialog::Open(EAppMsgType::Ok,FText::FromString("no tile selected"));
						return FReply::Unhandled();
					}

					BlockRoomWidgetHandler->ChangeSelectedRoom(FirstRoom);

					//Reset SelectedActors. 
					BlockRoomWidgetHandler->SelectedActors.Empty();

					return FReply::Handled();
				})
			]

			// Additional buttons and textboxes can be added here, each in its own SVerticalBox::Slot()
		]
	];
}

void SBlockRoomWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SProGenWidget::HandleRenderViewMovement(InDeltaTime, SceneCapInst, SceneCapComp, CurrentVelocity);
	BlockRoomWidgetHandler->HandleTileSelection(FirstRoom);

	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}


FReply SBlockRoomWidget::OpenSelectedRoom()
{
	if (!FirstRoom) return FReply::Unhandled();

	BlockRoomWidgetHandler->OpenSelectedRoomBP(FirstRoom);

	return FReply::Handled();
}


//Now Handle the function binding
TSharedRef<SVerticalBox> SBlockRoomWidget::ConstructButtonAndItsTextBox(const FSlateFontInfo& PropertyTextFont, const FString& TextBoxText, const FString& ButtonText, const TFunction<FReply()>& ButtonClick)
{
	TSharedPtr<STextBlock> LocalTextBlock;

	TSharedRef<SVerticalBox> Slot = SNew(SVerticalBox)

		//2. slot textbox and button
		+ SVerticalBox::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .AutoHeight()
		  .Padding(FMargin(10, 0, 0, 0))
		[
			SNew(SHorizontalBox)

			//1. test button textbox
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			  .HAlign(HAlign_Center)
			[
				ConstructTextBlock(PropertyTextFont, FText::FromString(TextBoxText), LocalTextBlock) //Let's see how it will be null init
			] //"If box component extends are incorrect"

			//Make test button
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .VAlign(VAlign_Center)
			  .HAlign(HAlign_Center)
			  .Padding(FMargin(10, 0, 0, 0))
			[
				SNew(SButton)
				.OnClicked(FOnClicked::CreateLambda(ButtonClick))
				[
					ConstructTextBlock(PropertyTextFont, FText::FromString(ButtonText), TextBlock)
				]
			]
		];

	return Slot;
}

SBlockRoomWidget::~SBlockRoomWidget()
{
	for (auto& SpawnedTile : BlockRoomWidgetHandler->SpawnedTiles)
	{
		if (SpawnedTile)
			SpawnedTile->Destroy();
	}
}

TSharedRef<STextBlock> SBlockRoomWidget::ConstructTextBlock(FSlateFontInfo FontInfo, FText Text, TSharedPtr<STextBlock>& MemberTextBlock)
{
	MemberTextBlock = SNew(STextBlock)
	   .Justification(ETextJustify::Center)
	   .Text(Text)
	   .Font(FontInfo)
	   .RenderOpacity(0.5);

	return MemberTextBlock.ToSharedRef();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
