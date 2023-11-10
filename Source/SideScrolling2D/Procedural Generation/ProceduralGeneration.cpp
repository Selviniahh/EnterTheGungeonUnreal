#include "ProceduralGeneration.h"
#include <stack>

#include "EngineUtils.h"
#include "RoomActor.h"
#include "Components/BoxComponent.h"
#include "Door/DoorActor.h"


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

	// FTimerHandle Delayer;
	// GetWorldTimerManager().SetTimer(Delayer, this, &AProceduralGeneration::GenerateMap, 0.1f, false);
	GenerateMap();
}

void AProceduralGeneration::GenerateMap()
{
	InitWorldTiles();
	
	//Test Collisions
	for (int i = 0; i < BlockRoomLocations.Num(); ++i)
	{
		ARoomActor* TestRoom = GetWorld()->SpawnActor<ARoomActor>(BlockRoom, BlockRoomLocations[i],FRotator(0.0f, 0.0f, -90.0f));
		SetTilesBlocked(TestRoom,BlockRoomLocations[i]);
		SetSocketExclusion(TestRoom);
	}

	//Spawning first room
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	ARoomActor* NextRoom = nullptr;
	//If debugging rooms are given use first one for this purpose otherwise use first room in the room design array. 
	if (DebugRoomSequence.Num() == 0)
	{
		//Normal one
		 NextRoom = Cast<ARoomActor>(RoomDesigns[0]->GetDefaultObject());
	}
	else
	{
		//Debugging
		 NextRoom = Cast<ARoomActor>(RoomDesigns[DebugRoomSequence[0]]->GetDefaultObject()); //Later on we will make here completely random as well. Just for now spawn first index as first room as always.
	}
	
	FirstRoomStartLoc = Tiles[MapSizeX/2][MapSizeY/2].Location + FVector(0,0,2);
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), FirstRoomStartLoc, Rotation);
	SetTilesBlocked(NextRoom,FirstRoomStartLoc);

	SetSocketExclusion(FirstRoom);
	IsEndSocketOverlapping(NextRoom,FirstRoomStartLoc);
	LastSpawnedRoom = FirstRoom;
	SpawnedRoomCount++;
	if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
	
	while (SpawnedRoomCount < NumberOfRooms)
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

		if (LastSpawnedRoom->ActorHasTag("NoExit"))
		{
			UE_LOG(LogTemp, Display, TEXT("Aborted all room spawning due to NoExit room encountered"));
			NumberOfRooms = -1; 
		}
	}

	//Wrapped with while loop in case the algorithm generates new large rooms and they also need to be processed
	while (!LargeRooms.IsEmpty())
	{
		MakeSideBranchFromLargeRoom();
	}

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

void AProceduralGeneration::VisualizeBeginEndTiles(ARoomActor* NextRoom, FRoomConnection Connection)
{
	FIntPoint StartIndex = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
	DrawDebugBox(GetWorld(),Tiles[StartIndex.X + Connection.PathStartOffset.X][StartIndex.Y + Connection.PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
	FIntPoint EndIndex = WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());
	DrawDebugBox(GetWorld(),Tiles[EndIndex.X + Connection.PathEndOffset.X][EndIndex.Y + Connection.PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
}

void AProceduralGeneration::SpawnRoom(FName Tag)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	
	//If Room sequence given, use those rooms if not given, get random rooms
	int RandomIndex;
	if (!DebugRoomSequence.IsEmpty())
	{
		if (CurrentIndex < DebugRoomSequence.Num())
			RandomIndex = DebugRoomSequence[CurrentIndex];
		else
			return;
		CurrentIndex++;
	}
	else
		RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	
	//Find a correct room. 
	while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || !CanIgnoreExitRoomSpawning(NextRoom)) //|| MoveOverlappedRoom(NextRoom,NextRoomLocation)
	{
		//If Room sequence given, use those rooms if not given, get random rooms
		if (!DebugRoomSequence.IsEmpty())
		{
			if (CurrentIndex < DebugRoomSequence.Num())
				RandomIndex = DebugRoomSequence[CurrentIndex];
			else
				return;
			CurrentIndex++;
		}
		else
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
		}
		
		NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	}
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];
	
	//If room overlaps at previous room's door exit location 
	if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	{
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		SetTilesBlocked(NextRoom,NextRoomLocation);
		ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
		NextRoom->SetEnterDoorActor(Door);
		
		LastSpawnedRoom = NextRoom;
		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
		SetSocketExclusion(LastSpawnedRoom);
	}
	else
	{
		MoveOverlappedRoom(NextRoom, NextRoomLocation);
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		SetTilesBlocked(NextRoom, NextRoomLocation);
		ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
		GetWorld()->SpawnActor<ADoorActor>(NextRoom->ExitDoor,NextRoom->DoorSocketExit->GetComponentLocation() + FVector(0,0,3), Rotation);
		NextRoom->EnterDoorActor = Door;
		NextRoom->SetEnterDoorActor(Door);
		SetSocketExclusion(NextRoom);

		
		//It overlapped so there will be corridor. We need to spawn a door for the nextroom's door socket exit socket location.
		//But we don't know if exit is staright or side so also I need to get Exit tag and spawn it. 

		
		// After spawning a room, store the connection information:
		
		FRoomConnection Connection;
		Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
		Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
		Connection.PathEndOffset = NextRoom->PathEndOffset;
		Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
		Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);
		Connection.RoomName = NextRoom->GetName();
		RoomConnections.Add(Connection);
		ConnectRoomsWithCorridors();
		
		if (VisualizeBeginAndEndTiles)
		{
			VisualizeBeginEndTiles(NextRoom, Connection);
		}
		
		LastSpawnedRoom = NextRoom;
		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;

	}
	
	
	// Large Room logic. 
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		LargeRooms.Add(NextRoom);
	}
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

