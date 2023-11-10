//TODO: Expose a Vector variable that will make entire map centered at that location. 
//TODO: Consider changing UnscaledBoxExtent to ScaledBoxExtent. 


#include "ProceduralGen.h"

#include <stack>

#include "Components/BoxComponent.h"
#include "ProceduralGeneration.h"
#include "Door/DoorActor.h"


// Sets default values
AProceduralGen::AProceduralGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProceduralGen::BeginPlay()
{
	Super::BeginPlay();
	TileBoxExtends = FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY / 2);
	GenerateMap();

	if (VisualizeOverlaps || VisualizeVisited)
	{
		VisualizeTiles();
	}
}

void AProceduralGen::GenerateMap()
{
	InitWorldTiles();
	SpawnTestCollisionObjects();
	SpawnFirstRoom();
	// IsEndSocketOverlapping(NextRoom, FirstRoomStartLoc); //TODO: THis function has been called but for no reason for first room. Later on remove it of course after you understood well enough refactored if necessary and make sure it works good
	// IsColliding(FirstRoom, FirstRoomStartLoc);

	while (SpawnedRoomCount < NumberOfRooms)
	{
		SpawnRoom(LastSpawnedRoom->ExitSocketDirection);

		if (LastSpawnedRoom->ActorHasTag("NoExit")) //TODO: I just writing this to later on don't forget. LargeRoom and NoExit rooms must be another bool option. Also when one selected other must be disabled. 
		{
			UE_LOG(LogTemp, Display, TEXT("Aborted all room spawning due to NoExit room encountered"));
			NumberOfRooms = -1;
		}
	}

	//TODO: Implement large room spawning here
}

void AProceduralGen::InitWorldTiles()
{
	//resize tiles array
	Tiles.SetNum(MapSizeX);
	for (int i = 0; i < MapSizeX; ++i)
		Tiles[i].SetNum(MapSizeY);

	for (int x = 0; x < MapSizeX; ++x)
		for (int y = 0; y < MapSizeY; ++y)
		{
			Tiles[x][y].Location = IndexToWorld(x, y);
			Tiles[x][y].X = x;
			Tiles[x][y].Y = y;
			Tiles[x][y].Parent = nullptr;
			Tiles[x][y].Blocked = false;
			Tiles[x][y].Direction = Dir_None;
		}
}

void AProceduralGen::SpawnTestCollisionObjects()
{
	for (int i = 0; i < BlockRoomLocations.Num(); ++i)
	{
		ARoomActor* TestRoom = GetWorld()->SpawnActor<ARoomActor>(BlockRoom, BlockRoomLocations[i], FRotator(0.0f, 0.0f, -90.0f));
		SetTilesBlocked(TestRoom, BlockRoomLocations[i]);
		SetSocketExclusion(TestRoom);
	}
}

void AProceduralGen::SpawnFirstRoom()
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);

	//First room spawning
	//TODO: Later for first room spawning make first room array will pick random index from 4 directions. There won't be enter only exit.  
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[0]->GetDefaultObject()); //Later on we will make here completely random as well. Just for now spawn first index as first room as always.
	FVector FirstRoomStartLoc = Tiles[MapSizeX / 2][MapSizeY / 2].Location + ZOffset;
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), FirstRoomStartLoc, Rotation);
	SetTilesBlocked(NextRoom, FirstRoomStartLoc);
	SetSocketExclusion(FirstRoom);
	LastSpawnedRoom = FirstRoom;
	SpawnedRoomCount++;
	if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++; //TODO: LATER FIX THIS AS WELL LARGEROOM ONLY MUST BE OPTION. I NEED TO MINIMIZE ALL THE TAG USAGE
}

void AProceduralGen::CalculatePathInfo(ARoomActor* NextRoom)
{
	FRoomConnection Connection;
	Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
	Connection.PathEndOffset = NextRoom->PathEndOffset;
	Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
	Connection.MaxCheckAmount = DetermineSafeCheckAmount(NextRoom);
	Connection.RoomName = NextRoom->GetName();
	RoomConnections.Add(Connection);

	if (VisualizeBeginAndEndTiles)
	{
		VisualizeBeginEndTiles(NextRoom, Connection);
	}
}

