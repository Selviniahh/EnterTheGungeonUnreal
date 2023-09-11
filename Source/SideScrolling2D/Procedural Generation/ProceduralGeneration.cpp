//TODO: IF IT'S LARGE ROOM MAKE -16 FOR 4 DIRECTIONS. 
#include "ProceduralGeneration.h"
#include <stack>
#include "ProceduralMap.h"
#include "RoomActor.h"
#include "Components/BoxComponent.h"
#include "UObject/UnrealTypePrivate.h"


// Sets default values
AProceduralGeneration::AProceduralGeneration()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned

void AProceduralGeneration::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Delayer;
	GetWorldTimerManager().SetTimer(Delayer, this, &AProceduralGeneration::GenerateMap, 0.1f, false);

}


void AProceduralGeneration::ConnectRoomsWithCorridors()
{
	for (FRoomConnection& Connection : RoomConnections)
	{
		FIntPoint StartIndex = WorldToIndex(Connection.StartPoint);

		// if (VisualizeEnterAndExitPathStartTile)
		// {
		// 	DrawDebugBox(GetWorld(),Tiles[StartIndex.X + Connection.PathStartOffset.X][StartIndex.Y + Connection.PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		// }
		
		FIntPoint EndIndex = WorldToIndex(Connection.EndPoint);

		// if (VisualizeEnterAndExitPathStartTile)
		// {
		// 	DrawDebugBox(GetWorld(),Tiles[EndIndex.X + Connection.PathEndOffset.X][EndIndex.Y + Connection.PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		// }
		// Find a path from StartIndex to EndIndex:
		if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y,Connection.PathStartOffset,Connection.PathEndOffset,SpawnCorridor, Connection.MaxCheckAmount))
		{
			for (int x = 0; x < MapSizeX; ++x)
			{
				for (int y = 0; y < MapSizeY; ++y)
				{
					Tiles[x][y].Visited = false; 
				}
			}
			FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y,Connection.PathStartOffset,Connection.PathEndOffset,SpawnCorridor, Connection.MaxCheckAmount);
		}
	}
	RoomConnections.Empty();
}

void AProceduralGeneration::MakeSideBranchFromLargeRoom()
{
	for (const auto LargeRoom : LargeRooms)
	{
		TArray<USceneComponent*> Sockets;
		LargeRoom->GetComponents<USceneComponent*>(Sockets);
		int SpawnCounter = 0;
	
		for (auto Socket : Sockets)
		{
			TArray<FName> AllTags = Socket->ComponentTags;
			if (!AllTags.Contains("Enter") && !AllTags.Contains("Exit") && !AllTags.IsEmpty())
			{
				FName SceneTag = Socket->ComponentTags[0];
				LastSpawnedRoom = nullptr;
				ARoomActor* SpawnedFirstRoom = SpawnFirstBranchRoom(ExpectedTag(SceneTag), Socket->GetComponentLocation());
				NumOfSideBranchRoom++;
				
				if (SpawnedFirstRoom->ActorHasTag("LargeRoom"))
				{
					LargeRooms.Add(SpawnedFirstRoom);
				}
				while (SpawnCounter < BranchLength && NumOfSideBranchRoom < MaxSideBranchCount && LastSpawnedRoom)
				{
					ARoomActor* SpawnedBranchRoom = SpawnBranchRoom(ExpectedTag(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]), SpawnCounter);
					NumOfSideBranchRoom++;
					if (SpawnedBranchRoom->ActorHasTag("LargeRoom"))
					{
						LargeRooms.Add(SpawnedBranchRoom);
					}
					SpawnCounter++;
				}
				SpawnCounter = 0;
			}
		}
		LargeRooms.Remove(LargeRoom);

	}
	
	if (!LargeRooms.IsEmpty())
	{
		MakeSideBranchFromLargeRoom();
	}
}

