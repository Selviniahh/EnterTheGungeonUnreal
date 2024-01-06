﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMapGeneration/Public/Slate Widget/ProGenWidget.h"

#include "EngineUtils.h"
#include "ProceduralMapGeneration/Public/Slate Widget/GlobalInputListener.h"
#include "ProceduralMapGeneration/Public/Slate Widget/PluginSettings.h"
#include "ProceduralMapGeneration/Public/Slate Widget/PopUpButton.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Materials/MaterialInterface.h"
#include "ProceduralMapGeneration/Procedural Generation/ProceduralGen.h"
#include "Widgets/Layout/SScrollBox.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "Slate Widget/RoomManager.h"
#include "Widgets/Views/SListView.h"
#include "Styling/SlateBrush.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

/*Couldn't handle matrix*/


void SProGenWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	SceneCapActor = InArgs._SceneCapActor;

	//Set the slate window focus
	FSlateApplication::Get().SetKeyboardFocus(SharedThis(this), EFocusCause::SetDirectly);

	//Load the material
	if (UMaterialInterface* Material = InArgs._Material)
		MaterialBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable

	//Set the fonts 
	FSlateFontInfo TitleTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 30;
	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 12;


	//Access to the progen actor if progen instance is dragged to the scene
	AProceduralGen* ProceduralGen = nullptr;
	for (TActorIterator<AProceduralGen> Actor(GEditor->GetEditorWorldContext().World()); Actor; ++Actor)
	{
		ProceduralGen = *Actor;
	}
	for (auto RoomDesign : ProceduralGen->RoomDesigns)
	{
		ARoomActor* RoomActor = Cast<ARoomActor>(RoomDesign->GetDefaultObject());
		ProGenRooms.Add(RoomActor);
	}
	
	//Assign plugin settings
	PluginSetting = GetDefault<UPluginSettings>();

	//Init button slate
	TSharedRef<SPopUpButton> PopUpButton = SNew(SPopUpButton);

	//Init RowStyle
	TSharedPtr<FTableRowStyle> DefaultTableRowStyle = MakeShared<FTableRowStyle>(FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"));
	for (auto RoomActor : ProGenRooms)
	{
		RowStyle.Add(RoomActor.Get()->GetName(),DefaultTableRowStyle);
	}
	
	ChildSlot
	[
		// Top-Level Vertical Box
		SNew(SVerticalBox)

		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			ConstructMenuAnchor(PopUpButton)
		]
		
		// TextBlock Slot
		+ SVerticalBox::Slot()
		  .AutoHeight() // Adjust as needed for your text size
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		  .Padding(FMargin(0, 10, 0, 15))
		[
			SNew(STextBlock)
		.Text(FText::FromString(TEXT("Procedural Map Generation")))
		.Justification(ETextJustify::Center)
		.Font(TitleTextFont) // Set font size to 24 and use bold weight
		]

		// HorizontalBox Slot
		+ SVerticalBox::Slot()
		.FillHeight(1) // Takes remaining space
		[
			SNew(SHorizontalBox)

			// Left Section (VerticalBox with Image)
			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Fill) // Adjust width ratio as needed
			  .HAlign(HAlign_Fill) // Adjust width ratio as needed
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				  .VAlign(VAlign_Fill)
				  .HAlign(HAlign_Fill)
				[
					SNew(SImage)
					.Image(MaterialBrush.Get())
				]
			]

			// Right Section (VerticalBox with TextBlocks and TextBoxes)
			+ SHorizontalBox::Slot()
			  .VAlign(VAlign_Fill)
			  .HAlign(HAlign_Fill) 
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					ConstructListView()
				]
			]
		]
	];
}

void SProGenWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	Geometry = AllottedGeometry;
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	//Set Scene Capture location
	FKey MyKey = FMyInputProcessor::PressedKey;
	FVector Direction = FVector::ZeroVector;
	if (MyKey == EKeys::W) Direction = FVector(Multiplayer, 0, 0);
	else if (MyKey == EKeys::S) Direction = FVector(-Multiplayer, 0, 0);
	else if (MyKey == EKeys::A) Direction = FVector(0, -Multiplayer, 0);
	else if (MyKey == EKeys::D) Direction = FVector(0, Multiplayer, 0);
	else if (MyKey == EKeys::Q) Direction = FVector(0, 0, -Multiplayer);
	else if (MyKey == EKeys::E) Direction = FVector(0, 0, Multiplayer);

	if (MyKey == EKeys::F)
	{
		MenuAnchor->SetIsOpen(true);
	}

	if (SceneCapActor && Direction != FVector::ZeroVector)
	{
		FVector CurrentLocation = SceneCapActor->GetActorLocation();
		FVector TargetLocation = CurrentLocation + Direction;
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, InDeltaTime, 99); // InterpSpeed is a float determining how fast to move
		SceneCapActor->SetActorLocation(NewLocation, true);
	}
	
	//Reset the key at the end so I can make actions per press 
	FMyInputProcessor::PressedKey = FKey();
}