bool AProceduralGeneration::IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc)
{
	FVector ExitLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
	ExitLoc.Y = -ExitLoc.Z; 
	ExitLoc.Z = 0; 
	FVector EndSocketWorldLoc = SpawnLoc + ExitLoc;
	FIntPoint Index = WorldToIndex(EndSocketWorldLoc);
	Index += NextRoom->ExitSocketCheckOffset;
	
	for (auto Tile: NextRoom->ExitSocketChecks)
	{
		int CurrentX = Index.X + Tile.X;
		int CurrentY = Index.Y + Tile.Y;

		if (VisualizeEndSocketOverlapCheck && IsValid(CurrentX,CurrentY))
		{
			DrawDebugBox(GetWorld(),Tiles[CurrentX][CurrentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Magenta,true);
		}
		if (IsValid(CurrentX,CurrentY) && Tiles[CurrentX][CurrentY].Blocked)
		{
			if (IsColliding(NextRoom, IndexToWorld(CurrentX,CurrentY))) //Only Generate message box in debugging
			{
				UE_LOG(LogTemp, Warning, TEXT("EndSocketOverlap ovelaps with the actor itself. "));
				if (NextRoom != LastCheckedRoom)
				{
					// FMessageDialog::Open(EAppMsgType::Ok,FText::Format(FTextFormat::FromString(TEXT("End Socket Overlap Check overlaps with the. The {0} actor itself. Modify Exit Socket Offset to make sure Overlap check doesn't overlap with it's own actor.")), FText::FromString(NextRoom->GetActorNameOrLabel())));
					LastCheckedRoom = NextRoom;
					return true;	
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("EndSocketOverlap ovelaps it will act as if overlapped:"));
			return true;
		}
	}
	return false;  // The area around the End Socket is free
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

void AProceduralGeneration::SetTilesBlocked(ARoomActor* Room, FVector SpawnLoc)
{
	//Box comp's World Location
	if (!Room) return;
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;
	
	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();
	TArray<FIntPoint> BlockedTiles;

	// Calculate top-left corner of the box in world space
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;

	// Amount of tile the room has
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
				BlockedTileHolder.Add(FIntPoint(CurrentTileX,CurrentTileZ)); //Just in case if the room get spawned and then destroyed, unsetting as blocked is required.  
				BlockedTiles.Add(FIntPoint(CurrentTileX,CurrentTileZ));
			}
		}
	}

	if (!Room->IsA(TurnCorridor) || !Room->IsA(StraightCorr))
	{
		RoomExclusions.Add(Room, BlockedTiles);
	}
}

void AProceduralGeneration::SetSocketExclusion(ARoomActor* Room)
{
	//Enter
	if (!Room) return;
	FIntPoint Index = WorldToIndex(Room->DoorSocketEnter->GetComponentLocation());
	
	//Enter exclusions
	FIntPoint EnterExclusionOffset = Room->EnterExclusionOffset;  // Get the offset from the Room
	TArray<FIntPoint> EnterExclusions = Room->EnterExclusions;

    for (const FIntPoint& point : EnterExclusions)
	{
    	int currentX = Index.X + point.X + EnterExclusionOffset.X;
    	int currentY = Index.Y + point.Y + EnterExclusionOffset.Y;

	    if (IsValid(currentX,currentY))
	    {
		    Tiles[currentX][currentY].Blocked = false;
		    Tiles[currentX][currentY].Visited = false;
	    }
    	
    	if (IsValid(currentX,currentY) && VisualizeAllExclusions)
    		DrawDebugBox(GetWorld(),Tiles[currentX][currentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,0),FColor::Purple,true);
	}
	
	
	// Exit exclusions
	FIntPoint ExitExclusionOffset = Room->ExitExclusionOffset;  // Get the offset from the Room
	TArray<FIntPoint> exitExclusions = Room->ExitExclusions;
	
	Index = WorldToIndex(Room->DoorSocketExit->GetComponentLocation());
	
	for (const FIntPoint& point : exitExclusions)
	{
		int currentX = Index.X + point.X + ExitExclusionOffset.X;
		int currentY = Index.Y + point.Y + ExitExclusionOffset.Y;

		if (IsValid(currentX, currentY))
		{
			Tiles[currentX][currentY].Blocked = false;
			Tiles[currentX][currentY].Visited = false;
		}
		if (IsValid(currentX,currentY) && VisualizeAllExclusions)
			DrawDebugBox(GetWorld(),Tiles[currentX][currentY].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,0),FColor::Purple,true);
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
	// const int MAX_ATTEMPTS = 10000;
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
				// Ensure the positions are within the grid bounds
				if (IsValid(x, y))
				{
					if (!IsColliding(NextRoom, Tiles[x][y].Location))
						if (!IsBufferZoneColliding(NextRoom, Tiles[x][y].Location))
							if (!IsEndSocketOverlapping(NextRoom, Tiles[x][y].Location))
							{
								NextRoomLocation = Tiles[x][y].Location;
								
								UE_LOG(LogTemp, Display, TEXT("Attempt: %i"), attempts);

								return true;
							}
				}
                
				++attempts;
				
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

void AProceduralGeneration::ConnectRoomsWithCorridors()
{
	for (FRoomConnection& Connection : RoomConnections)
	{
		FIntPoint StartIndex = WorldToIndex(Connection.StartPoint);

		// if (VisualizeBeginAndEndTiles)
		// {
		// 	DrawDebugBox(GetWorld(),Tiles[StartIndex.X + Connection.PathStartOffset.X][StartIndex.Y + Connection.PathStartOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		// }
		
		FIntPoint EndIndex = WorldToIndex(Connection.EndPoint);

		// if (VisualizeBeginAndEndTiles)
		// {
		// 	DrawDebugBox(GetWorld(),Tiles[EndIndex.X + Connection.PathEndOffset.X][EndIndex.Y + Connection.PathEndOffset.Y].Location + FVector(TileSizeX/2,TileSizeY/2,0),FVector(TileSizeX/2,TileSizeY/2,TileSizeY/2),FColor::Cyan,true);
		// }
		// Find a path from StartIndex to EndIndex:
 		if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y,Connection.PathStartOffset,Connection.PathEndOffset,SpawnCorridor, Connection.MaxCheckAmount, Connection.RoomName))
		{
			for (int x = 0; x < MapSizeX; ++x)
			{
				for (int y = 0; y < MapSizeY; ++y)
				{
					Tiles[x][y].Visited = false; 
				}
			}
			FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y,Connection.PathStartOffset,Connection.PathEndOffset,SpawnCorridor, Connection.MaxCheckAmount, Connection.RoomName);
		}
	}
	RoomConnections.Empty();
}