void AProceduralGeneration::MakeBranchConnection()
{
	// Step 1: Store all the LargeRooms in an array
	TArray<ARoomActor*> AvailableLargeRooms = LargeRooms;

	// Step 2: Store valid scene comps (Sockets) in another array
	TArray<USceneComponent*> AvailableSockets;

	// Iterate through each LargeRoom to check each of its scene comps
	for (auto CurrentRoom : AvailableLargeRooms)
	{
		TArray<USceneComponent*> CurrentRoomSockets;
		CurrentRoom->GetComponents<USceneComponent*>(CurrentRoomSockets);

		// For each scene comp of the current LargeRoom
		for (auto CurrentSocket : CurrentRoomSockets)
		{
			FString SocketName = CurrentSocket->GetName();
			if (SocketName == "RootScene" || SocketName == "TileMapComponent" || SocketName == "BoxComponent" || SocketName == "DoorSocketEnter") continue;
			
			// Try to find a path to each scene comp of all other LargeRooms. NOTE: It can be same room.
			for (auto OtherRoom : AvailableLargeRooms)
			{
				TArray<USceneComponent*> OtherRoomSockets;
				OtherRoom->GetComponents<USceneComponent*>(OtherRoomSockets);

				// For each scene comp in the other LargeRooms. NOTE: It can be same room but different scene comp.
				for (auto OtherSocket : OtherRoomSockets)
				{
					FString OtherSocketName = OtherSocket->GetName();
					if (OtherSocketName == "RootScene" || OtherSocketName == "TileMapComponent" || OtherSocketName == "BoxComponent" || OtherSocketName == "DoorSocketEnter" || OtherSocket == CurrentSocket) continue;
					FIntPoint Start = WorldToIndex(CurrentSocket->GetComponentLocation());
					FIntPoint End = WorldToIndex(OtherSocket->GetComponentLocation());

					//Based on The CurrentSocket and OtherSocket make offsets to Start and End. But there's a catch. Even offset applied, collision returns true if initial location is colliding. 
					OffsetLargeRoomSceneComps(OtherRoom,*CurrentSocket, *OtherSocket, Start, End);

					
					
					//If it cannot find path, reset visited to false and try again. If path can be found, add sockets to list. 
					if (!FindCorridorPath(Start.X, Start.Y, End.X, End.Y, FIntPoint(0,0), FIntPoint(0,0), false, 50000))
					{
						for (int x = 0; x < MapSizeX; ++x)
						{
							for (int y = 0; y < MapSizeY; ++y)
							{
								Tiles[x][y].Visited = false;
							}
						}
						//It couldn't find one 
						if (!FindCorridorPath(Start.X, Start.Y, End.X, End.Y, FIntPoint(0,0), FIntPoint(0,0), false, 50000))
						{
							UE_LOG(LogTemp, Warning, TEXT("Couldn't start connection between: %s,%s. Room's name are %s,%s"), *CurrentSocket->GetFName().ToString(),*OtherSocket->GetFName().ToString(), *CurrentRoom->GetFName().ToString(),*OtherRoom->GetFName().ToString());
						}
						else
						{
							// Add both scene comps to the array if they can form a corridor path
							AvailableSockets.AddUnique(CurrentSocket);
							AvailableSockets.AddUnique(OtherSocket);
							SpawnRoomForBranchConnection(ExpectedTag(DirectionToTag(PathStart->Direction)),Start, End);
						}
					}
					else //This means without any issue, it found a path. 
					{
						// Add both scene comps to the array if they can form a corridor path
						AvailableSockets.AddUnique(CurrentSocket);
						AvailableSockets.AddUnique(OtherSocket);
						SpawnRoomForBranchConnection(ExpectedTag(DirectionToTag(PathStart->Direction)),Start, End);
					}
				}
			}
		}
	}
}

void AProceduralGeneration::SocketExclusionForLargeRoom(ARoomActor* Room)
{
	TArray<USceneComponent*> SceneComponents;
	Room->GetComponents<USceneComponent*>(SceneComponents);

	//Remove Enter and Exit sockets from the array pool
	for (auto SceneComp : SceneComponents)
	{
		if (SceneComp->ComponentHasTag("Enter") || SceneComp->ComponentHasTag("Exit"))
		{
			SceneComponents.Remove(SceneComp);
		}
	}

	//Get the names of the scene components and add _Offset to end of each. 
	TArray<FName> SceneCompNames;
	for (auto SceneComp : SceneComponents)
	{
		FString Name = SceneComp->GetFName().ToString();
		Name.Append(TEXT("_Exclude"));
		SceneCompNames.Add(FName(*Name));
	}
	
	//Get the class of the Room
	UClass* RoomClass = Room->GetClass();

	// Iterate through all properties of the Room
	for (TFieldIterator<FProperty> PropIt(RoomClass); PropIt; ++PropIt)
	{
		FProperty* Prop = *PropIt;
		FArrayProperty* ArrayProp = CastField<FArrayProperty>(Prop);
		if (ArrayProp)
		{
			FStructProperty* StructInnerProp = CastField<FStructProperty>(ArrayProp->Inner);
			if (StructInnerProp && StructInnerProp->Struct == TBaseStructure<FIntPoint>::Get())
			{
				for (auto Name : SceneCompNames)
				{
					if (StructInnerProp->GetFName() == Name)
					{
						// This is an array of FIntPoints. Do your logic here.
						FScriptArrayHelper_InContainer ArrayHelper(ArrayProp,Room);
						if (ArrayHelper.Num() > 0)
						{
							for (int i = 0; i < ArrayHelper.Num(); ++i)
							{
								FIntPoint* IntPoint = reinterpret_cast<FIntPoint*>(ArrayHelper.GetRawPtr(i));

								//1. Looks harder than it is. Foreach SceneComponents check if it's name is equal to the name of the array. But before we need to scrap the _Exclude from the name. suffix
								FName ChoppedName = FName(*Name.ToString().LeftChop(8));
								for (auto SceneComp : SceneComponents)
								{
									if (ChoppedName == SceneComp->GetFName())
									{
										FIntPoint Index = WorldToIndex(SceneComp->GetComponentLocation());

										int CurrentX = Index.X + IntPoint->X;
										int CurrentY = Index.Y + IntPoint->Y;
										
										if (IsValid(CurrentX,CurrentY))
										{
											Tiles[CurrentX][CurrentY].Blocked = false;
											Tiles[CurrentX][CurrentY].Visited = false;
										}
    	
										if (VisualizeAllExclusions)
										{
											DrawDebugBox(GetWorld(),Tiles[CurrentX][CurrentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,0),FColor::Purple,true);
										}
									}
								}
							}
						}
					}	
				}
			}
		}
	}
}