TSharedRef<SListView<TWeakObjectPtr<ARoomActor>>> SProGenWidget::ConstructListView()
{
	ConstructedAssetListView = SNew(SListView<TWeakObjectPtr<ARoomActor>>)
	.ListItemsSource(&ProGenRooms)
	.OnGenerateRow(this, &SProGenWidget::OnGenerateListViewRow)
	.OnSelectionChanged(SharedThis(this), &SProGenWidget::OnSelectionChanged);
	
	return ConstructedAssetListView.ToSharedRef();
}

TSharedRef<ITableRow> SProGenWidget::OnGenerateListViewRow(TWeakObjectPtr<ARoomActor> RoomActor, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!RoomActor.IsValid()) return SNew(STableRow<TWeakObjectPtr<ARoomActor>>, OwnerTable);
	SetDirectionMaps(RoomActor);

	HighlightAvailableRoomRows(RoomActor);
	
	TSharedRef<STableRow<TWeakObjectPtr<ARoomActor>>> ListViewRowWidget = SNew(STableRow<TWeakObjectPtr<ARoomActor>>, OwnerTable)
		.Style(RowStyle[RoomActor->GetName()].Get())
		[
			SNew(SHorizontalBox)

			//First slot for ActorName
			+ SHorizontalBox::Slot()
			  .Padding(FMargin(10, 10, 10, 10))
			  .HAlign(HAlign_Center)
			  .VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
				.Text(FText::FromString(RoomActor->GetName()))
				.Justification(ETextJustify::Center)
				]
			]

			//Second slot for two image
			+ SHorizontalBox::Slot()
			  .Padding(FMargin(10, 10, 10, 10))
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				  .AutoWidth() // Use AutoWidth to size the slot to the content
				  .VAlign(VAlign_Center) // Vertically center the image in the slot
				  .HAlign(HAlign_Center) // Horizontally center the image in the slot
				  .Padding(FMargin(0,0,10,0))
				[
					SNew(SImage)
					.Image(SlateEnterBrushMap[RoomActor.Get()->GetName()].Get())
				]
				+ SHorizontalBox::Slot()
				  .AutoWidth() // Similarly, use AutoWidth for the second image
				  .VAlign(VAlign_Center) // Vertically center the image
				  .HAlign(HAlign_Center) // Horizontally center the image
				  .Padding(FMargin(0,0,10,0))
				[
					SNew(SImage)
					.Image(SlateExitBrushMap[RoomActor->GetName()].Get())
				]
			]

			//Third slot for Tested Text and button
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .HAlign(HAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Tested"))
				]

				+ SHorizontalBox::Slot()
				  .Padding(FMargin(6, 0, 0, 0))
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				  .HAlign(HAlign_Center)
				[
					SNew(SCheckBox)
					.IsEnabled(false)
				]
			]

			//Fourth slot for Make test textbox and button (I am not sure to entire delete here) 
			+ SHorizontalBox::Slot()
			  .Padding(FMargin(10, 10, 10, 10))
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				  .AutoWidth()
				  .VAlign(VAlign_Center)
				[
					SNew(SButton)
				.OnClicked(this, &SProGenWidget::OnButtonClicked)
				.Text(FText::FromString(TEXT("Make Test")))
				.Visibility(this,&SProGenWidget::MakeTestButtonVisibility,RoomActor)
				]
			]
		];
	
	return ListViewRowWidget;
}