bool AProceduralGeneration::FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount, FString RoomName, int* PathCost)
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
		UE_LOG(LogTemp, Display, TEXT("Room %s Out of bound so I returned: %i, %i "), *RoomName, StartX, StartY);
		return false;
	}
	if (Tiles[GoalX][GoalY].Blocked)
	{
		UE_LOG(LogTemp, Error, TEXT("Room %s Goal tile is blocked. Disable visualize overlaps. Enable Visualize Begin and End tiles. Manually offset the Path End Offset."), *RoomName);
		return false;
	}

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
				TArray<FTileStruct*> PathSequence;
				FTileStruct* prevNode = nullptr;  // Keep track of the previous node
				FTileStruct* PathNode =  Current;
				while (PathNode != nullptr)
				{
					if (PathCost)
					{
						(*PathCost)++;
					}
					if (PathNode->Parent == prevNode) {
						UE_LOG(LogTemp, Error, TEXT("Room %s Circular reference detected between nodes. Breaking out of loop."), *RoomName);
						break;
					}
					PathSequence.Add(PathNode);
					if (VisualizeCorridorPath)
					{
						DrawDebugBox(GetWorld(), Tiles[PathNode->X][PathNode->Y].Location + FVector(TileSizeX/2,TileSizeY/2,0), FVector(TileSizeX/2,TileSizeY/2,TileSizeY), FColor::Red, true, -1, 0, 0);
					}
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
			
			
			if (SpawnCorr)
			{
				SpawnCorridors(GoalX,GoalY);
			}
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			SecondCounter++;
			int newX = Current->X + row[i];
			int newY = Current->Y + col[i];
			FVector TileWorldPos = IndexToWorld(newX,newY);
			ARoomActor* Corridor = Cast<ARoomActor>(TurnCorridor->GetDefaultObject());

			if (IsValid(newX, newY))
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
					}
				}
			}
		}
		SafeCheck++;
	}
	if (SafeCheck >= MaxIterationAmount)
	{
		UE_LOG(LogTemp, Error, TEXT("Room %s No corridor path found Number of iteration is : %d, %d. If iteration is high, end path couldn't found. If iteration is small, (0-10 begin path not found"),*RoomName, SafeCheck, SecondCounter);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Room %s No available path found. Iterated 4 times just 4 direction. Make sure Path Start is not overlapping. Disable Overlap Visualization and enable Start&End visualiztion"), *RoomName);
		
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

	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;


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
			SpawnLocations.Add(SpawnLoc);
			SpawnRotations.Add(RotStack.top());
		}
		else
		{
			//First corridor is not straight. It will be turned. 
			FRotator FirstCorrRot = DetermineFirstTurnRotation(NextDir);
			SpawnLoc.Z += 1;
			
			//Assigning rot is done. Now spawn turned corr
			if (FirstCorrRot != FRotator(31,31,31))
			{
				ARoomActor* Corridor;
				if (FirstCorrRot == FRotator(0,0,-90) || FirstCorrRot == FRotator(0,90,-90))
				{
					Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLoc, FirstCorrRot);
				}
				else
				{
					Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, FirstCorrRot);
				}
				SetTilesBlocked(Corridor,SpawnLoc);
			}

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
			SpawnLocations.Add(SpawnLoc);
			SpawnRotations.Add(RotStack.top());
		}
		else
		{
			// Assuming TurnCorridor has the right rotation logic inside it
			FRotator TurnCorrRot = DetermineMiddleTurnRotation(CurrDir, NextDir);
			SpawnLoc.Z += 1;
			if (TurnCorrRot != FRotator(31,31,31))
			{
				ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, TurnCorrRot);
				SetTilesBlocked(Corridor,SpawnLoc);
			}
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
		SpawnLocations.Add(SpawnLoc);
		SpawnRotations.Add(RotStack.top());
	}
	else
	{
		SpawnLoc.Z += 1;
		if (LastCorrRot != FRotator(31,31,31))
		{
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, LastCorrRot);
			SetTilesBlocked(Corridor,SpawnLoc);
		}
	}
	LocStack.pop();
	RotStack.pop();
	CurrDir = NextDir;

	for (int i = 0; i < SpawnLocations.Num(); ++i)
	{
		// if (!IsColliding(StraightCorr->GetDefaultObject<ARoomActor>(),SpawnLocations[i]))
		{
			ARoomActor* NormalCorr = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLocations[i], SpawnRotations[i]);
			SetTilesBlocked(NormalCorr,SpawnLocations[i]);	
		}
		
	}
}