void AProceduralGeneration::OffsetLargeRoomSceneComps(ARoomActor* Room, USceneComponent& SceneComp1,USceneComponent& SceneComp2, FIntPoint& Start, FIntPoint& End)
{
	FString Name1 = SceneComp1.GetFName().ToString().Append(TEXT("_Offset"));
	FString Name2 = SceneComp2.GetFName().ToString().Append(TEXT("_Offset"));

	UClass* RoomClass = Room->GetClass();
	for (TFieldIterator<FProperty> PropIt(RoomClass); PropIt; ++PropIt)
	{
		FProperty* Prop = *PropIt;
		FStructProperty* StructProp = CastField<FStructProperty>(Prop); //If this is a struct property
		if (StructProp && StructProp->Struct == TBaseStructure<FIntPoint>::Get()) //if this is FIntPoint
		{
			if (StructProp->GetFName() == FName(*Name1))
			{
				const FIntPoint* IntPoint = StructProp->ContainerPtrToValuePtr<FIntPoint>(Room);
				Start += *IntPoint;
			}
			else if (StructProp->GetFName() == FName(*Name2))
			{
				const FIntPoint* IntPoint = StructProp->ContainerPtrToValuePtr<FIntPoint>(Room);
				End += *IntPoint;
			}
		}
	}

	if (VisualizeEnterAndExitPathStartTile)
	{
		DrawDebugBox(GetWorld(),Tiles[Start.X][Start.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Green,true);
		DrawDebugBox(GetWorld(),Tiles[End.X][End.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Green,true);
	}
}


void AProceduralGeneration::GenerateMap()
{
	InitWorldTiles();
	
	//Test Collision
	for (int i = 0; i < BlockRoomLocations.Num(); ++i)
	{
		ARoomActor* TestRoom = GetWorld()->SpawnActor<ARoomActor>(BlockRoom, BlockRoomLocations[i],FRotator(0.0f, 0.0f, -90.0f));
		SetTilesBlocked(TestRoom,BlockRoomLocations[i]);
		SetSocketExclusion(TestRoom);
	}

	//Spawning first room
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[0]->GetDefaultObject());
	while (NextRoom->ActorHasTag("NoExit"))
	{
		NextRoom = Cast<ARoomActor>(RoomDesigns[0]->GetDefaultObject());
	}
	FirstRoomStartLoc = Tiles[MapSizeX/2][MapSizeY/2].Location + FVector(0,0,2);
	SetTilesBlocked(NextRoom,FirstRoomStartLoc);
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[0], FirstRoomStartLoc, Rotation);

	SetSocketExclusion(FirstRoom);
	LastSpawnedRoom = FirstRoom;
	
	while (SpawnedRoomCount <= NumberOfRooms)
	{
		if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightUp"))
		{
			SpawnRoom("StraightDown");
			SpawnedRoomCount++;
		}
		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightDown"))
		{
			SpawnRoom("StraightUp");
			SpawnedRoomCount++;
		}
		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideRight"))
		{
			SpawnRoom("SideLeft");
			SpawnedRoomCount++;
		}
		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideLeft"))
		{
			SpawnRoom("SideRight");
			SpawnedRoomCount++;
		}
	}
	//It working correct. Now test MakeBranchConnection
	MakeSideBranchFromLargeRoom();

	/*Not working. I'll take care of it later */
	// MakeBranchConnection();
	
	if (VisualiseOverlaps)
	{
		VisualizeOverlaps();
	}
	if (VisualiseVisited)
	{
		VisualizeVisited();
	}
	// MakeBranchConnection();
}


int AProceduralGeneration::DetermineSafeCheckAmount(ARoomActor* NextRoom) const
{
	if (NextRoom->ActorHasTag("LargeRoom"))
		return LargeRoomMaxSafeCheck;
	else
		return NormalRoomMaxSafeCheck;
}

