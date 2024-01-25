// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/CorridorTest/CorrScenarioManagerWidget.h"

#include "SlateMaterialBrush.h"
#include "SlateOptMacros.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/CorridorTest/CorridorTestHandler.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SCorrScenarioManagerWidget::Construct(const FArguments& InArgs)
{
	FirstRoom = InArgs._FirstRoom;
	SecondRoom = InArgs._SecondRoom;
	PlugSetting = GetDefault<UPluginSettings>();

	if (UMaterialInterface* Material = PlugSetting->SceneCapMaterial.Get())
		SceneCapImgBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable

	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	PropertyTextFont.Size = 12;

	World = GEditor->GetEditorWorldContext().World();
	FlushPersistentDebugLines(World);

	//Access Scene capture component. THe reason not creating actor from C++, Scene capture component details are not exposed in BP editor
	SceneCapInst = PlugSetting->SceneCapActorInst.Get();
	TArray<USceneCaptureComponent2D*> SceneCapCompArray;
	SceneCapInst->GetComponents(SceneCapCompArray);

	FVector CenterLocation = PlugSetting->ProGenInst->Tiles[PlugSetting->ProGenInst->MapSizeX / 2][PlugSetting->ProGenInst->MapSizeY / 2].Location;
	SpawnAndVisualizeRoom(FirstRoom, CenterLocation);

	if (PlugSetting->TilePlaneActor.IsPending())
		PlugSetting->TilePlaneActor.LoadSynchronous();

	//Load other stuffs
	if (PlugSetting->TileHoverMaterial.IsPending())
		TileHoverMat = PlugSetting->TileHoverMaterial.LoadSynchronous();
	TileHoverMat = PlugSetting->TileHoverMaterial.Get();

	if (PlugSetting->TileSelectionMaterial.IsPending())
		TileSelectMat = PlugSetting->TileSelectionMaterial.LoadSynchronous();

	TileSelectMat = PlugSetting->TileSelectionMaterial.Get();
	TileActor = CastChecked<AActor>(PlugSetting->TilePlaneActor.Get()->GetDefaultObject());

	if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(FirstRoom->GetComponentByClass(UStaticMeshComponent::StaticClass())))
	{
		TileUnhoverMat = MeshComponent->GetMaterial(0);
	}

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

			//NOTE: 1. Start all corridor scenarios 
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			                      .Padding(FMargin(15, 5, 15, 5))
			[
				HorizontalField(
					{
						ConstructTextBlock(PropertyTextFont, FText::FromString("Not decided good enough yet")),
						ConstructButton(FText::FromString("Start Test"), [this]()
						{
							return FReply::Handled();
						}),
					})
			]

			//NOTE: 2. Undo all the tile selection etc
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			                      .Padding(FMargin(15, 5, 15, 5))
			[
				HorizontalField(
					{
						ConstructTextBlock(PropertyTextFont, FText::FromString("Unto all the spawned tiles")),
						ConstructButton(FText::FromString("Undo tiles"), [this]()
						{
							for (auto Tile : SpawnedTiles)
							{
								Tile->Destroy();
							}
							SpawnedLocations.Empty();
							return FReply::Handled();
						}),
					})
			]
		]
	];
}

ARoomActor* SCorrScenarioManagerWidget::SpawnAndVisualizeRoom(ARoomActor* Room, const FVector& SpawnLoc)
{
	//Spawn the first room first
	Room = World->SpawnActor<ARoomActor>(Room->GetClass(), SpawnLoc, PlugSetting->ProGenInst->DefaultRotation);
	SpawnedRooms.Add(Room);

	//now it's time to make box overlap
	PlugSetting->ProGenInst->VisualizeOverlaps = true;
	PlugSetting->ProGenInst->SetTilesBlocked(Room, SpawnLoc, PlugSetting->ProGenInst->DefaultRotation);
	PlugSetting->ProGenInst->SetSocketExclusion(Room, SpawnLoc);
	PlugSetting->ProGenInst->VisualizeTiles();

	return Room;
}

AActor* SCorrScenarioManagerWidget::MakeRayCast(AActor* RoomToIgnore)
{
	//Init raycast parameters
	int RaycastLength = 1000;
	FHitResult OutHit;
	FVector StartLocation = SceneCapInst->GetActorLocation();
	FVector EndLocation = StartLocation + (SceneCapInst->GetActorForwardVector() * RaycastLength);
	RayCastEndLoc = EndLocation;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(RoomToIgnore);
	AActor* CurrentHitActor = nullptr;

	if (GEditor->GetEditorWorldContext().World()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility))
	{
		CurrentHitActor = OutHit.GetActor();
	}

	return CurrentHitActor;
}

void SCorrScenarioManagerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (!HandleTileSelection(FirstRoom))
	{
		for (auto OffsetIndex : SpawnTileOffsets)
		{
			FIntPoint CurrentIndex = PlugSetting->ProGenInst->WorldToIndex(RayCastEndLoc) + OffsetIndex;
			if (SpawnedLocations.Contains(PlugSetting->ProGenInst->IndexToWorld(CurrentIndex.X, CurrentIndex.Y))) continue;;
			AActor* SpawnedTile = World->SpawnActor<AActor>(PlugSetting->TilePlaneActor.Get()->GetDefaultObject()->GetClass(), PlugSetting->ProGenInst->IndexToWorld(CurrentIndex.X, CurrentIndex.Y), FRotator(0, 0, 0));
			if (!SpawnedTile) return;
			SpawnedTile->AddActorLocalOffset(FVector(0, 0, 50));
			float ScaleFactor = PlugSetting->ProGenInst->TileSizeX / 100.0f; // Assuming TileSizeX is 16, this will be 0.16
			SpawnedTile->SetActorScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
			SpawnedTiles.Add(SpawnedTile);
			SpawnedLocations.Add(PlugSetting->ProGenInst->IndexToWorld(CurrentIndex.X, CurrentIndex.Y));
		}
	}

	if (FSlateApplication::Get().GetModifierKeys().IsAltDown()) //Is alt down
	{
		if (SelectedTiles.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("THere's no selected tile, select a tile with holding shift and try again"));
			return;
		}
		
		AActor* HitActor = MakeRayCast(FirstRoom);
		if (HitActor && HitActor->IsA(SecondRoom->GetClass()))
		{
			//Unblock the tiles of the room and destroy it
			for (auto Tile : SpawnedRooms.Last(0)->BlockedRoomTiles)
				PlugSetting->ProGenInst->Tiles[Tile.X][Tile.Y].Blocked = false;
			SpawnedRooms.Last(0)->Destroy();
		}

		//If the area is overlapping open dialog box and discard
		FIntPoint SpawnPoint = PlugSetting->ProGenInst->WorldToIndex(SelectedTiles.Last(0)->GetActorLocation());
		FVector SpawnLoc = PlugSetting->ProGenInst->IndexToWorld(SpawnPoint.X, SpawnPoint.Y);
		if (PlugSetting->ProGenInst->IsColliding(SecondRoom,SpawnLoc, PlugSetting->ProGenInst->DefaultRotation))
		{
			FMessageDialog::Open(EAppMsgType::Ok,FText::FromString("Second Room " + SecondRoom->GetClass()->GetName() + " is overlapping with the first selected room " + FirstRoom->GetClass()->GetName() + "Move away and try again"));
			return;
		}

		//Good job now let's check if last selected tile's direction corresponding with the selected room. This going to be hard
		//Alright I think I got it. Before I detected in for loop inside progen class the next selected area's direction when I making turn penalty. This goes same. When I select the first tile, it will compare the room's position and the tile's position
		//I already handled this case in progen I will initialize a new array and this will hold selected tiles' direction also I can this way if there's one tile gap, I can warn the user and restart again. But Before I really had better move everything to the handler class first
		Direction ExpectedDirection = SecondRoom->EnterSocketDirection;
		// if (ExpectedDirection)
		{
			
		}
		SpawnAndVisualizeRoom(SecondRoom, SpawnLoc);
	}

	UE_LOG(LogTemp, Display, TEXT("SPAWNEDTILES: %d"), SelectedTiles.Num());
}

SCorrScenarioManagerWidget::~SCorrScenarioManagerWidget()
{
	UE_LOG(LogTemp, Display, TEXT("sa"));
	for (auto Room : SpawnedRooms)
		Room->Destroy();

	for (auto Tile : SpawnedTiles)
		Tile->Destroy();
}

TSharedRef<SWidget> SCorrScenarioManagerWidget::ConstructTextBlock(FSlateFontInfo FontInfo, FText Text, const FSlateColor* Color)
{
	TSharedRef<STextBlock> TextBlock = SNew(STextBlock)
	   .Justification(ETextJustify::Center)
	   .Text(Text)
	   .Font(FontInfo)
		.Justification(ETextJustify::Center)
	   .RenderOpacity(0.5);

	if (Color) TextBlock.Get().SetColorAndOpacity(*Color);

	//Just wrapped in a button to make hover and unhover effect 
	return SNew(SButton)
	   .ButtonStyle(FCoreStyle::Get(), "NoBorder")
	   .HAlign(HAlign_Center)
	   .VAlign(VAlign_Center)
	   .OnHovered_Lambda([TextBlock]()
	                    {
		                    TextBlock->SetRenderOpacity(1.0); // Hover: increase opacity
	                    })
	   .OnUnhovered_Lambda([TextBlock]()
	                    {
		                    TextBlock->SetRenderOpacity(0.5); // Unhover: decrease opacity
	                    })
	[
		TextBlock
	];
}

