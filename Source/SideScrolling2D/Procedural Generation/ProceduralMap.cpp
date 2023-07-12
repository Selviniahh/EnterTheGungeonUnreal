//Now Generate doors at correct Location
//1. First inside BP_Room specify the door locations with scene comp. 

#include "ProceduralMap.h"
#include "RoomActor.h"
#include "Door/DoorActor.h"


AProceduralMap::AProceduralMap()
{
	//We turned off this
	PrimaryActorTick.bCanEverTick = true;
}

void AProceduralMap::BeginPlay()
{
	Super::BeginPlay();
	GenerateMap();
}

void AProceduralMap::GenerateMap()
{
	FVector NextRoomLocation(0.0f, 0.0f, -245.0f);
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	const FActorSpawnParameters SpawnParams;

	// Spawn the first room at the starting location
	const ARoomActor* PreviousRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[0], NextRoomLocation, Rotation, SpawnParams);
	const ADoorActor* FirstDoorEnter = GetWorld()->SpawnActor<ADoorActor>(DoorBlueprint, PreviousRoom->DoorSocketEnter->GetComponentLocation(), Rotation, SpawnParams);


	for (int i = 1; i < NumberOfRooms; ++i)
	{
		const int RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
		// Spawn an exit door at the exit door location of the previous room
		const ADoorActor* DoorExit = GetWorld()->SpawnActor<ADoorActor>(DoorBlueprint, PreviousRoom->DoorSocketExit->GetComponentLocation(), Rotation, SpawnParams);
		
		// Calculate the location for the next room. This location will be next room's location
		NextRoomLocation = DoorExit->GetActorLocation();

		// Spawn the next room at the exit door location of the previous room
		const ARoomActor* NewRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation, SpawnParams);

		// Update the previous room to be the newly spawned room for the next iteration
		PreviousRoom = NewRoom;
	}
}

// Called every frame
void AProceduralMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