void AProceduralGeneration::SpawnRoom(FName Tag)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation() + FVector(0,0,1);
	
	//If Room sequence given, use those rooms if not given, get random rooms
	int RandomIndex;
	if (!RoomSequence.IsEmpty())
	{
		if (CurrentIndex < RoomSequence.Num())
			RandomIndex = RoomSequence[CurrentIndex];
		else
			return;
		CurrentIndex++;
	}
	else
		RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	
	//Find a correct room. 
	while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || NextRoom->ActorHasTag("NoExit"))
	{
		//If Room sequence given, use those rooms if not given, get random rooms
		if (!RoomSequence.IsEmpty())
		{
			if (CurrentIndex < RoomSequence.Num())
				RandomIndex = RoomSequence[CurrentIndex];
			else
				return;
			CurrentIndex++;
		}
		else
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
		NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	}
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];
	
	//If room overlaps at previous room's door exit location 
	if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	{
		SetTilesBlocked(NextRoom,NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		
		// if (VisualizeEnterAndExitPathStartTile)
		// {
		// 	FIntPoint StartIndex = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
		// 	DrawDebugBox(GetWorld(),Tiles[StartIndex.X + LastSpawnedRoom->PathStartOffset.X][StartIndex.Y + LastSpawnedRoom->PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		//
		// 	FIntPoint EndIndex = WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());
		// 	DrawDebugBox(GetWorld(),Tiles[EndIndex.X + NextRoom->PathEndOffset.X][EndIndex.Y + NextRoom->PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		// }
		
		LastSpawnedRoom = NextRoom;
		SetSocketExclusion(LastSpawnedRoom);
		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	}
	else
	{
		MoveOverlappedRoom(NextRoom, NextRoomLocation);
		SetTilesBlocked(NextRoom, NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);

		// After spawning a room, store the connection information:
		FRoomConnection Connection;
		Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
		Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
		Connection.PathEndOffset = NextRoom->PathEndOffset;
		Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
		Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);

		RoomConnections.Add(Connection);
		SetSocketExclusion(NextRoom);
		ConnectRoomsWithCorridors();

		if (VisualizeEnterAndExitPathStartTile)
		{
			FIntPoint StartIndex = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
			DrawDebugBox(GetWorld(),Tiles[StartIndex.X + Connection.PathStartOffset.X][StartIndex.Y + Connection.PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		
			FIntPoint EndIndex = WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());
			DrawDebugBox(GetWorld(),Tiles[EndIndex.X + Connection.PathEndOffset.X][EndIndex.Y + Connection.PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		}
		
		LastSpawnedRoom = NextRoom;
		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	}
	
	
	// Large Room logic. 
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		LargeRooms.Add(NextRoom);
	}
}

void AProceduralGeneration::SpawnRoomForBranchConnection(FName Tag, FIntPoint StartIndex, FIntPoint EndIndex)
{
	FVector TargetLoc = FVector(0,0,0); //Placeholder
	FRoomConnection Connection = FRoomConnection();
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = IndexToWorld(StartIndex.X,StartIndex.Y) + FVector(0,0,1);

	TArray<ARoomActor*> ValidRooms;
	TArray<float> PathCost;

	//Add an array all the available rooms that could be spawned and calculate distance
	for (int i = 0; i < RoomDesigns.Num(); ++i)
	{
		ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[i]->GetDefaultObject());
		if (NextRoom->DoorSocketEnter->ComponentHasTag(Tag) && !NextRoom->ActorHasTag("NoExit") && !NextRoom->ActorHasTag("LargeRoom"))
		{ 
			if (IsEndSocketOverlapping(NextRoom,NextRoomLocation) || IsColliding(NextRoom, NextRoomLocation))
			{
				NextRoomLocation = IndexToWorld(StartIndex.X,StartIndex.Y) + FVector(0,0,1);
				MoveOverlappedRoom(NextRoom, NextRoomLocation);
			}
				
				TArray<FIntPoint> BlockedTiles = BlockAndRetrieveTiles(NextRoom,NextRoomLocation);
				FVector RelativeLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
				RelativeLoc.Y = -RelativeLoc.Z;
				RelativeLoc.Z = 0;
				FVector Pos = NextRoomLocation + RelativeLoc;
				FIntPoint Start2 = WorldToIndex(Pos);

				if (FindCorridorPath(Start2.X, Start2.Y, EndIndex.X, EndIndex.Y, NextRoom->PathStartOffset, NextRoom->PathEndOffset, false, 10000))
				{
					ValidRooms.Add(NextRoom);
					PathCost.Add(FoundPathCost);	
				}
				else
				{
					for (int x = 0; x < MapSizeX; ++x)
					{
						for (int y = 0; y < MapSizeY; ++y)
						{
							Tiles[x][y].Visited = false;
						}
					}
					if (FindCorridorPath(Start2.X, Start2.Y, EndIndex.X, EndIndex.Y, NextRoom->PathStartOffset, NextRoom->PathEndOffset, false, 10000))
					{
						ValidRooms.Add(NextRoom);
						PathCost.Add(FoundPathCost);
					}

				}

				//After pathfinding attempt, unblock the tiles because room is not spawned yet. But to make pathfinding correct, it was required to be set as blocked. 
				for (auto BlockedTile : BlockedTiles)
				{
					Tiles[BlockedTile.X][BlockedTile.Y].Blocked = false;
				}
			}
	}

	// Find the room with the lowest PathCost
	if (PathCost.IsEmpty()) return;
	int32 MinIndex = 0;
	float MinDistance = PathCost[0];
	for (int32 i = 1; i < PathCost.Num(); i++)
	{
		if (PathCost[i] < MinDistance)
		{
			MinDistance = PathCost[i];
			MinIndex = i;
		}
	}

	ARoomActor* NextRoom = ValidRooms[MinIndex];
	if (!NextRoom) return;
	
	if (CurrentDistance < PreviousDistance || CurrentDistance == PreviousDistance ) //If we still can get close 
	{
		NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
		NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];

		//If room overlaps at previous room's door exit location 
		if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
		{
			NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
			SetTilesBlocked(NextRoom,NextRoomLocation);

			LastSpawnedRoom = NextRoom;
			SetSocketExclusion(LastSpawnedRoom);
			CurrentDistance = FVector::Distance(LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), TargetLoc);
			// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
		}
		else
		{
			MoveOverlappedRoom(NextRoom, NextRoomLocation);
			NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
			SetTilesBlocked(NextRoom,NextRoomLocation);

			// After spawning a room, store the connection information:
			Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
			Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
			Connection.PathEndOffset = NextRoom->PathEndOffset;
			Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
			Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);

			SetSocketExclusion(NextRoom);
			RoomConnections.Add(Connection);
			ConnectRoomsWithCorridors();

			LastSpawnedRoom = NextRoom;
			CurrentDistance = FVector::Distance(LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), TargetLoc);
			// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
		}

		if (CurrentDistance > PreviousDistance && CurrentDistance != PreviousDistance)
		{
				// We're not getting closer, so stop the recursion and spawn a corridor.
				FIntPoint Start = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
				FIntPoint End = WorldToIndex(TargetLoc);
				FindCorridorPath(Start.X,Start.Y,End.X,End.Y,Connection.PathStartOffset,Connection.PathEndOffset,true, 10000); //This means we spawn corridor
				return; // Ensure we exit the function
		}
	}
	else //Here also means we cannot get closer. 
	{
		// We're not getting closer, so stop the recursion and spawn a corridor.
		FIntPoint Start = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
		FIntPoint End = WorldToIndex(TargetLoc);
		FindCorridorPath(Start.X,Start.Y,End.X,End.Y,Connection.PathStartOffset,Connection.PathEndOffset,true, 10000); //This means we spawn corridor
		return; // Ensure we exit the function
	}

	PreviousDistance = CurrentDistance;
	FName DoorSocketExitTag = ExpectedTag(FName(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]));

	// Now make the recursive call, since we're still making progress towards the target.
	SpawnRoomForBranchConnection(DoorSocketExitTag,WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation()) + LastSpawnedRoom->PathStartOffset, EndIndex);
}