void AProceduralGen::SpawnRoom(const Direction EndSocketDirection)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();

	ARoomActor* NextRoom = SelectRoomWithDirection(ExpectedTag(EndSocketDirection));

	//TODO: You know this 2 line has to gone. 
	NextRoomExitTag = NextRoom->ExitSocketDirection;
	NextRoomEnterTag = NextRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	if (!IsEndSocketOverlapping(NextRoom, NextRoomLocation) && !IsColliding(NextRoom, NextRoomLocation))
	{
		SpawnNonOverlappedRoom(Rotation, NextRoomLocation, NextRoom);
	}
	else
	{
		SpawnOverlappedRoom(Rotation, NextRoomLocation, NextRoom);
	}
	SpawnedRoomCount++;
}

void AProceduralGen::SpawnNonOverlappedRoom(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom)
{
	NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	SetTilesBlocked(NextRoom, NextRoomLocation);

	ADoorActor* Door = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor, NextRoomLocation + ZOffset, Rotation);
	NextRoom->SetEnterDoorActor(Door);

	LastSpawnedRoom = NextRoom;
	SetSocketExclusion(LastSpawnedRoom);

	//TODO: YOU KNOW WHAT TO DO WITH THIS.
	if (LastSpawnedRoom->ActorHasTag("LargeRoom")) LargeRoomCounter++;
}

void AProceduralGen::SpawnOverlappedRoom(const FRotator& Rotation, FVector NextRoomLocation, ARoomActor*& NextRoom)
{
	if (!MoveOverlappedRoom(NextRoom, NextRoomLocation)) //TODO: I believe if available space couldn't be found we need to do something in here. 
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Couldn't find a valid spot for overlapped room for ") + NextRoom->GetName()));

	NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	SetTilesBlocked(NextRoom, NextRoomLocation);
	SpawnDoors(Rotation, NextRoomLocation, NextRoom);
	SetSocketExclusion(NextRoom);

	//Making corridor
	CalculatePathInfo(NextRoom);
	ConnectRoomsWithCorridors();
	LastSpawnedRoom = NextRoom;
}

void AProceduralGen::SpawnDoors(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom)
{
	ADoorActor* EnterDoor = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor, NextRoomLocation + ZOffset, Rotation);
	GetWorld()->SpawnActor<ADoorActor>(NextRoom->ExitDoor, NextRoom->DoorSocketExit->GetComponentLocation() + ZOffset, Rotation);
	NextRoom->SetEnterDoorActor(EnterDoor);
}