int AProceduralGeneration::DetermineSafeCheckAmount(ARoomActor* NextRoom) const
{
	if (NextRoom->ActorHasTag("LargeRoom"))
		return LargeRoomMaxSafeCheck;
	else
		return NormalRoomMaxSafeCheck;
}

void AProceduralGeneration::MakeSideBranchFromLargeRoom()
{
	TArray<ARoomActor*> RoomsToBeRemoved;
	TArray<ARoomActor*> RoomsToBeAdded;
	
	for (const auto LargeRoom : LargeRooms)
	{
		TArray<USceneComponent*> Sockets;
		LargeRoom->GetComponents<USceneComponent>(Sockets);
		int SpawnCounter = 0;
	
		for (auto Socket : Sockets)
		{
			TArray<FName> AllTags = Socket->ComponentTags;
			if (!AllTags.Contains("Enter") && !AllTags.Contains("Exit") && !AllTags.IsEmpty()  && NumOfSideBranchRoom < MaxSideBranchRoom) //&& !AllTags.Contains("Exit") //Another one
			{
				FName SceneTag = Socket->ComponentTags[0];
				Socket->ComponentTags.RemoveAt(0);
				LastSpawnedRoom = nullptr;

				//1. Based on socket, get the all FintPoint from reflection. Find the correct one for this specific socket. Exclude it. And then Offset.
				//This is for offset. Pass SpawnFirstBranchRoom to found value it will be path start offset. 
				SocketExclusionForLargeRoom(LargeRoom);
				
				ARoomActor* SpawnedFirstRoom = SpawnFirstBranchRoom(ExpectedTag(SceneTag), Socket->GetComponentLocation(), *Socket, LargeRoom, RoomsToBeAdded); //First Room cannot be overlapped

				//It's null means
				if (!LastSpawnedRoom)
				{
					if (Socket->ComponentTags.Find("Enter")  == INDEX_NONE && Socket->ComponentTags.Find("Exit") == INDEX_NONE)
					{
						UClass* DoorClass;
						if (SceneTag == "StraightDown" || SceneTag == "StraightUp")
							DoorClass = LargeRoom->NoExitDoorStraight;
						else
							DoorClass = LargeRoom->NoExitDoorStraight;
					
						ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(DoorClass,Socket->GetComponentLocation() + FVector(0,0,3), Socket->GetComponentRotation());
						SpawnedFirstRoom->SetEnterDoorActor(Door);

					}
				}
				
				if (SpawnedFirstRoom->ActorHasTag("LargeRoom"))
				{
					// LargeRooms.Add(SpawnedFirstRoom);
					RoomsToBeAdded.Add(SpawnedFirstRoom);
				}
				SpawnCounter = 0;
				bool EndBranch = false;
				while (SpawnCounter < BranchLength && NumOfSideBranchRoom < MaxSideBranchRoom && LastSpawnedRoom && !EndBranch)
				{
					ARoomActor* SpawnedBranchRoom = SpawnBranchRoom(ExpectedTag(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]), SpawnCounter, RoomsToBeAdded, EndBranch, Socket->ComponentTags, RoomsToBeAdded);
					NumOfSideBranchRoom++;
					if (SpawnedBranchRoom && SpawnedBranchRoom->ActorHasTag("LargeRoom"))
					{
						// LargeRooms.Add(SpawnedBranchRoom);
						RoomsToBeAdded.Add(SpawnedBranchRoom);
					}
					SpawnCounter++;
				}
			}
			
			//In case max NumOfSideBranchRoom is reached and branch cut off, NoExit room must be spawned to finish the side branch. 
			if ((LastSpawnedRoom && !LastSpawnedRoom->ActorHasTag("NoExit")) && (SpawnCounter >= BranchLength || NumOfSideBranchRoom >= MaxSideBranchRoom))
			{
				SpawnCounter = BranchLength;
				bool EndBranch = false;
				SpawnBranchRoom(ExpectedTag(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]), SpawnCounter, RoomsToBeAdded, EndBranch, Socket->ComponentTags, RoomsToBeAdded);
			}
		}
		RoomsToBeRemoved.Add(LargeRoom);
	}

	//RoomsToBeRemoved and RoomsToBeAdded have been defined and extracted from loop to not cause array modification during iteration.
	for (auto ToBeRemoved : RoomsToBeRemoved)
	{
		LargeRooms.Remove(ToBeRemoved);
	}

	for (auto TobeAdded : RoomsToBeAdded)
	{
		LargeRooms.Add(TobeAdded);
	}

	//Recursive for the new rooms added to LargeRooms. 
	
}