ARoomActor* AProceduralGeneration::SpawnFirstBranchRoom(FName Tag, FVector SpawnLoc)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = SpawnLoc + FVector(0,0,1);
	int RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());

	//Find a correct room. 
	while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || NextRoom->ActorHasTag("NoExit"))
	{
		RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
		NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	}
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];

	//If room overlaps at previous room's door exit location 
	if (!IsColliding(NextRoom, NextRoomLocation) && !IsEndSocketOverlapping(NextRoom,NextRoomLocation))
	{
		SetTilesBlocked(NextRoom,NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);

		SetSocketExclusion(NextRoom);
		ConnectRoomsWithCorridors();
		LastSpawnedRoom = NextRoom;
		NumOfSideBranchRoom++;
		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	}
	else
	{
		//It's overlapped here but because this is side branch, we don't forgive overlaps. Spawn Door that represents no entrance. 
	}
	
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		LargeRooms.Add(NextRoom);
	}
	ConnectRoomsWithCorridors();
	return NextRoom;
}

ARoomActor* AProceduralGeneration::SpawnBranchRoom(FName Tag, int SpawnCounter)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation() + FVector(0,0,1);
	int RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());

	//End of branch. Spawn NoExit Room
	if (SpawnCounter == BranchLength -1)
	{
		while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || !NextRoom->ActorHasTag("NoExit"))
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
		}	
	}
	else
	{
		while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || NextRoom->ActorHasTag("NoExit"))
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
		}
	}
	
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];

	//If room overlaps at previous room's door exit location 
	if (!IsColliding(NextRoom, NextRoomLocation) && !IsEndSocketOverlapping(NextRoom,NextRoomLocation))
	{
		SetTilesBlocked(NextRoom,NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		
		LastSpawnedRoom = NextRoom;
		SetSocketExclusion(LastSpawnedRoom);
		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	}
	else
	{
		//It's overlapped here but because this is side branch, we don't forgive overlaps. Spawn Door that represents no entrance.
		MoveOverlappedRoom(NextRoom, NextRoomLocation);
		SetTilesBlocked(NextRoom, NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);

		// After spawning a room, store the connection information:
		FRoomConnection Connection;
		Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
		Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
		Connection.PathEndOffset = NextRoom->PathEndOffset;
		Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
		Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);

		SetSocketExclusion(NextRoom);
		RoomConnections.Add(Connection);
		ConnectRoomsWithCorridors();
		LastSpawnedRoom = NextRoom;
		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	}

	// Large Room logic. 
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		LargeRooms.Add(NextRoom);
	}
	return NextRoom;
}

