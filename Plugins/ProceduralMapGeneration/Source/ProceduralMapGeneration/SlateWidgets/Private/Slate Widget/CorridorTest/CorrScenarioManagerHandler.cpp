// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Slate Widget/CorridorTest/CorrScenarioManagerHandler.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/ProGenSubsystem.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"

void UCorrScenarioManagerHandler::Initialize(ARoomActor* InFirstRoom, ARoomActor* InSecondRoom)
{
	FirstRoom = InFirstRoom;
	SecondRoom = InSecondRoom;
	PlugSetting = GetDefault<UPluginSettings>();

	PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
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

	if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(FirstRoom->GetComponentByClass(UStaticMeshComponent::StaticClass())))
	{
		TileUnhoverMat = MeshComponent->GetMaterial(0);
	}
}

bool UCorrScenarioManagerHandler::HandleTileSelection(ARoomActor* RoomToIgnore)
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

AActor* UCorrScenarioManagerHandler::MakeRayCast(AActor* RoomToIgnore)
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

ARoomActor* UCorrScenarioManagerHandler::SpawnAndVisualizeRoom(ARoomActor*& Room, const FVector& SpawnLoc)
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

void UCorrScenarioManagerHandler::SpawnTiles()
{
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
}

FReply UCorrScenarioManagerHandler::HandleSecondRoomSpawning(const bool IsButtonClicked)
{
	if ((FSlateApplication::Get().GetModifierKeys().IsAltDown() && DoOnce) || IsButtonClicked) //Is alt down
	{
		DoOnce = false;

		if (SelectedTiles.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("THere's no selected tile, select a tile with holding shift and try again"));
			return FReply::Unhandled();
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
		FVector SpawnLoc = PlugSetting->ProGenInst->IndexToWorld(SpawnPoint.X, SpawnPoint.Y) + PlugSetting->ProGenInst->IndexToWorld(1, 1); 		// I need to know why I had to make offset in here OHHH that's because center of the tile is different than the room's enter position 

		if (PlugSetting->ProGenInst->IsColliding(SecondRoom, SpawnLoc, PlugSetting->ProGenInst->DefaultRotation))
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Second Room " + SecondRoom->GetClass()->GetName() + " is overlapping with the first selected room " +
				FirstRoom->GetClass()->GetName() + "Move away and try again"));
			
			return FReply::Unhandled();
		}

		TArray<FIntPoint> AllTiles;
		for (auto Tile : SelectedTiles)
			AllTiles.Add(PlugSetting->ProGenInst->WorldToIndex(Tile->GetActorLocation()));

		TArray<EDirection2> AllDirections;
		for (int i = 0; i < AllTiles.Num() - 1; ++i)
		{
			AllDirections.Add(GetTheTilesDirection(AllTiles[i], AllTiles[i + 1]));
		}

		//If the last selected tile is not matching with the second room's enter socket direction
		if (!PlugSetting->ProGenInst->LastCorrException(NormalDirToEDirection2(SecondRoom->EnterSocketDirection), AllDirections.Last()))
		{
			FMessageDialog::Open(EAppMsgType::Ok,FText::FromString("Last selected tile doesn't match with expected direction. Expected Direction: "
														   + UEnum::GetValueAsString(SecondRoom->EnterSocketDirection)));
			return FReply::Unhandled();
		}
		
		SpawnAndVisualizeRoom(SecondRoom, SpawnLoc);

		//Fill the selected tile points relative to the First Room's end soc index
		FVector FirstRoomEndSoc = FirstRoom->DoorSocketExit->GetComponentLocation();
		FIntPoint FirstRoomEndSocIndex = PlugSetting->ProGenInst->WorldToIndex(FirstRoomEndSoc);
		for (auto Tile : SelectedTiles)
		{
			FVector TileLoc = Tile->GetActorLocation();
			FIntPoint Index = PlugSetting->ProGenInst->WorldToIndex(Tile->GetActorLocation());
			FIntPoint Result = FirstRoomEndSocIndex - Index;
			SelectedTilePoints.Add(Result);
		}
	}
	return FReply::Handled();
}

void UCorrScenarioManagerHandler::Destruct()
{
	for (auto Room : SpawnedRooms)
		Room->Destroy();

	for (auto Tile : SpawnedTiles)
		Tile->Destroy();

	PlugSetting->ProGenInst->InitWorldTiles();
}

void UCorrScenarioManagerHandler::UndoTiles()
{
	Destruct();
	SpawnedLocations.Empty();
	FlushPersistentDebugLines(GEditor->GetEditorWorldContext().World());

	//Respawn the first room
	FVector CenterLocation = PlugSetting->ProGenInst->Tiles[PlugSetting->ProGenInst->MapSizeX / 2][PlugSetting->ProGenInst->MapSizeY / 2].Location;
	SpawnAndVisualizeRoom(FirstRoom, CenterLocation);
}

//TODO: Add your own subsystem ideology right here
void UCorrScenarioManagerHandler::SaveGivenPaths()
{
	UProGenSubsystem* ProGenSubsystem = GEditor->GetEditorSubsystem<UProGenSubsystem>();
	auto ScenarioDirectionPair = TPair<TEnumAsByte<Direction>, TEnumAsByte<Direction>>(FirstRoom->EnterSocketDirection, SecondRoom->ExitSocketDirection);
	ProGenSubsystem->CorridorTestScenarios.Add(ScenarioDirectionPair,SelectedTilePoints);
}