void SProGenWidget::HighlightAvailableRoomRows(TWeakObjectPtr<ARoomActor> RoomActor)
{
	if (ConstructedAssetListView.Get()->GetNumItemsSelected() == 1)
	{
		Direction FirstRoomExitSocDir = ConstructedAssetListView.Get()->GetSelectedItems()[0]->ExitSocketDirection;
		Direction ExpectedDirection = AProceduralGen::ExpectedDirection(FirstRoomExitSocDir);

		if (RoomActor->EnterSocketDirection == ExpectedDirection)
		{
			//Highlight the row
			FTableRowStyle* HighlightStyle = RowStyle[RoomActor->GetName()].Get();
			FSlateColor HighlightColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.8f, 0.3f)); // Light yellow with some transparency

			HighlightStyle->SetEvenRowBackgroundBrush(FSlateColorBrush(HighlightColor));
			HighlightStyle->SetOddRowBackgroundBrush(FSlateColorBrush(HighlightColor));
			HighlightStyle->SetEvenRowBackgroundHoveredBrush(FSlateColorBrush(HighlightColor));
			HighlightStyle->SetOddRowBackgroundHoveredBrush(FSlateColorBrush(HighlightColor));	
		}
	}
	else //Reset to default
	{
		TSharedPtr<FTableRowStyle> NewStyle = MakeShared<FTableRowStyle>(FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"));
		RowStyle[RoomActor->GetName()] = NewStyle;
	}
}

/*if first selected element changed, undo all highlights*/
void SProGenWidget::OnSelectionChanged(TWeakObjectPtr<ARoomActor> RoomActor, ESelectInfo::Type SelectedType)
{
	TSharedPtr<FTableRowStyle> NewStyle = MakeShared<FTableRowStyle>(FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"));
	TWeakObjectPtr<ARoomActor> CurrentFirstSelectedItem = ConstructedAssetListView.Get()->GetSelectedItems().Num() > 0 ? ConstructedAssetListView.Get()->GetSelectedItems()[0] : nullptr;
	if (PreviousFirstSelectedItem != CurrentFirstSelectedItem)
	{
		for (auto& StyleEntry : RowStyle)
		{
			 StyleEntry.Value = MakeShared<FTableRowStyle>(FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"));
		}
		
		//Assign Previous selected one
		PreviousFirstSelectedItem = CurrentFirstSelectedItem;
	}
	ConstructedAssetListView.Get()->RebuildList();
}

TSharedRef<SHorizontalBox> SProGenWidget::ConstructTextInput(const FText& Text, const FText& HintText, const FSlateFontInfo& PropertyTextFont, const FOnTextChanged& OnTextChangedDelegate)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .HAlign(HAlign_Center)
		  .Padding(FMargin(15, 0, 15, 0))
		[
			SNew(STextBlock)
					.Text(Text)
					.Font(PropertyTextFont)
		]

		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .HAlign(HAlign_Center)
		[
			SNew(SEditableTextBox)
					.Font(PropertyTextFont)
					.HintText(HintText)
					.OnTextChanged(OnTextChangedDelegate)
		];
}

EVisibility SProGenWidget::MakeTestButtonVisibility(TWeakObjectPtr<ARoomActor> SelectedRoom) const
{
	if (ConstructedAssetListView.Get()->GetNumItemsSelected() == 2 && ConstructedAssetListView.Get()->GetSelectedItems()[1] == SelectedRoom)
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Hidden;
	}
}

//TODO: If the directions are incorrect, Pop up message box
FReply SProGenWidget::OnButtonClicked()
{
	/*If selection is incorrect open msg dialog box*/
	Direction FirstRoomExitSocDir = ConstructedAssetListView.Get()->GetSelectedItems()[0]->ExitSocketDirection;
	Direction SecRoomEnterSocDir = ConstructedAssetListView.Get()->GetSelectedItems()[1]->EnterSocketDirection;
	Direction ExpectedDirection = AProceduralGen::ExpectedDirection(FirstRoomExitSocDir);
	if (SecRoomEnterSocDir != ExpectedDirection)
	{
		FString FirstRoomExitSocDirStr = UEnum::GetValueAsString(FirstRoomExitSocDir);
		FString SecRoomEnterSocDirStr = UEnum::GetValueAsString(SecRoomEnterSocDir);
		FString ExpectedDirectionStr = UEnum::GetValueAsString(ExpectedDirection);
		FText Message = FText::FromString("Incorrect Test Selection. \n\nFirst Room's exit socket direction is " + FirstRoomExitSocDirStr + "\n"
		"Second Room's enter socket direction is " + SecRoomEnterSocDirStr + "\n"
		"Second Selected room expected direction is: " + ExpectedDirectionStr);
		FMessageDialog::Open(EAppMsgType::Ok,Message);
	}
	else
	{
		const FName TabName = FName(TEXT("RoomManagerTab")); // Unique name for the tab identifier
		if (!FGlobalTabmanager::Get()->HasTabSpawner(TabName))
			{
				FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& SpawnTabArgs)
				{
					return SNew(SDockTab)
					.TabRole(NomadTab)
					[
						SNew(SRoomManager)
					];
				}))
				.SetDisplayName(FText::FromString("RoomManagerTab"));
			}

		FGlobalTabmanager::Get()->TryInvokeTab(FName("RoomManagerTab"));
	}

	


	
	// TArray<TWeakObjectPtr<ARoomActor>> SelectedRooms = ConstructedAssetListView.Get()->GetSelectedItems();
	// if (SelectedRooms.Num() < 2)
	// {
	// 	const FName TabName = FName(TEXT("RoomManagerTab")); // Unique name for the tab identifier
	//
	// 	if (!FGlobalTabmanager::Get()->HasTabSpawner(TabName))
	// 	{
	// 		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateLambda([SelectedRooms, this](const FSpawnTabArgs& SpawnTabArgs)
	// 		{
	// 			return SNew(SDockTab)
	// 			.TabRole(NomadTab)
	// 			[
	// 				SNew(SRoomManager)
	// 			];
	// 		}))
	// 		.SetDisplayName(FText::FromString("RoomManagerTab"));
	// 	}
	//
	// 	FGlobalTabmanager::Get()->TryInvokeTab(FName("RoomManagerTab"));
	// }
	return FReply::Handled();
}