bool AProceduralGeneration::IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc)
{
	FVector ExitLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
	ExitLoc.Y = -ExitLoc.Z; 
	ExitLoc.Z = 0; 
	FVector EndSocketWorldLoc = SpawnLoc + ExitLoc;
	FIntPoint Index = WorldToIndex(EndSocketWorldLoc);

	FName DirectionTag = NextRoom->DoorSocketExit->ComponentTags[0]; 

	// Create a new array to hold the modified points
	TArray<FIntPoint> SocketCheck;
	
	FIntPoint AdjustedTile = NextRoom->ExitSocketCheck;

	if (DirectionTag == "SideLeft") {
			AdjustedTile.X = -AdjustedTile.X;  // Invert Y for left direction
	}
	else if (DirectionTag == "SideRight")
	{
		AdjustedTile.Y = -AdjustedTile.Y;  // Invert Y because I need to go upward.
		
		for (int x = 0; x <= AdjustedTile.X; ++x) {
			for (int y = 0; y >= AdjustedTile.Y; --y) {
				SocketCheck.Add(FIntPoint(x, y));
			}
		}
	}
	// Add more conditions for other directions like "StraightUp", "StraightDown"


	
	
	for (auto Tile: SocketCheck)
	{
		int CurrentX = Index.X + Tile.X;
		int CurrentY = Index.Y + Tile.Y;

		if (VisualizeEndSocketOverlapCheck)
		{
			DrawDebugBox(GetWorld(),Tiles[CurrentX][CurrentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Magenta,true);

		}
		if (IsValid(CurrentX,CurrentY) && Tiles[CurrentX][CurrentY].Blocked)
		{
			return true;
		}
	}
	return false;  // The area around the End Socket is free
}

void AProceduralGeneration::InitWorldTiles()
{
	//resize tiles array
	Tiles.SetNum(MapSizeX);
	for (int i = 0; i < MapSizeX; ++i)
		Tiles[i].SetNum(MapSizeY);

	for (int x = 0; x < MapSizeX; ++x)
		for (int y = 0; y < MapSizeY; ++y)
		{
			Tiles[x][y].Location = IndexToWorld(x,y);
			Tiles[x][y].X = x;
			Tiles[x][y].Y = y;
			Tiles[x][y].Parent = nullptr;
			Tiles[x][y].Blocked = false;
			Tiles[x][y].Direction = EDirection2::Dir_None;
		}
}

bool AProceduralGeneration::FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount)
{
	TArray<FIntPoint> Storing;
	TArray<int> row = {-1, 0, 0, 1};
	TArray<int> col = {0, -1, 1, 0};
	TArray<FTileStruct*> OpenList;
	int SafeCheck = 0;
	int SecondCounter = 0;
	
	//Make offset adjustments
	StartX += StartOffset.X;
	StartY += StartOffset.Y;
	GoalX += EndOffset.X;
	GoalY += EndOffset.Y;
	FoundPathCost = INT_MAX;
	
	if (!IsValid(StartX,StartY))
	{
		UE_LOG(LogTemp, Display, TEXT("Out of bound so I returned: %i, %i "), StartX, StartY);
		return false;
	} //return

	// StartX++;
	FTileStruct* Start = &Tiles[StartX][StartY];
	// DetermineStartPathOffset(Start,StartX,StartY);
	Start->Visited = true;
	Start->HCost = FPathNode::GetHCost(StartX, StartY, GoalX, GoalY);
	OpenList.Add(Start);

	

	while (OpenList.Num() > 0 && SafeCheck < MaxIterationAmount)
	{
		// Find the node with the smallest FCost
		int minIndex = 0;
		for (int i = 1; i < OpenList.Num(); ++i)
		{
			if (OpenList[i]->FCost() < OpenList[minIndex]->FCost())
				minIndex = i;
		}

		FTileStruct* Current = OpenList[minIndex];

		OpenList.RemoveAt(minIndex);

		if (Current->X == GoalX && Current->Y == GoalY)
		{
			if (VisualizeCorridorPath)
			{
				TArray<FTileStruct*> PathSequence;
				FTileStruct* prevNode = nullptr;  // Keep track of the previous node
				FTileStruct* PathNode =  Current;
				while (PathNode != nullptr)
				{
					if (PathNode->Parent == prevNode) {
						UE_LOG(LogTemp, Error, TEXT("Circular reference detected between nodes. Breaking out of loop."));
						break;
					}
					PathSequence.Add(PathNode);
					DrawDebugBox(GetWorld(), Tiles[PathNode->X][PathNode->Y].Location + FVector(TileSizeX/2,TileSizeY/2,0), FVector(TileSizeX/2,TileSizeY/2,TileSizeY), FColor::Red, true, -1, 0, 0);
					Storing.Add(FIntPoint(PathNode->X,PathNode->Y));
					prevNode = PathNode;
					PathNode = PathNode->Parent;
					//Safe check. In rare occasions, it can end up circular reference even though I took precausion. 
					SafeCheck++;
					if (SafeCheck > MaxIterationAmount)
					{
						return false; 
					}
				}

				if (!PathSequence.IsEmpty())
				{
					PathEnd = PathSequence[0];
					PathStart = PathSequence[PathSequence.Num() -2];
				}
				
			}
			
			if (SpawnCorr)
			{
				SpawnCorridors(GoalX,GoalY);
			}
			FoundPathCost = Current->GCost;
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			SecondCounter++;
			int newX = Current->X + row[i];
			int newY = Current->Y + col[i];
			FVector TileWorldPos = IndexToWorld(newX,newY);
			ARoomActor* Corridor = Cast<ARoomActor>(StraightCorr->GetDefaultObject());
			
			if (IsValid(newX, newY)) // && !Tiles[newX][newY].Visited && !IsColliding(Corridor,TileWorldPos)
			{
				if (!Tiles[newX][newY].Visited)
				{
					if (!IsColliding(Corridor,TileWorldPos))
					{
						FTileStruct* Neighbour = &Tiles[newX][newY];
						int newMovementCostToNeighbour = Current->GCost + 1; // assuming each move costs 1

						if (newMovementCostToNeighbour < Neighbour->GCost || !OpenList.Contains(Neighbour))
						{
							Neighbour->GCost = newMovementCostToNeighbour;
							Neighbour->HCost = FPathNode::GetHCost(newX, newY, GoalX, GoalY);
							Neighbour->Parent = Current;
							DeterminePathDirection(Current, newX, newY, Neighbour);
							OpenList.Add(Neighbour);
						}
						Tiles[newX][newY].Visited = true;
						if (newX == GoalX && newY == GoalY)
						{
							UE_LOG(LogTemp, Display, TEXT("Working:"));

						}
					}
				}
			}
		}
		SafeCheck++;
	}
	if (SafeCheck >= MaxIterationAmount)
	{
		UE_LOG(LogTemp, Error, TEXT("No corridor path found Number of iteration is : %d, %d. If iteration is high, end path couldn't found. If iteration is small, (0-10 begin path not found"), SafeCheck, SecondCounter);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No available path found. Iterated 4 times just 4 direction"));
		
	}
	return false; 
}


