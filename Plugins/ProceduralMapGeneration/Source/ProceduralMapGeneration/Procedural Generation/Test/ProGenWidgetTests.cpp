// Fill out your copyright notice in the Description page of Project Settings.


#include "ProGenWidgetTests.h"

#include "Components/BoxComponent.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "Slate Widget/PluginSettings.h"

void UProGenWidgetTests::Initialize(ARoomActor* First, ARoomActor* Second)
{
	PluginSettings = GetDefault<UPluginSettings>();
	
	this->FirstRoom = First;
	this->SecondRoom = Second;
	AProceduralGen* ProGeneration = CastChecked<AProceduralGen>(PluginSettings->ProGenActor.Get()->GetDefaultObject());
	this->ProGen = ProGeneration;
}

void UProGenWidgetTests::MakeOverlapTest()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World) return;

	FirstRoom = World->SpawnActor<ARoomActor>(FirstRoom->GetClass(),FVector(0,0,0),ProGen->DefaultRotation);
	SecondRoom = World->SpawnActor<ARoomActor>(SecondRoom->GetClass(),DetermineSecondRoomSpawnLocation(),ProGen->DefaultRotation);
	PluginSettings->SceneCapActorInst->SetActorLocation(FirstRoom->GetActorLocation());
}

FVector UProGenWidgetTests::DetermineSecondRoomSpawnLocation()
{
	FVector Extends = FirstRoom->BoxComponent->GetScaledBoxExtent() * 4;
	FVector SecRoomOffset = FVector::Zero();
	
	switch (FirstRoom->ExitSocketDirection)
	{
	case HorizontalRight:
		SecRoomOffset.X = Extends.X;
		break;
	case HorizontalLeft:
		SecRoomOffset.X = -Extends.X;
		break;
	case VerticalUp:
		SecRoomOffset.Y = Extends.Y;
		break;
	case VerticalDown:
		SecRoomOffset.Y = -Extends.Y;
		break;
	default: ;
	}

	return SecRoomOffset;
}
