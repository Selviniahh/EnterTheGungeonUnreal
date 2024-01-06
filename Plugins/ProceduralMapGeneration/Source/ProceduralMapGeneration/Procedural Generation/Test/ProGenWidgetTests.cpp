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

	FVector BoxComp = FirstRoom->BoxComponent->GetScaledBoxExtent() * 2;
	double MaxDouble = FMath::Max3(BoxComp.X, BoxComp.Y, BoxComp.Z);

	//TODO: I need to set render target exactly center of the room not the one at room's specified origin. Calculate the box comp center and set it to render target's location
	PluginSettings->SceneCapActorInst->SetActorLocation(FirstRoom->GetActorLocation() + FVector(0,0,MaxDouble));

	//now it's time to make box overlap  
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