void AProceduralGeneration::SpawnCorridors(int goalX, int goalY)
{
	std::stack<FVector> LocStack;
	std::stack<FRotator> RotStack;
	std::stack<EDirection2> DirStack;
	FTileStruct* Current = &Tiles[goalX][goalY];
	TArray<FTileStruct*> CurrentTracker;
	CurrentTracker.Add(Current);
	TSet<FTileStruct*> VisitedNodes;


	while (Current != nullptr)
	{
		if (VisitedNodes.Contains(Current))
		{
			// Detected a cycle
			UE_LOG(LogTemp, Warning, TEXT("Detected a cycle in path traversal at node (%d, %d)"), Current->X, Current->Y);
			break; // Break out of the loop
		}
		VisitedNodes.Add(Current);
		
		Tiles[Current->X][Current->Y].Path = true;
		LocStack.push(Tiles[Current->X][Current->Y].Location);
		DirStack.push(Tiles[Current->X][Current->Y].Direction);
		RotStack.push(Tiles[Current->X][Current->Y].Rotation);
		Current = Current->Parent;
		CurrentTracker.Add(Current);
	}
	
	//First assign CurrDir and pop it from DirStack
	EDirection2 CurrDir = DirStack.top();
	DirStack.pop();

	//Secondly peek next dir after popping CurrDir previously
	EDirection2 NextDir = DirStack.top();
	CurrDir = DetermineFirstDirection(NextDir);
	// First corridor logic
	if (!LocStack.empty())
	{
		//Check first current and next corr dir and spawn straight if not spawn turned in else 
		FVector SpawnLoc = LocStack.top();
		if (CurrDir == NextDir)
		{
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLoc, RotStack.top());
			SetTilesBlocked(Corridor,SpawnLoc);
		}
		else
		{
			//First corridor is not straight. It will be turned. 
			FRotator FirstCorrRot = DetermineFirstTurnRotation(NextDir);
			SpawnLoc.Z += 1;
			
			//Assigning rot is done. Now spawn turned corr
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, FirstCorrRot);
			SetTilesBlocked(Corridor,SpawnLoc);

		}
		
		LocStack.pop();
		RotStack.pop();
		CurrDir = DirStack.top();
		DirStack.pop();
	}
	
	//Middle corridors between first and last 
	while (LocStack.size() > 1)
	{
		// Set the next direction if available
		if (!DirStack.empty())
		{
			NextDir = DirStack.top();
			DirStack.pop();
		}
		else
		{
			NextDir = Dir_None;
		}
		
		FVector SpawnLoc = LocStack.top();
		if (CurrDir == NextDir)
		{
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLoc, RotStack.top());
			SetTilesBlocked(Corridor,SpawnLoc);		}
		else
		{
			// Assuming TurnCorridor has the right rotation logic inside it
			FRotator TurnCorrRot = DetermineMiddleTurnRotation(CurrDir, NextDir);
			SpawnLoc.Z += 1;
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, TurnCorrRot);
			SetTilesBlocked(Corridor,SpawnLoc);
		}
		LocStack.pop();
		RotStack.pop();
		CurrDir = NextDir;
	}
	
	//Last corridor logic. After while loop over last corridor will be left
	FVector SpawnLoc = LocStack.top();
	FRotator LastCorrRot = DetermineLastCorrRotation(CurrDir);

	EDirection2 NextRoomEnterDir = ConvertNextRoomEnterTagToDirection();
	
	if ((CurrDir == NextRoomEnterDir) || LastCorrException(CurrDir,NextRoomEnterDir))
	{
		ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLoc, RotStack.top());
		SetTilesBlocked(Corridor,SpawnLoc);
	}
	else
	{
		SpawnLoc.Z += 1;
		ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, LastCorrRot);
		SetTilesBlocked(Corridor,SpawnLoc);
	}
	LocStack.pop();
	RotStack.pop();
	CurrDir = NextDir;
	
}

bool AProceduralGeneration::IsColliding(ARoomActor* Room, FVector SpawnLoc)
{
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;
	
	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();

	// Calculate top-left corner of the box in world space
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;

	// Dimensions of each tile
	int TilesX = FMath::CeilToInt(BoxExtends.X * 2 / TileSizeX); 
	int TilesZ = FMath::CeilToInt(BoxExtends.Z * 2 / TileSizeY);

	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	for (int x = 0; x < TilesX; ++x)
	{
		for (int z = 0; z < TilesZ; ++z)
		{
			int CurrentTileX = (StartIndex.X + x);
			int CurrentTileZ = (StartIndex.Y + z);
			if (IsValid(CurrentTileX,CurrentTileZ))
			{
				if (Tiles[CurrentTileX][CurrentTileZ].Blocked)
				{
					return true;
				}
			}
		}
	}
	return false; 
}

bool AProceduralGeneration::IsBufferZoneColliding(ARoomActor* Room, FVector SpawnLoc)
{
	int BufferX = BufferSize * TileSizeX;
	int BufferY = BufferSize * TileSizeY;
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;
	
	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent() + FVector(BufferX,0,BufferY);
	

	// Calculate top-left corner of the box in world space
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;

	// Dimensions of each tile
	int TilesX = FMath::CeilToInt(BoxExtends.X * 2 / TileSizeX); 
	int TilesZ = FMath::CeilToInt(BoxExtends.Z * 2 / TileSizeY);

	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	for (int x = 0; x < TilesX; ++x)
	{
		for (int z = 0; z < TilesZ; ++z)
		{
			int CurrentTileX = (StartIndex.X + x);
			int CurrentTileZ = (StartIndex.Y + z);
			if (IsValid(CurrentTileX,CurrentTileZ))
			{
				if (Tiles[CurrentTileX][CurrentTileZ].Blocked)
				{
					return true;
				}
			}
		}
	}
	return false; 
}

//Same as IsColliding. Just setting given indexes to be blocked.

void AProceduralGeneration::SetTilesBlocked(ARoomActor* Room, FVector SpawnLoc)
{
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;
	
	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();

	// Calculate top-left corner of the box in world space
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;

	// Dimensions of each tile
	int TilesX = FMath::CeilToInt(BoxExtends.X * 2 / TileSizeX); //For some reason tile generation for room's X axis starts early. I had to offset to right and reduce 1 extra tile generation on X. I offset 1 axis to right and reduced 1 tile generation.
	int TilesZ = FMath::CeilToInt(BoxExtends.Z * 2 / TileSizeY);

	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	for (int x = 0; x < TilesX; ++x)
	{
		for (int z = 0; z < TilesZ; ++z)
		{
			int CurrentTileX = (StartIndex.X + x);
			int CurrentTileZ = (StartIndex.Y + z);
			if (IsValid(CurrentTileX,CurrentTileZ))
			{
				Tiles[CurrentTileX][CurrentTileZ].Blocked = true;
				Tiles[CurrentTileX][CurrentTileZ].Visited = true;
			}
		}
	}
}