bool AProceduralGen::IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc)
{
	FVector ExitLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
	SwapZYaxis(ExitLoc);
	FVector EndSocketWorldLoc = SpawnLoc + ExitLoc;
	FIntPoint Index = WorldToIndex(EndSocketWorldLoc);
	Index += NextRoom->ExitSocketCheckOffset;

	for (auto Tile : NextRoom->ExitSocketChecks)
	{
		int CurrentX = Index.X + Tile.X;
		int CurrentY = Index.Y + Tile.Y;

		if (IsValid(CurrentX, CurrentY) && VisualizeEndSocketOverlapCheck)
			DrawDebugBox(GetWorld(), Tiles[CurrentX][CurrentY].Location + TileBoxExtends, TileBoxExtends, FColor::Magenta, true);

		if (IsValid(CurrentX, CurrentY) && Tiles[CurrentX][CurrentY].Blocked)
		{
			//TODO: Consider to delete this if block entirely later on. If given tile is marked as blocked no ned to check is colliding already
			if (IsColliding(NextRoom, IndexToWorld(CurrentX, CurrentY))) //Only Generate message box in debugging
			{
				UE_LOG(LogTemp, Warning, TEXT("EndSocketOverlap ovelaps with the actor itself. "));
				if (NextRoom != LastCheckedRoom)
				{
					LastCheckedRoom = NextRoom;
					return true;
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("EndSocketOverlap ovelaps it will act as if overlapped:"));
			return true;
		}
	}
	return false; // The area around the End Socket is fre
}

bool AProceduralGen::IsColliding(const ARoomActor* Room, const FVector& SpawnLoc)
{
	bool IsColliding = false;

	ForEachTileInRoom(Room, SpawnLoc, [&](const int X, const int Z)
	{
		if (Tiles[X][Z].Blocked)
		{
			IsColliding = true;
		}
	});

	return IsColliding;
}

void AProceduralGen::SetTilesBlocked(ARoomActor* Room, const FVector& SpawnLoc)
{
	TArray<FIntPoint> BlockedTiles;
	ForEachTileInRoom(Room, SpawnLoc, [&](const int X, const int Z)
	{
		Tiles[X][Z].Blocked = true;
		Tiles[X][Z].Visited = true;
		BlockedTileHolder.Add(FIntPoint(X, Z)); //TODO: Not sure enough if this BlockedTileHolder must be removed
		BlockedTiles.Add(FIntPoint(X, Z));
	});

	//TODO: Couldn't much understand what is this for. If it corridor we add room exclusions but why for only corridor? Consider to remove it later
	if (!Room->IsA(TurnCorridor) || !Room->IsA(StraightCorr))
	{
		RoomExclusions.Add(Room, BlockedTiles);
	}
}

void AProceduralGen::SetSocketExclusion(ARoomActor* Room)
{
	if (!Room) return;

	//Enter exclusions
	FIntPoint StartIndex = WorldToIndex(Room->DoorSocketEnter->GetComponentLocation());
	SetExclusion(Room, StartIndex, Room->EnterExclusionOffset, Room->EnterExclusions);

	//Exit Exclusions
	FIntPoint EndIndex = WorldToIndex(Room->DoorSocketExit->GetComponentLocation());
	SetExclusion(Room, EndIndex, Room->ExitExclusionOffset, Room->ExitExclusions);

	//TODO: Large room implementation later on work on this
	// //IF this room is large room, make exclusion for other scene comps of the room.
	// if (Room->ActorHasTag("LargeRoom"))
	// {
	// 	// Get a list of all scene components in the room
	// 	TArray<USceneComponent*> SceneComps;
	// 	Room->GetComponents<USceneComponent>(SceneComps);
	// 	SocketExclusionForLargeRoom(Room);
	// 	
	// }
}

void AProceduralGen::ConnectRoomsWithCorridors()
{
	for (FRoomConnection& Connection : RoomConnections)
	{
		FIntPoint StartIndex = WorldToIndex(Connection.StartPoint);
		FIntPoint EndIndex = WorldToIndex(Connection.EndPoint);

		// Find a path from StartIndex to EndIndex:
		if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y, Connection.PathStartOffset, Connection.PathEndOffset, SpawnCorridor, Connection.MaxCheckAmount, Connection.RoomName))
		{
			ResetAllVisited();
			FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y, Connection.PathStartOffset, Connection.PathEndOffset, SpawnCorridor, Connection.MaxCheckAmount, Connection.RoomName);
		}
	}
	RoomConnections.Empty();
}

void AProceduralGen::SetExclusion(ARoomActor* Room, const FIntPoint& Index, const FIntPoint& ExclusionOffset, TArray<FIntPoint> Exclusions)
{
	for (const FIntPoint& Point : Exclusions)
	{
		int CurrentX = Index.X + Point.X + ExclusionOffset.X;
		int CurrentY = Index.Y + Point.Y + ExclusionOffset.Y;

		if (IsValid(CurrentX, CurrentY))
		{
			Tiles[CurrentX][CurrentY].Blocked = false;
			Tiles[CurrentX][CurrentY].Visited = false;
		}

		if (IsValid(CurrentX, CurrentY) && VisualizeAllExclusions)
			DrawDebugBox(GetWorld(), Tiles[CurrentX][CurrentY].Location + TileBoxExtends, TileBoxExtends, FColor::Purple, true);
	}
}

void AProceduralGen::SwapZYaxis(FVector& VectorToSwap)
{
	VectorToSwap.Y = -VectorToSwap.Z;
	VectorToSwap.Z = 0;
}