bool AProceduralGeneration::ContainsManualInstruction(TArray<FName> Names)
{
	for (auto Name : Names)
	{
		if (Name != "StraightDown" || Name != "StraightUp" || Name != "StraightLeft" || Name != "StraightRight")
		{
			return true;
		}
	}
	return false;
}

ARoomActor* AProceduralGeneration::SpawnFirstBranchRoom(FName Tag, FVector SpawnLoc, USceneComponent& SceneComp, ARoomActor* LargeRoom, TArray<ARoomActor*>& RoomsToBeAdded)
{
	int SafeCheck = 0;
	bool SpawnLargeRoom = CanSpawnLargeRoom();
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = SpawnLoc;
	int RandomIndex;
	ARoomActor* NextRoom = nullptr;

	//Find a correct room.  
	while (!NextRoom
		|| !NextRoom->DoorSocketEnter->ComponentHasTag(Tag)
		|| NextRoom->ActorHasTag("NoExit")
		|| IsColliding(NextRoom, NextRoomLocation)
		|| IsEndSocketOverlapping(NextRoom,NextRoomLocation)
		|| (!SpawnLargeRoom && NextRoom->ActorHasTag("LargeRoom")))
	{
		if (!ContainsManualInstruction(SceneComp.ComponentTags))
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
			SafeCheck++;
			if (SafeCheck > 500)
			{
				UE_LOG(LogTemp, Warning, TEXT("Large room couldn't find available space to start branch. Aborting"));
				return NextRoom; //It doesn't matter what I returned here. LastSpawnedRoom is still null.
			}
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Sa "));
			RandomIndex = FCString::Atoi(*SceneComp.ComponentTags[0].ToString());
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
			SceneComp.ComponentTags.RemoveAt(0);
		}
	}
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];

	//I modified above while loop. It will check collision in while loop until it founds a correct room. So I don't need to check again here. 
	if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	{
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		SetTilesBlocked(NextRoom,NextRoomLocation);
		ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
		NextRoom->SetEnterDoorActor(Door);
		
		SetSocketExclusion(NextRoom);
		ConnectRoomsWithCorridors();
		LastSpawnedRoom = NextRoom;
		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
		NumOfSideBranchRoom++;
	}
	else //Useless
	{
		UE_LOG(LogTemp, Warning, TEXT("Large room couldn't find available space to start branch. Aborting"));
		return nullptr;
	}
	
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		RoomsToBeAdded.Add(NextRoom);
	}
	ConnectRoomsWithCorridors();
	return NextRoom;
}

