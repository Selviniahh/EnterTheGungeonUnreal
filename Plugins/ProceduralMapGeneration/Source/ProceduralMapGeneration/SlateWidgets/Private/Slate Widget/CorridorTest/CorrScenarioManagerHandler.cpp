// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Slate Widget/CorridorTest/CorrScenarioManagerHandler.h"

#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/PluginSettings.h"

void UCorrScenarioManagerHandler::Initialize()
{
	
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

ARoomActor* UCorrScenarioManagerHandler::SpawnAndVisualizeRoom(ARoomActor* Room, const FVector& SpawnLoc)
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