ARoomActor* AProceduralGen::SelectRoomWithDirection(const Direction EndSocketDirection)
{
	//If DebugRoomSequence is given the sequence has to be selected in order. 
	if (!DebugRoomSequence.IsEmpty() && CurrentIndex < DebugRoomSequence.Num())
	{
		ARoomActor* SequenceRoom = Cast<ARoomActor>(DebugRoomSequence[CurrentIndex]->GetDefaultObject());
		CurrentIndex++;
		return SequenceRoom;
	}

	//Determine all the valid rooms could be selected 
	TArray<ARoomActor*> ValidRooms;
	for (auto RoomDesign : RoomDesigns)
	{
		ARoomActor* RoomCandidate = Cast<ARoomActor>(RoomDesign->GetDefaultObject());
		if (RoomCandidate && RoomCandidate->EnterSocketDirection == EndSocketDirection)
		{
			ValidRooms.Add(RoomCandidate);
		}
	}

	if (ValidRooms.Num() > 0)
	{
		int32 RoomIndex = FMath::RandRange(0, ValidRooms.Num() - 1);
		return ValidRooms[RoomIndex];
	}

	return nullptr;
}

FVector AProceduralGen::CalculateTopLeftCorner(const FVector& WorldLoc, const FVector& BoxExtends)
{
	FVector TopLeftCorner;
	TopLeftCorner.X = WorldLoc.X - BoxExtends.X;
	TopLeftCorner.Y = WorldLoc.Y - BoxExtends.Z;
	TopLeftCorner.Z = 0;
	return TopLeftCorner;
}

void AProceduralGen::ForEachTileInRoom(const ARoomActor* Room, const FVector& SpawnLoc, const TFunction<void(int X, int Z)>& TileAction)
{
	if (!Room) return;

	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	SwapZYaxis(RelativeLoc);

	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();
	FVector TopLeftCorner = CalculateTopLeftCorner(WorldLoc, BoxExtends);
	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	// Amount of tile the room has
	int TilesX = FMath::CeilToInt(BoxExtends.X * 2 / TileSizeX);
	int TilesZ = FMath::CeilToInt(BoxExtends.Z * 2 / TileSizeY);

	for (int x = 0; x < TilesX; ++x)
	{
		for (int z = 0; z < TilesZ; ++z)
		{
			int CurrentTileX = (StartIndex.X + x);
			int CurrentTileZ = (StartIndex.Y + z);
			if (IsValid(CurrentTileX, CurrentTileZ))
			{
				TileAction(CurrentTileX, CurrentTileZ);
			}
		}
	}
}