ARoomActor* AProceduralGeneration::SpawnBranchRoom(FName Tag, int& SpawnCounter, TArray<ARoomActor*>& RoomsToBeAdded, bool& EndBranch, TArray<FName>& SocketComps, TArray<ARoomActor*>& RoomsBeAdded)
{
	bool StopBranch = false;
	bool SpawnLargeRoom = CanSpawnLargeRoom();
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	int RandomIndex;

	//This is the second room of the branch. So it can be easily 
	if (SocketComps.Num() >= 1)
	{
		RandomIndex = FCString::Atoi(*SocketComps[0].ToString());
		SocketComps.RemoveAt(0);
	}
	else //If manual branch rooms are not given for this branch, it will spawn random room. 
	{
		RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	}
	
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());

	//End of branch. Spawn NoExit Room
	if (SpawnCounter >= BranchLength)
	{
		while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || !NextRoom->ActorHasTag("NoExit") || (!SpawnLargeRoom && NextRoom->ActorHasTag("LargeRoom")))
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
		}	
	}
	else //Spawn normal room
	{
		while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag) || NextRoom->ActorHasTag("NoExit") || (!SpawnLargeRoom && NextRoom->ActorHasTag("LargeRoom")))
		{
			RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
			NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
		}
	}
	
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];

	//If room overlaps at previous room's door exit location 
	if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	{
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		SetTilesBlocked(NextRoom,NextRoomLocation);
		ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
		NextRoom->SetEnterDoorActor(Door);

		
		LastSpawnedRoom = NextRoom;
		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
		SetSocketExclusion(LastSpawnedRoom);

		if (LastSpawnedRoom->ActorHasTag("NoExit"))
		{
			SpawnCounter = BranchLength;
			return LastSpawnedRoom;
		}
	}
	else
	{
		MoveOverlappedRoom(NextRoom, NextRoomLocation);

		//Check here if it can make a path. It will be hard to determine all the StartPoint,EndPoint, PathStartOffset, PathEndOffset.
		//Make calculations for path check. 
		FRoomConnection InitialConnection;
		InitialConnection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
		InitialConnection.EndPoint = NextRoomLocation;
		InitialConnection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
		InitialConnection.PathEndOffset = NextRoom->PathEndOffset;
		FIntPoint StartIndex = WorldToIndex(InitialConnection.StartPoint);
		FIntPoint EndIndex = WorldToIndex(InitialConnection.EndPoint);
		int PathCost = 0;
		
		//If it cannot find a valid path or path cost is too high
		if (!LastSpawnedRoom->ActorHasTag("LargeRoom"))
		{
			if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y,InitialConnection.PathStartOffset,InitialConnection.PathEndOffset,false, 50000, InitialConnection.RoomName, &PathCost)
				|| PathCost > 150) 
			{
				UE_LOG(LogTemp, Display, TEXT("Promising: %i"), PathCost);
				//Successfully caught that that we need to stop spawning branch.

				//UnBlock the tiles
				if (RoomExclusions.Find(LastSpawnedRoom))
				{
					TArray<FIntPoint>* Points = RoomExclusions.Find(LastSpawnedRoom);
					for (auto Point : *Points)
					{
						Tiles[Point.X][Point.Y].Blocked = false;
					}
				}
				
				NextRoomLocation = LastSpawnedRoom->DoorSocketEnter->GetComponentLocation();
				FName Name = LastSpawnedRoom->DoorSocketEnter->ComponentTags[0];
				
				LastSpawnedRoom->Destroy();

				//Find NoExit Room
				while (!NextRoom->DoorSocketEnter->ComponentHasTag(Name) || !NextRoom->ActorHasTag("NoExit") || NextRoom->ActorHasTag("LargeRoom"))
				{
					RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
					NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
				}
				if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
				{
					NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
					SetTilesBlocked(NextRoom,NextRoomLocation);
					ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
					NextRoom->SetEnterDoorActor(Door);

					// LastSpawnedRoom = NextRoom;
					if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
					SetSocketExclusion(LastSpawnedRoom);
					EndBranch = true;
					return nullptr;
				}
				else
				{
					MoveOverlappedRoom(NextRoom, NextRoomLocation);
					NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
					SetTilesBlocked(NextRoom, NextRoomLocation);

					// After spawning a room, store the connection information:
					FRoomConnection Connection;
					Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
					Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
					Connection.PathEndOffset = NextRoom->PathEndOffset;
					Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
					Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);
					Connection.RoomName = NextRoom->GetName();
					RoomConnections.Add(Connection);
					SetSocketExclusion(NextRoom);
					ConnectRoomsWithCorridors();
					
					if (VisualizeBeginAndEndTiles)
					{
						VisualizeBeginEndTiles(NextRoom, Connection);
					}
					EndBranch = true;
					return nullptr;
				}
			}
		}
		
		BlockedTileHolder.Empty();
		NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
		SetTilesBlocked(NextRoom, NextRoomLocation);
		ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation);
		GetWorld()->SpawnActor<ADoorActor>(NextRoom->ExitDoor,NextRoom->DoorSocketExit->GetComponentLocation() + FVector(0,0,3), Rotation);
		NextRoom->SetEnterDoorActor(Door);


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
		
		{
			LastSpawnedRoom = NextRoom;
			if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
			// GetWorld()->SpawnActor<ADoorActor>(NextRoom->Door,FirstRoomStartLoc + FVector(0,0,1), Rotation); //Here is commented don't forget
		}

		if (StopBranch)
		{
			EndBranch = true;
		}
	}

	// Large Room logic. 
	if (NextRoom->ActorHasTag("LargeRoom"))
	{
		RoomsToBeAdded.Add(NextRoom);
	}

	if (LastSpawnedRoom->ActorHasTag("NoExit"))
	{
		SpawnCounter = BranchLength;
		return LastSpawnedRoom;
	}
	return NextRoom;
}