TSharedRef<SButton> SCorrScenarioManagerWidget::ConstructButton(const FText& Text, const TFunction<FReply()>& ButtonClick)
{
	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	PropertyTextFont.Size = 12;
	TSharedPtr<STextBlock> TextBlock = SNew(STextBlock).Text(Text);

	TSharedRef<SButton> Button = SNew(SButton)
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	.OnClicked(FOnClicked::CreateLambda(ButtonClick))
	.ContentPadding(FMargin(5, 0, 5, 0))
	.Text(Text);


	Button->SetOnHovered(FSimpleDelegate::CreateLambda([Button]() { Button.Get().SetRenderOpacity(1); }));
	Button->SetOnUnhovered(FSimpleDelegate::CreateLambda([Button]() { Button.Get().SetRenderOpacity(0.5); }));
	return Button;
}

TSharedRef<SHorizontalBox> SCorrScenarioManagerWidget::HorizontalField(std::initializer_list<TSharedRef<SWidget>> Content)
{
	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);

	for (const auto& Element : Content)
	{
		HorizontalBox->AddSlot()
		             .AutoWidth()
		             .HAlign(HAlign_Fill)
		             .VAlign(VAlign_Fill)
		             .Padding(FMargin(10, 5, 10, 5))
		[
			Element
		];
	}

	return HorizontalBox;
}

bool SCorrScenarioManagerWidget::HandleTileSelection(ARoomActor* RoomToIgnore)
{
	AActor* CurrentHitActor = MakeRayCast(RoomToIgnore);
	if (CurrentHitActor && CurrentHitActor->ActorHasTag(FName("Tile")))
	{
		if (LastHitTile != CurrentHitActor)
		{
			// Revert the material of the last hit actor if tile changed and it weren't selected 
			if (LastHitTile && TileUnhoverMat)
			{
				UMeshComponent* LastMeshComponent = Cast<UMeshComponent>(LastHitTile->GetComponentByClass(UMeshComponent::StaticClass()));
				if (LastMeshComponent && !LastMeshComponent->ComponentTags.Contains("SelectedTile"))
				{
					LastMeshComponent->SetMaterial(0, TileUnhoverMat);
					if (SelectedTiles.Contains(LastHitTile))
						SelectedTiles.Remove(LastHitTile);
				}
				//If tile were selected but ctrl, is held, revert the material
				else if (FSlateApplication::Get().GetModifierKeys().IsControlDown() && LastMeshComponent->ComponentTags.Contains("SelectedTile"))
				{
					//WHen deselecting, if the selected tile deselected, remove from the array
					if (SelectedTiles.Contains(LastHitTile))
						SelectedTiles.Remove(LastHitTile);

					LastMeshComponent->SetMaterial(0, TileUnhoverMat);
				}
			}

			// Update the last hit actor and store its original material
			LastHitTile = CurrentHitActor;
			if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(CurrentHitActor->GetComponentByClass(UMeshComponent::StaticClass())))
			{
				//If shift pressed select the tile
				if (FSlateApplication::Get().GetModifierKeys().IsShiftDown()) //Is shift down
				{
					MeshComponent->SetMaterial(0, TileSelectMat);
					MeshComponent->ComponentTags.Add(FName("SelectedTile"));

					if (!SelectedTiles.Contains(CurrentHitActor))
						SelectedTiles.Add(CurrentHitActor);
				}
				else if (!MeshComponent->ComponentTags.Contains("SelectedTile")) //No shift selected, apply hover material
				{
					TileUnhoverMat = MeshComponent->GetMaterial(0);
					MeshComponent->SetMaterial(0, TileHoverMat);
				}
			}
		}
		return true;
	}
	else
	{
		// No hit or hit a different actor, revert the material of the last hit actor if the tile weren't selected
		if (LastHitTile && TileUnhoverMat)
		{
			UMeshComponent* MeshComponent = Cast<UMeshComponent>(LastHitTile->GetComponentByClass(UMeshComponent::StaticClass()));
			if (!MeshComponent->ComponentTags.Contains("SelectedTile"))
			{
				MeshComponent->SetMaterial(0, TileUnhoverMat);
			}
		}
		LastHitTile = nullptr;
		TileUnhoverMat = nullptr;
		return false;
	}
	return false;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