TArray<FIntPoint> AProceduralGeneration::BlockAndRetrieveTiles(ARoomActor* Room, FVector SpawnLoc)
{
	TArray<FIntPoint> BlockedTiles;
	
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;
	
	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();

	// Calculate top-left corner of the box in world space
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;

	// Dimensions of each tile
	int TilesX = FMath::CeilToInt(BoxExtends.X * 2 / TileSizeX); //For some reason tile generation for room's X axis starts early. I had to offset to right and reduce 1 extra tile generation on X. I offset 1 axis to right and reduced 1 tile generation.
	int TilesZ = FMath::CeilToInt(BoxExtends.Z * 2 / TileSizeY);

	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	for (int x = 0; x < TilesX; ++x)
	{
		for (int z = 0; z < TilesZ; ++z)
		{
			int CurrentTileX = (StartIndex.X + x);
			int CurrentTileZ = (StartIndex.Y + z);
			if (IsValid(CurrentTileX,CurrentTileZ))
			{
				Tiles[CurrentTileX][CurrentTileZ].Blocked = true;
				Tiles[CurrentTileX][CurrentTileZ].Visited = true;
				BlockedTiles.Add(FIntPoint(CurrentTileX,CurrentTileZ));
			}
		}
	}

	return BlockedTiles;
}

void AProceduralGeneration::SetSocketExclusion(ARoomActor* Room)
{
	//Enter
	FIntPoint Index = WorldToIndex(Room->DoorSocketEnter->GetComponentLocation());
	// if (VisualizeEnterAndExitPathStartTile)
	// {
	// 	DrawDebugBox(GetWorld(),Tiles[Index.X + Room->PathStartOffset.X][Index.Y + Room->PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
	// }
	
	//Enter exclusions
	TArray<FIntPoint> EnterExclusions = Room->EnterExclusions;

    for (const FIntPoint& point : EnterExclusions)
	{
    	int currentX = Index.X + point.X;
    	int currentY = Index.Y + point.Y;


	    if (IsValid(currentX,currentY))
	    {
		    Tiles[currentX][currentY].Blocked = false;
		    Tiles[currentX][currentY].Visited = false;
	    }
    	
    	if (VisualizeAllExclusions)
    		DrawDebugBox(GetWorld(),Tiles[currentX][currentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,0),FColor::Purple,true);
	}
	
	
	// Exit exclusions
	TArray<FIntPoint> exitExclusions = Room->ExitExclusions;
	
	Index = WorldToIndex(Room->DoorSocketExit->GetComponentLocation());
	// if (VisualizeEnterAndExitPathStartTile)
	// {
 // 		DrawDebugBox(GetWorld(),Tiles[Index.X + Room->PathEndOffset.X][Index.Y + Room->PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
	// }
	
	for (const FIntPoint& point : exitExclusions)
	{
		int currentX = Index.X + point.X;
		int currentY = Index.Y + point.Y;
        
		if (IsValid(currentX, currentY))
		{
			Tiles[currentX][currentY].Blocked = false;
			Tiles[currentX][currentY].Visited = false;
		}
	}

	//IF this room is large room, make exclusion for other scene comps of the room.
	if (Room->ActorHasTag("LargeRoom"))
	{
		// Get a list of all scene components in the room
		TArray<USceneComponent*> SceneComps;
		Room->GetComponents<USceneComponent>(SceneComps);
		SocketExclusionForLargeRoom(Room);
		
	}
	
}

bool AProceduralGeneration::MoveOverlappedRoom(ARoomActor* NextRoom, FVector& NextRoomLocation)
{
	const int MAX_ATTEMPTS = 100000000;
	int attempts = 0;
    
	// Get the starting point from the NextRoomLocation's tile indexes
	FIntPoint StartIndex = WorldToIndex(NextRoomLocation);
	int startX = StartIndex.X;
	int startY = StartIndex.Y;
    
	int maxDistance = FMath::Max(MapSizeX, MapSizeY);
    
	for (int dist = 1; dist <= maxDistance; ++dist) 
	{
		for (int x = startX - dist; x <= startX + dist; ++x) 
		{
			for (int y = startY - dist; y <= startY + dist; ++y) 
			{
				// DrawDebugBox(GetWorld(), Tiles[x][y].Location, FVector(TileSizeX / 2, TileSizeY / 2, 10), FColor::Red, true);
				// Ensure the positions are within the grid bounds
				if (IsValid(x, y)) 
				{
					if (!IsColliding(NextRoom, Tiles[x][y].Location))
					{
						if (!IsBufferZoneColliding(NextRoom,Tiles[x][y].Location))
						{
							if (!IsEndSocketOverlapping(NextRoom,Tiles[x][y].Location))
							{
								NextRoomLocation = Tiles[x][y].Location;
								return true;
							}
						}
					}
				}
                
				++attempts;
				if (attempts <= SafeCheckAmount)
				{
					DrawDebugBox(GetWorld(), Tiles[x][y].Location, FVector(TileSizeX / 2, TileSizeY / 2, 10), FColor::Cyan, true);
				}
				
				if (attempts >= MAX_ATTEMPTS)
				{
					UE_LOG(LogTemp, Warning, TEXT("Exceeded maximum attempts to find a valid spot!"));
					return false; // This will exit the function early.
				}
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Nothing has been found"));
	return false; // This will exit the function early.
	// If you reach here, no valid spot was found. Handle this scenario as needed.
}

// Called every frame

void AProceduralGeneration::VisualizeOverlaps()
{
	for (int x = 0; x < MapSizeX; ++x)
	{
		for (int y = 0; y < MapSizeY; ++y)
		{
			if (Tiles[x][y].Blocked)
			{
				DrawDebugBox(GetWorld(),Tiles[x][y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Yellow,true);
			}
		}
	}
}

void AProceduralGeneration::VisualizeVisited()
{
	for (int x = 0; x < MapSizeX; ++x)
	{
		for (int y = 0; y < MapSizeY; ++y)
		{
			if (Tiles[x][y].Visited)
			{
				DrawDebugBox(GetWorld(),Tiles[x][y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Magenta,true);
			}
		}
	}
}

void AProceduralGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
