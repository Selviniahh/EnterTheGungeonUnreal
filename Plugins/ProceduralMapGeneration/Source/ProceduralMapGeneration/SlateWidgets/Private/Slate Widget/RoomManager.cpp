// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/RoomManager.h"
#include "SlateMaterialBrush.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/ProGenWidget.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/HandleTileSelection/BlockRoomWidget.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/Test/ProGenWidgetTests.h"

class SBlockRoomWidget;
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRoomManager::Construct(const FArguments& InArgs)
{
	FirstRoom = InArgs._RoomFirst;
	SecondRoom = InArgs._RoomSecond;
	PluginSetting = GetDefault<UPluginSettings>();
	SceneCapInst = PluginSetting->SceneCapActorInst.Get();
	
	AllRoomTests = NewObject<UProGenWidgetTests>(GetTransientPackage(), UProGenWidgetTests::StaticClass());
	AllRoomTests->Initialize(FirstRoom,SecondRoom);

	if (UMaterialInterface* Material = PluginSetting->SceneCapMaterial.Get())
		SceneCapImgBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable

	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	PropertyTextFont.Size = 12;
	
	ButtonStyle = MakeShared<FButtonStyle>();
	ButtonStyle.Get()->SetNormal(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on
	ButtonStyle.Get()->SetHovered(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on
	ButtonStyle.Get()->SetPressed(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on

	//Access Scene capture component. THe reason not creating actor from C++, Scene capture component details are not exposed in BP editor
	TArray<USceneCaptureComponent2D*> SceneCapCompArray;
	SceneCapInst->GetComponents(SceneCapCompArray);
	SceneCapComp = SceneCapCompArray[0];
	TSharedPtr<STextBlock> LocalTextBlock;
	
	ChildSlot
	[
		//Parent
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		[
			SNew(SHorizontalBox)

			//1. Slot
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			  .FillWidth(1.0)
			[
				SNew(SImage)
				.Image(SceneCapImgBrush.Get()) // Initialize member variable)
			]

			+ SHorizontalBox::Slot()
			[
				SNew(SVerticalBox)

				//2. slot
				+ SVerticalBox::Slot()
				  .HAlign(HAlign_Fill)
				  .VAlign(VAlign_Fill)
				  .AutoHeight()
				  .Padding(FMargin(10,0,0,0))
				[
					SNew(SHorizontalBox)

					//1. test button textbox
					+ SHorizontalBox::Slot()
					  .AutoWidth()
					  .VAlign(VAlign_Center)
					  .HAlign(HAlign_Center)
					[
						ConstructTextBlock(PropertyTextFont, FText::FromString("Make Overlap Check"),LocalTextBlock) //Let's see how it will be null init
					]

					//Make test button
					+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						  .HAlign(HAlign_Center)
						  .Padding(FMargin(10,0,0,0))
					[
					SNew(SButton)
						.OnClicked(this, &SRoomManager::OnButtonVisBlockedClicked)
						.OnHovered(this, &SRoomManager::OnVisBlockedHovered, &TextBlock)
						.OnUnhovered(this, &SRoomManager::OnVisBlockedUnHovered, &TextBlock)
						[
							ConstructTextBlock(PropertyTextFont, FText::FromString("Make Test"),TextBlock)
						]
					]

					//Open Block selection widget room
					+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						  .HAlign(HAlign_Center)
						  .Padding(FMargin(10,0,0,0))
					[
					SNew(SButton)
						.OnClicked(this, &SRoomManager::OnButtonOpenTileSelectorWidget)
						.OnHovered(this, &SRoomManager::OnVisBlockedHovered, &TextBlock2)
						.OnUnhovered(this, &SRoomManager::OnVisBlockedUnHovered, &TextBlock2)
						[
							ConstructTextBlock(PropertyTextFont, FText::FromString("Make Test"), TextBlock2)
						]
					]
				]
			]
		]
	];
}

void SRoomManager::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SProGenWidget::HandleRenderViewMovement(InDeltaTime, SceneCapInst, SceneCapComp, CurrentVelocity);
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

TSharedRef<STextBlock> SRoomManager::ConstructTextBlock(FSlateFontInfo FontInfo, FText Text, TSharedPtr<STextBlock>& MemberTextBlock)
{
	MemberTextBlock = SNew(STextBlock)
	   .Justification(ETextJustify::Center)
	   .Text(Text)
	   .Font(FontInfo)
	   .RenderOpacity(0.5);

	return MemberTextBlock.ToSharedRef();
}

FReply SRoomManager::OnButtonVisBlockedClicked()
{
	ARoomActor* SpawnedFirstRoom = AllRoomTests->MakeOverlapTest();
	AllSpawnedRooms.Add(SpawnedFirstRoom);
	return FReply::Handled();
}

FReply SRoomManager::OnButtonOpenTileSelectorWidget()
{
	//Init the widget
	TSharedRef<SBlockRoomWidget> BlockRoomWidget = SNew(SBlockRoomWidget)
	.FirstRoom(AllSpawnedRooms[0]);

	//Create the widget as SWindow
	TSharedRef<SWindow> RoomManagerWindow = SNew(SWindow)
	.Title(FText::FromString(TEXT("Block tile selection for ") + FirstRoom->GetName()))
	.ClientSize(FVector2D(1920,1080)) //TODO: Later on for all window sizes, make what engine's window was already has
	.SupportsMaximize(true)
	.SupportsMinimize(true)
	[ //It's content
		BlockRoomWidget
	];

	FSlateApplication::Get().AddWindow(RoomManagerWindow);
	
	return FReply::Handled();
}

SRoomManager::~SRoomManager()
{
	FlushPersistentDebugLines(GEditor->GetEditorWorldContext().World());

	//Destroy all spawned rooms when the room manager widget closed by the user
	for (auto SpawnedRoom : AllSpawnedRooms)
	{
		SpawnedRoom->Destroy();
	}
}

#pragma region VisualizeBlocked


void SRoomManager::OnVisBlockedHovered(TSharedPtr<STextBlock>* MemberTextBlock)
{
	MemberTextBlock->Get()->SetRenderOpacity(1);
}

void SRoomManager::OnVisBlockedUnHovered(TSharedPtr<STextBlock>* MemberTextBlock)
{
	MemberTextBlock->Get()->SetRenderOpacity(0.5);
}

void SRoomManager::OnPressed(TSharedPtr<STextBlock>* MemberTextBlock)
{
	MemberTextBlock->Get()->SetRenderOpacity(1);
}

#pragma endregion


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