void AProceduralGeneration::SocketExclusionForLargeRoom(ARoomActor* Room)
{
	TArray<USceneComponent*> SceneComponents;
	Room->GetComponents<USceneComponent*>(SceneComponents);

	//Remove Enter and Exit sockets from the array pool
	TArray<USceneComponent*> CompsToRemove;
	for (auto SceneComp : SceneComponents)
	{
		if (SceneComp->ComponentHasTag("Enter") || SceneComp->ComponentHasTag("Exit"))
		{
			CompsToRemove.Add(SceneComp);
		}
	}
	
	//Remove the stored ones from scene comp list.
	for (auto Component : CompsToRemove)
	{
		SceneComponents.Remove(Component);
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
										FIntPoint Offset = GetOffsetFromGivenVarName(Room);
										
										int CurrentX = Index.X + Offset.X + IntPoint->X;
										int CurrentY = Index.Y + Offset.Y + IntPoint->Y;
										
										if (IsValid(CurrentX,CurrentY))
										{
											Tiles[CurrentX][CurrentY].Blocked = false;
											Tiles[CurrentX][CurrentY].Visited = false;
										}
    	
										if (IsValid(CurrentX,CurrentY) && VisualizeAllExclusions)
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

FIntPoint AProceduralGeneration::GetOffsetFromGivenVarName(ARoomActor* Room)
{
	for (TFieldIterator<FProperty> PropIt(Room->GetClass()); PropIt; ++PropIt)
	{
		FProperty* Prop = *PropIt;
		FStructProperty* StructProp = CastField<FStructProperty>(Prop);
		if (StructProp && StructProp->Struct == TBaseStructure<FIntPoint>::Get())
		{
			TArray<USceneComponent*> SceneComponents;
			Room->GetComponents<USceneComponent*>(SceneComponents);
			
			FIntPoint* IntPoint = StructProp->ContainerPtrToValuePtr<FIntPoint>(Room);
			FName ChoppedName = FName(*StructProp->GetName().LeftChop(7));
			for (auto SceneComp : SceneComponents)
			{
				if (ChoppedName == SceneComp->GetFName())
				{
					return *IntPoint;
				}
			}
		}
	}
	return {};
}

//End of the cpp
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

#pragma message("Not used yet")
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

#pragma message("Not working Visit later")
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
			if (SocketName == "RootScene" || SocketName == "TileMapComponent" || SocketName == "BoxComponent" || SocketName == "DoorSocketEnter")
			{
				continue;
			}
			
			// Try to find a path to each scene comp of all other LargeRooms. NOTE: It can be same room.
			for (auto OtherRoom : AvailableLargeRooms)
			{
				TArray<USceneComponent*> OtherRoomSockets;
				OtherRoom->GetComponents<USceneComponent*>(OtherRoomSockets);
				
				// For each scene comp in the other LargeRooms. NOTE: It can be same room but different scene comp.
				for (auto OtherSocket : OtherRoomSockets)
				{
					FString OtherSocketName = OtherSocket->GetName();
					if (OtherSocketName == "RootScene" || OtherSocketName == "TileMapComponent" || OtherSocketName == "BoxComponent" || OtherSocketName == "DoorSocketEnter" || OtherSocket == CurrentSocket)
					{
						continue;
					}
					
					FIntPoint Start = WorldToIndex(CurrentSocket->GetComponentLocation());
					FIntPoint End = WorldToIndex(OtherSocket->GetComponentLocation());
					//Based on The CurrentSocket and OtherSocket make offsets to Start and End. But there's a catch. Even offset applied, collision returns true if initial location is colliding. 
					
					//If it cannot find path, reset visited to false and try again. If path can be found, add sockets to list. 
					if (!FindCorridorPath(Start.X, Start.Y, End.X, End.Y, FIntPoint(0, 0), FIntPoint(0, 0), false, 1000, CurrentRoom->GetName()))
					{
						ResetAllVisited();
						//It couldn't find one 
						
						if (!FindCorridorPath(Start.X, Start.Y, End.X, End.Y, FIntPoint(0, 0), FIntPoint(0, 0), false, 1000, CurrentRoom->GetName()))
						
						{
							UE_LOG(LogTemp, Warning, TEXT("Couldn't start connection between: %s,%s. Room's name are %s,%s"), *CurrentSocket->GetFName().ToString(), *OtherSocket->GetFName().ToString(), *CurrentRoom->GetFName().ToString(),
							       *OtherRoom->GetFName().ToString());
						}
						
						else
						{
							// Add both scene comps to the array if they can form a corridor path
							AvailableSockets.AddUnique(CurrentSocket);
							AvailableSockets.AddUnique(OtherSocket);
							SpawnRoomForBranchConnection(ExpectedTag(CurrentSocket->ComponentTags[0]), Start, End);
						}
					}
					
					else //This means without any issue, it found a path. 
					{
						// Add both scene comps to the array if they can form a corridor path
						AvailableSockets.AddUnique(CurrentSocket);
						AvailableSockets.AddUnique(OtherSocket);
						SpawnRoomForBranchConnection(ExpectedTag(CurrentSocket->ComponentTags[0]), Start, End);
					}
				}
			}
		}
	}
}