void AProceduralGen::SpawnCorridors(int goalX, int goalY)
{
	TArray<FVector> LocStack;
	TArray<FRotator> RotStack;
	TArray<EDirection2> DirStack;
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
		LocStack.Add(Tiles[Current->X][Current->Y].Location);
		DirStack.Push(Tiles[Current->X][Current->Y].Direction);
		RotStack.Push(Tiles[Current->X][Current->Y].Rotation);
		Current = Current->Parent;
		CurrentTracker.Add(Current);
	}

	//First assign CurrDir and pop it from DirStack
	EDirection2 CurrDir = DirStack.Top();
	DirStack.Pop();

	//Secondly peek next dir after popping CurrDir previously
	EDirection2 NextDir = DirStack.Top();
	CurrDir = DetermineFirstDirection(NextDir);
	// First corridor logic
	if (!LocStack.IsEmpty())
	{
		//Check first current and next corr dir and spawn straight if not spawn turned in else 
		FVector SpawnLoc = LocStack.Top();
		if (CurrDir == NextDir)
		{
			SpawnLocations.Add(SpawnLoc);
			SpawnRotations.Add(RotStack.Top());
		}
		else
		{
			//First corridor is not straight. It will be turned. 
			FRotator FirstCorrRot = DetermineFirstTurnRotation(NextDir);
			SpawnLoc.Z += 1;

			//Assigning rot is done. Now spawn turned corr
			if (FirstCorrRot != FRotator(31, 31, 31))
			{
				ARoomActor* Corridor;
				if (FirstCorrRot == FRotator(0, 0, -90) || FirstCorrRot == FRotator(0, 90, -90))
				{
					Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLoc, FirstCorrRot);
				}
				else
				{
					Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, FirstCorrRot);
				}
				SetTilesBlocked(Corridor, SpawnLoc);
			}
		}

		LocStack.Pop();
		RotStack.Pop();
		CurrDir = DirStack.Top();
		DirStack.Pop();
	}

	//Middle corridors between first and last 
	while (LocStack.Num() > 1)
	{
		// Set the next direction if available
		if (!DirStack.IsEmpty())
		{
			NextDir = DirStack.Top();
			DirStack.Pop();
		}
		else
		{
			NextDir = Dir_None;
		}

		FVector SpawnLoc = LocStack.Top();
		if (CurrDir == NextDir)
		{
			SpawnLocations.Add(SpawnLoc);
			SpawnRotations.Add(RotStack.Top());
		}
		else
		{
			// Assuming TurnCorridor has the right rotation logic inside it
			FRotator TurnCorrRot = DetermineMiddleTurnRotation(CurrDir, NextDir);
			SpawnLoc.Z += 1;
			if (TurnCorrRot != FRotator(31, 31, 31))
			{
				ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, TurnCorrRot);
				SetTilesBlocked(Corridor, SpawnLoc);
			}
		}
		LocStack.Pop();
		RotStack.Pop();
		CurrDir = NextDir;
	}

	//Last corridor logic. After while loop over last corridor will be left
	FVector SpawnLoc = LocStack.Top();
	FRotator LastCorrRot = DetermineLastCorrRotation(CurrDir);

	EDirection2 NextRoomEnterDir = ConvertNextRoomEnterTagToDirection();

	if ((CurrDir == NextRoomEnterDir) || LastCorrException(CurrDir, NextRoomEnterDir))
	{
		SpawnLocations.Add(SpawnLoc);
		SpawnRotations.Add(RotStack.Top());
	}
	else
	{
		SpawnLoc.Z += 1;
		if (LastCorrRot != FRotator(31, 31, 31))
		{
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridor, SpawnLoc, LastCorrRot);
			SetTilesBlocked(Corridor, SpawnLoc);
		}
	}
	LocStack.Pop();
	RotStack.Pop();
	CurrDir = NextDir;

	for (int i = 0; i < SpawnLocations.Num(); ++i)
	{
		// if (!IsColliding(StraightCorr->GetDefaultObject<ARoomActor>(),SpawnLocations[i]))
		{
			ARoomActor* NormalCorr = GetWorld()->SpawnActor<ARoomActor>(StraightCorr, SpawnLocations[i], SpawnRotations[i]);
			SetTilesBlocked(NormalCorr, SpawnLocations[i]);
		}
	}
}

void AProceduralGen::VisualizeTiles()
{
	for (int X = 0; X < MapSizeX; ++X)
	{
		for (int Y = 0; Y < MapSizeY; ++Y)
		{
			bool Condition = VisualizeOverlaps ? Tiles[X][Y].Blocked : Tiles[X][Y].Visited;
			FColor Color = VisualizeOverlaps ? FColor::Yellow : FColor::Magenta;
			if (Condition)
			{
				DrawDebugBox(GetWorld(), Tiles[X][Y].Location + TileBoxExtends, TileBoxExtends, Color, true);
			}
		}
	}
}

void AProceduralGen::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Get the name of the property that was changed
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	//Check if the property changed is VisualizeOverlaps
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AProceduralGen, VisualizeOverlaps))
	{
		if (VisualizeOverlaps)
		{
			VisualizeVisited = false;
		}
	}
	//Check if the property changed is VisualizeOverlaps
	else if (PropertyName == GET_MEMBER_NAME_CHECKED(AProceduralGen, VisualizeVisited))
	{
		if (VisualizeVisited)
		{
			VisualizeOverlaps = false;
		}
	}
}