void SProGenWidget::SetDirectionMaps(TWeakObjectPtr<ARoomActor> RoomActor)
{
	FSoftObjectPath DirPath;
	switch (RoomActor->EnterSocketDirection)
	{
	case HorizontalRight:
		DirPath = PluginSetting->Right;
		break;
	case HorizontalLeft:
		DirPath = PluginSetting->Left;
		break;
	case VerticalUp:
		DirPath = PluginSetting->Up;
		break;
	case VerticalDown:
		DirPath = PluginSetting->Down;
		break;
	default: ;
	}
	TSharedPtr<FSlateBrush> SlateBrush = MakeShared<FSlateBrush>();
	if (UTexture2D* TextureRaw = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *DirPath.ToString())))
	{
		SlateBrush.Get()->SetResourceObject(TextureRaw);
		SlateBrush.Get()->ImageSize = FVector2D(16,16);
		SlateBrush.Get()->DrawAs = ESlateBrushDrawType::Image;
		SlateBrush.Get()->ImageType = ESlateBrushImageType::FullColor;
	}
	
	SlateEnterBrushMap.Add(RoomActor.Get()->GetName(),SlateBrush);
	
	FSoftObjectPath DirPathEnd;
	switch (RoomActor->ExitSocketDirection)
	{
	case HorizontalRight:
		DirPathEnd = PluginSetting->Right;
		break;
	case HorizontalLeft:
		DirPathEnd = PluginSetting->Left;
		break;
	case VerticalUp:
		DirPathEnd = PluginSetting->Up;
		break;
	case VerticalDown:
		DirPathEnd = PluginSetting->Down;
		break;
	default: ;
	}
	TSharedPtr<FSlateBrush> SlateBrushEnd = MakeShared<FSlateBrush>();
	if (UTexture2D* TextureRaw = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *DirPathEnd.ToString())))
	{
		SlateBrushEnd.Get()->SetResourceObject(TextureRaw);
		SlateBrushEnd.Get()->ImageSize = FVector2D(16,16);
		SlateBrushEnd.Get()->DrawAs = ESlateBrushDrawType::Image;
		SlateBrushEnd.Get()->ImageType = ESlateBrushImageType::FullColor;
	}
	SlateExitBrushMap.Add(RoomActor.Get()->GetName(),SlateBrushEnd);
}

#pragma region unmanaged
TSharedRef<SMenuAnchor> SProGenWidget::ConstructMenuAnchor(const TSharedRef<SPopUpButton>& PopUpButton)
{
	MenuAnchor = SNew(SMenuAnchor)
	   .MenuContent(PopUpButton)
		.Placement(MenuPlacement_ComboBox)
		.FitInWindow(true)
		.RenderTransform(SharedThis(this),&SProGenWidget::SetPopUpLocation);

	return MenuAnchor.ToSharedRef();
}

TOptional<TTransform2<float>> SProGenWidget::SetPopUpLocation() const
{
	// Get the absolute mouse cursor position.
	FVector2D MousePos = FSlateApplication::Get().GetCursorPos();
	FVector2D LocalMousePos = Geometry.AbsoluteToLocal(MousePos);
	return TTransform2<float>(LocalMousePos);
}
#pragma endregion unmanaged

END_SLATE_FUNCTION_BUILD_OPTIMIZATION