#pragma message("Not working Visit later")
void AProceduralGeneration::SpawnRoomForBranchConnection(FName Tag, FIntPoint StartIndex, FIntPoint EndIndex)
{
	FRoomConnection Connection = FRoomConnection();
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = IndexToWorld(StartIndex.X,StartIndex.Y);
	TArray<ARoomActor*> ValidRooms;
	TArray<float> PathCost;

	//Add an array all the available rooms that could be spawned and calculate distance
	for (int i = 0; i < RoomDesigns.Num(); ++i)
	{
		ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[i]->GetDefaultObject());
		if (NextRoom->DoorSocketEnter->ComponentHasTag(Tag) && !NextRoom->ActorHasTag("NoExit") && !NextRoom->ActorHasTag("LargeRoom"))
		{
			NextRoomLocation = IndexToWorld(StartIndex.X,StartIndex.Y); //Reassigning here is required because if it overlaps with MoveOverlappedRoom function, NextRoomLocation is modified
			
			if (IsEndSocketOverlapping(NextRoom,NextRoomLocation) || IsColliding(NextRoom, NextRoomLocation))
			{
				NextRoomLocation = IndexToWorld(StartIndex.X,StartIndex.Y);
				MoveOverlappedRoom(NextRoom, NextRoomLocation);
				NextRoom->IsOverlapped = true; 
			}
				
			// TArray<FIntPoint> BlockedTiles = BlockAndRetrieveTiles(NextRoom,NextRoomLocation);
			FVector RelativeLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
			RelativeLoc.Y = -RelativeLoc.Z;
			RelativeLoc.Z = 0;
			FVector Pos = NextRoomLocation + RelativeLoc;
			FIntPoint Start2 = WorldToIndex(Pos);

			if (FindCorridorPath(Start2.X, Start2.Y, EndIndex.X, EndIndex.Y - 1, NextRoom->PathStartOffset, NextRoom->PathEndOffset, false, 1000, NextRoom->GetName()))
			{
				ValidRooms.Add(NextRoom);
				PathCost.Add(FoundPathCost);
			}
			// else
			// {
			// 	ResetAllVisited();
			// 	if (FindCorridorPath(Start2.X, Start2.Y, EndIndex.X, EndIndex.Y - 1, NextRoom->PathStartOffset, NextRoom->PathEndOffset, false, 1000))
			// 	{
			// 		ValidRooms.Add(NextRoom);
			// 		PathCost.Add(FoundPathCost);
			// 	}
			// }
			//After pathfinding attempt, unblock the tiles because room is not spawned yet. But to make pathfinding correct, it was required to be set as blocked. 
			// for (auto BlockedTile : BlockedTiles)
			// {
			// 	Tiles[BlockedTile.X][BlockedTile.Y].Blocked = false;
			// 	Tiles[BlockedTile.X][BlockedTile.Y].Visited = false;
			// }

			
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
	
	//alernative part
	NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor,NextRoomLocation + FVector(0,0,3), Rotation); //Comment here if required
	NextRoom->SetEnterDoorActor(Door);

	SetTilesBlocked(NextRoom,NextRoomLocation);

	if (NextRoom->IsOverlapped)
	{
		Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
		Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
		Connection.PathEndOffset = NextRoom->PathEndOffset;
		Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
		Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);
		RoomConnections.Add(Connection);
		ConnectRoomsWithCorridors();
	}
	
	SetSocketExclusion(NextRoom);
	LastSpawnedRoom = NextRoom;

	// Now make the recursive call, since we're still making progress towards the target.
	RecursiveCallAmount++;
	if (RecursiveCallAmount == 2)
	{
		return;
	}
	SpawnRoomForBranchConnection(ExpectedTag(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]),WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation()) + LastSpawnedRoom->PathStartOffset, EndIndex);


	// if (CurrentDistance < PreviousDistance || CurrentDistance == PreviousDistance ) //If we still can get close 
	// {
	// 	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0]; //Just useful to spawning corridors. Nothing to do with rooms
	// 	NextRoomEnterTag = NextRoom->DoorSocketEnter->ComponentTags[0];
	//
	// 	//If room overlaps at previous room's door exit location
	// 	if (!IsEndSocketOverlapping(NextRoom,NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	// 	{
	// 		NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	// 		SetTilesBlocked(NextRoom,NextRoomLocation);
	//
	// 		LastSpawnedRoom = NextRoom;
	// 		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
	// 		SetSocketExclusion(LastSpawnedRoom);
	// 		CurrentDistance = FVector::Distance(LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), IndexToWorld(EndIndex.X, EndIndex.Y));
	// 		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	// 	}
	// 	else
	// 	{ //I doubt here will be ever needed cuz we already make all the collision check before. 
	// 		MoveOverlappedRoom(NextRoom, NextRoomLocation);
	// 		NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	// 		SetTilesBlocked(NextRoom,NextRoomLocation);
	//
	// 		// After spawning a room, store the connection information:
	// 		Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	// 		Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
	// 		Connection.PathEndOffset = NextRoom->PathEndOffset;
	// 		Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
	// 		Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);
	//
	// 		SetSocketExclusion(NextRoom);
	// 		RoomConnections.Add(Connection);
	// 		ConnectRoomsWithCorridors();
	//
	// 		LastSpawnedRoom = NextRoom;
	// 		if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
	// 		CurrentDistance = FVector::Distance(LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), IndexToWorld(EndIndex.X, EndIndex.Y));
	// 		// GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
	// 	}
	//
	// 	if (CurrentDistance > PreviousDistance && CurrentDistance != PreviousDistance)
	// 	{
	// 			// We're not getting closer, so stop the recursion and spawn a corridor.
	// 			FIntPoint Start = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
	// 			FIntPoint End = WorldToIndex(IndexToWorld(EndIndex.X, EndIndex.Y));
	// 			FindCorridorPath(Start.X,Start.Y,End.X,End.Y,Connection.PathStartOffset,Connection.PathEndOffset,true, 10000); //This means we spawn corridor
	// 			return; // Ensure we exit the function
	// 	}
	
	// }
	// else //Here also means we cannot get closer. 
	// {
	// 	// We're not getting closer, so stop the recursion and spawn a corridor.
	// 	FIntPoint Start = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
	// 	FIntPoint End = WorldToIndex(IndexToWorld(EndIndex.X, EndIndex.Y));
	// 	FindCorridorPath(Start.X,Start.Y,End.X,End.Y,Connection.PathStartOffset,Connection.PathEndOffset,true, 10000); //This means we spawn corridor
	// 	return; // Ensure we exit the function
	// }
	//
	// PreviousDistance = CurrentDistance;
	// FName DoorSocketExitTag = ExpectedTag(FName(LastSpawnedRoom->DoorSocketExit->ComponentTags[0]));
	//
	// // Now make the recursive call, since we're still making progress towards the target.
	// SpawnRoomForBranchConnection(DoorSocketExitTag,WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation()) + LastSpawnedRoom->PathStartOffset, EndIndex);
}

void AProceduralGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}