bool AProceduralGen::MoveOverlappedRoom(ARoomActor* NextRoom, FVector& NextRoomLocation)
{
	TSet<FIntPoint> VisitedTiles;
	int Attempts = 0;

	// Get the starting point from the NextRoomLocation's tile indexes
	FIntPoint StartIndex = WorldToIndex(NextRoomLocation);
	int StartX = StartIndex.X;
	int StartY = StartIndex.Y;

	int MaxDistance = FMath::Max(MapSizeX, MapSizeY);

	for (int Dist = 1; Dist <= MaxDistance; ++Dist)
	{
		for (int x = StartX - Dist; x <= StartX + Dist; ++x)
		{
			for (int y = StartY - Dist; y <= StartY + Dist; ++y)
			{
				// Ensure the determined position is suitable to be spawned
				if (IsValid(x, y) && !VisitedTiles.Contains(FIntPoint(x, y)))
					if (!IsColliding(NextRoom, Tiles[x][y].Location))
						if (!IsBufferZoneColliding(NextRoom, Tiles[x][y].Location))
							if (!IsEndSocketOverlapping(NextRoom, Tiles[x][y].Location))
							{
								NextRoomLocation = Tiles[x][y].Location;
								return true;
							}

				++Attempts;
				VisitedTiles.Add(FIntPoint(x, y));

				if (Attempts >= MaxAttemptForRoomMoving)
				{
					UE_LOG(LogTemp, Warning, TEXT("Exceeded maximum attempts to find a valid spot!"));
					return false; // This will exit the function early.
				}
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Nothing has been found"));
	return false; // This will exit the function early.
}

bool AProceduralGen::IsBufferZoneColliding(ARoomActor* Room, FVector SpawnLoc)
{
	int BufferX = BufferSize * TileSizeX;
	int BufferY = BufferSize * TileSizeY;
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	RelativeLoc.Y = -RelativeLoc.Z;
	RelativeLoc.Z = 0;

	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent() + FVector(BufferX, 0, BufferY);


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
			if (IsValid(CurrentTileX, CurrentTileZ))
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

bool AProceduralGen::FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount, FString RoomName, int* PathCost)
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

	if (!IsValid(StartX, StartY))
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
			FTileStruct* prevNode = nullptr; // Keep track of the previous node
			FTileStruct* PathNode = Current;
			while (PathNode != nullptr)
			{
				if (PathCost)
				{
					(*PathCost)++;
				}
				if (PathNode->Parent == prevNode)
				{
					UE_LOG(LogTemp, Error, TEXT("Room %s Circular reference detected between nodes. Breaking out of loop."), *RoomName);
					break;
				}
				PathSequence.Add(PathNode);
				if (VisualizeCorridorPath)
				{
					DrawDebugBox(GetWorld(), Tiles[PathNode->X][PathNode->Y].Location + FVector(TileSizeX / 2, TileSizeY / 2, 0), FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY), FColor::Red, true, -1, 0, 0);
				}
				Storing.Add(FIntPoint(PathNode->X, PathNode->Y));
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
				SpawnCorridors(GoalX, GoalY);
			}
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			SecondCounter++;
			int newX = Current->X + row[i];
			int newY = Current->Y + col[i];
			FVector TileWorldPos = IndexToWorld(newX, newY);
			ARoomActor* Corridor = Cast<ARoomActor>(TurnCorridor->GetDefaultObject());

			if (IsValid(newX, newY))
			{
				if (!Tiles[newX][newY].Visited)
				{
					if (!IsColliding(Corridor, TileWorldPos))
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
		UE_LOG(LogTemp, Error, TEXT("Room %s No corridor path found Number of iteration is : %d, %d. If iteration is high, end path couldn't found. If iteration is small, (0-10 begin path not found"), *RoomName, SafeCheck, SecondCounter);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Room %s No available path found. Iterated 4 times just 4 direction. Make sure Path Start is not overlapping. Disable Overlap Visualization and enable Start&End visualiztion"), *RoomName);
	}
	return false;
}

void AProceduralGen::VisualizeBeginEndTiles(ARoomActor* NextRoom, const FRoomConnection& Connection)
{
	FIntPoint StartIndex = WorldToIndex(LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
	DrawDebugBox(GetWorld(), Tiles[StartIndex.X + Connection.PathStartOffset.X][StartIndex.Y + Connection.PathStartOffset.Y].Location + FVector(TileSizeX / 2, TileSizeY / 2, 0), FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY / 2), FColor::Cyan,
	             true);
	FIntPoint EndIndex = WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());
	DrawDebugBox(GetWorld(), Tiles[EndIndex.X + Connection.PathEndOffset.X][EndIndex.Y + Connection.PathEndOffset.Y].Location + FVector(TileSizeX / 2, TileSizeY / 2, 0), FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY / 2), FColor::Cyan, true);
}

void AProceduralGen::ResetAllVisited()
{
	for (int x = 0; x < MapSizeX; ++x)
		for (int y = 0; y < MapSizeY; ++y)
			Tiles[x][y].Visited = false;
}

void AProceduralGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}