//TODO: Expose a Vector variable that will make entire map centered at that location. 
//TODO: Consider changing UnscaledBoxExtent to ScaledBoxExtent. 
//TODO: WHat's the reason RoomConnections must be array rather than a variable. As soon as the room is overlapped.First I need to spawn that room and make a corridor. ASAP. Otherwise, it could make lots and lots of complications
#include "ProceduralGen.h"

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

	//Assign TileBoxExtends of the assigned tiles
	TileBoxExtends = FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY / 2);
	
	//Cast all room designs.
	for (auto RoomDesign : RoomDesigns)
	{
		ARoomActor* CastedRoom = Cast<ARoomActor>(RoomDesign->GetDefaultObject());
		CastedRooms.Add(CastedRoom);
	}
	
	GenerateMap();
	
	if (VisualizeOverlaps || VisualizeVisited || VisualizeOverlappedRoomTiles)
	{
		VisualizeTiles();
	}
}

void AProceduralGen::GenerateMap()
{
	SCOPE_CYCLE_COUNTER(STAT_GenerateMap);
	InitWorldTiles();
	SpawnTestCollisionObjects();
	SpawnFirstRoom();

	while (SpawnedRoomCount < NumberOfRooms)
	{
		RoomSpawning(LastSpawnedRoom->ExitSocketDirection);

		if (LastSpawnedRoom->NoExit)
		{
			UE_LOG(LogTemp, Display, TEXT("Aborted all room spawning due to NoExit room encountered"));
			NumberOfRooms = -1;
		}
	}

	//Large Room logic
	if (!LargeRooms.IsEmpty())
	{
		MakeSideBranchFromLargeRoom();
		LargeRooms.Empty();
	}
	if (!LargeRoomsToBeAdded.IsEmpty()) //TODO: Probably there's a room to refactor here  
	{
		MakeSideBranchFromLargeRoom();
	}
}

void AProceduralGen::RoomSpawning(const Direction EndSocketDirection)
{
	SCOPE_CYCLE_COUNTER(STAT_RoomSpawning);
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	bool CanSpawnLargeRoom = LargeRoomCounter < MaxLargeRoomCount ? true : false;

	ARoomActor* NextRoom = SelectRoomWithDirection(ExpectedDirection(EndSocketDirection), CanSpawnLargeRoom, false);

	//TODO: You know this 2 line has to gone. 
	NextRoomExitTag = NextRoom->ExitSocketDirection;
	NextRoomEnterTag = NextRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	if (!IsColliding(NextRoom, NextRoomLocation))
	{
		SpawnNonOverlappedRoom(Rotation, NextRoomLocation, NextRoom);
	}
	else
	{
		SpawnOverlappedRoom(Rotation, NextRoomLocation, NextRoom);
	}
}

bool AProceduralGen::CanMakeCorridorPathBeforeSpawning(ARoomActor*& NextRoom, const FVector& NextRoomLocation)
{
	TArray<FIntPoint> BlockedTiles = SetTilesBlocked(NextRoom, NextRoomLocation);
	SetSocketExclusion(NextRoom, NextRoomLocation);

	SCOPE_CYCLE_COUNTER(STAT_CanMakeCorridorPathBeforeSpawning);
	FRoomConnection Connection;
	Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	Connection.EndPoint = NextRoomLocation;
	Connection.PathEndOffset = NextRoom->PathEndOffset;
	Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
	Connection.MaxCheckAmount = FindCorridorPathLimit;
	Connection.RoomName = NextRoom->GetName();
	FIntPoint StartIndex = WorldToIndex(Connection.StartPoint);
	FIntPoint EndIndex = WorldToIndex(Connection.EndPoint);
	ResetAllVisited();
	if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y, Connection.PathStartOffset, Connection.PathEndOffset, false, Connection.MaxCheckAmount, NextRoom))
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find a valid path for overlapped %s room."), *NextRoom->GetName());
		UnBlockTiles(BlockedTiles);
		return false;
	}
	UnBlockTiles(BlockedTiles);
	return true;
}

TSharedPtr<TArray<ARoomActor*>> AProceduralGen::GetBPSpecificBranchRooms(ARoomActor*& NextRoom, const FString& SocketName)
{
	TSharedPtr<TArray<ARoomActor*>> RoomActors = MakeShared<TArray<ARoomActor*>>();

	// Iterate over the properties of the actor's class
	for (TFieldIterator<FProperty> PropIt(NextRoom->GetClass()); PropIt; ++PropIt)
	{
		FProperty* Prop = *PropIt;
		FString PropertyName = Prop->GetFName().ToString();
		FString NameItShouldBe = (SocketName + TEXT("_Spawn"));
		if (PropertyName != NameItShouldBe) continue;
		// Check if the property is an array
		if (FArrayProperty* ArrayProp = CastField<FArrayProperty>(Prop))
		{
			FProperty* InnerProp = ArrayProp->Inner;
			UE_LOG(LogTemp, Warning, TEXT("Inner Property Class: %s"), *InnerProp->GetClass()->GetName());
				
			// Cast the Inner of the ArrayProp to FObjectProperty
			FClassProperty* ClassInnerProp = CastField<FClassProperty>(ArrayProp->Inner);

			// Check if the Inner property is of ARoomActor type or its subclass
			if (ClassInnerProp && ClassInnerProp->MetaClass->IsChildOf(ARoomActor::StaticClass()))
			{
				UE_LOG(LogTemp, Warning, TEXT("ObjectInnerProp is valid for %s"), *Prop->GetName());

				// This is an array of ARoomActor. Access the array here.
				FScriptArrayHelper_InContainer ArrayHelper(ArrayProp, NextRoom);

				for (int i = 0; i < ArrayHelper.Num(); ++i)
				{
					UClass* RoomActorClass = Cast<UClass>(ClassInnerProp->GetObjectPropertyValue(ArrayHelper.GetRawPtr(i)));
					if (RoomActorClass && RoomActorClass->IsChildOf(ARoomActor::StaticClass()))
					{
						if (ARoomActor* RoomActor = NewObject<ARoomActor>(NextRoom,RoomActorClass))
						{
							RoomActors->Add(RoomActor);
						}
					}
				}
				return RoomActors;
			}
		}
	}
	return RoomActors;
}

void AProceduralGen::InitAndSpawnRoom(ARoomActor*& NextRoom, const FVector& NextRoomLocation, const FRotator& Rotation, const bool IsOverlapped, bool AddLargeRoomTempArray)
{
	UE_LOG(LogTemp, Display, TEXT("SpawnedRoom: %s at this loc: %s"), *NextRoom->GetName(), *NextRoomLocation.ToString());

	NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	SetTilesBlocked(NextRoom, NextRoomLocation);
	SpawnDoors(Rotation, NextRoomLocation, NextRoom, true);
	SetSocketExclusion(NextRoom, NextRoomLocation);

	if (IsOverlapped)
	{
		ConnectRoomsWithCorridors(NextRoom);
	}

	if (NextRoom->LargeRoom)
	{
		AddLargeRoomTempArray ? LargeRoomsToBeAdded.Add(NextRoom) : LargeRooms.Add(NextRoom);
		LargeRoomCounter++;
	}

	SpawnedRoomCount++;
	LastSpawnedRoom = NextRoom;
}

void AProceduralGen::MakeSideBranchFromLargeRoom()
{
	SCOPE_CYCLE_COUNTER(STAT_MakeSideBranchFromLargeRoom);
	TSharedPtr<TArray<ARoomActor*>> ManualBranchRooms;
	int SpawnCounter = 0;
	bool EndBranch = false;
	auto IsSocketAvailable = [&](const USceneComponent* Socket)
	{
		TArray<FName> AllTags = Socket->ComponentTags;
		return (!AllTags.Contains("Enter") && !AllTags.Contains("Exit") && !AllTags.IsEmpty()
			&& NumOfSideBranchRoom < MaxSideBranchRoom);
	};

	auto ProcessLargeRoomSockets = [&](ARoomActor* LargeRoom)
	{
		TArray<USceneComponent*> Sockets;
		LargeRoom->GetComponents<USceneComponent>(Sockets);
		for (auto Socket : Sockets) //Each large room's each socket
		{
			if (IsSocketAvailable(Socket)) //After here only available sockets will be selected to make side branch
			{ 
				ManualBranchRooms = GetBPSpecificBranchRooms(LargeRoom, Socket->GetName());
				if (ARoomActor* FirstSpawnedBranchRoom = SpawnFirstBranchRoom(TagToDirection(Socket->ComponentTags[0]), Socket->GetComponentLocation(), SpawnCounter, ManualBranchRooms))
				{
					while (FirstSpawnedBranchRoom && SpawnCounter < BranchLength && NumOfSideBranchRoom < MaxSideBranchRoom && !EndBranch)
					{
						SpawnBranchRoom(LastSpawnedRoom->ExitSocketDirection, LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), SpawnCounter, EndBranch, Socket->ComponentTags, TagToDirection(Socket->ComponentTags[0]), ManualBranchRooms);
						SpawnCounter++;
					}
				}
				else
				{
					SpawnNoExitDoor(LargeRoom, Socket->ComponentTags[0], Socket->GetComponentLocation());
				}
			}
			SpawnedRooms.Empty();
		}
	};

	TArray<ARoomActor*> IterateLargeRooms = LargeRooms.IsEmpty() ? LargeRoomsToBeAdded : LargeRooms;
	for (auto LargeRoom : IterateLargeRooms)
	{
		SelectedLargeRoom = LargeRoom;
		ProcessLargeRoomSockets(LargeRoom);
	}
}

void AProceduralGen::UnBlockLastRoomItsCorridorAndDestroy()
{
	SCOPE_CYCLE_COUNTER(STAT_UnBlockLastRoomItsCorridorAndDestroy);
	for (auto BlockedTile : SpawnedRooms.Last()->BlockedRoomTiles)
		Tiles[BlockedTile.X][BlockedTile.Y].Blocked = false;

	for (auto Corridor : SpawnedRooms.Last()->OwnerCorridors)
	{
		for (auto BlockedCorr : Corridor->BlockedCorTiles)
		{
			Tiles[BlockedCorr.X][BlockedCorr.Y].Blocked = false;
		}
	}
	for (auto OwnerCorridor : SpawnedRooms.Last()->OwnerCorridors)
	{
		OwnerCorridor->Destroy();
	}

	SpawnedRooms.Pop()->Destroy();
	if (!SpawnedRooms.IsEmpty())
		LastSpawnedRoom = SpawnedRooms.Last();
}

ARoomActor* AProceduralGen::SpawnBranchRoom(Direction ExpDirection, FVector SpawnLocation, int& SpawnCounter, bool& EndBranch, TArray<FName>& SocketComps, Direction LargeRoomSceneComp, TSharedPtr<TArray<ARoomActor*>> ManualBranchRooms)
{
	SCOPE_CYCLE_COUNTER(STAT_SpawnBranchRoom);
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	bool CanSpawnLargeRoom = LargeRoomCounter < MaxLargeRoomCount ? true : false;
	TArray<ARoomActor*> CustomRoomDesigns = CastedRooms;
	bool OnlySpawnNoExit = false;
	bool IsManualBranchGiven = false;
	
	//Now in here check that there's a manual room given for that comp or not.
	

	ARoomActor* NextRoom = nullptr; //TODO: Pass custom array here. I don't know how but in here try to select and spawn all the rooms that not overlapping and can make corridor path  
	if (SpawnCounter + 1 != BranchLength || !ManualBranchRooms->IsEmpty())
	{
		NextRoom = SelectRoomWithDirection(ExpectedDirection(ExpDirection), CanSpawnLargeRoom, false, nullptr, ManualBranchRooms);
	}
	else
	{
		NextRoom = SelectRoomWithDirection(ExpectedDirection(ExpDirection), CanSpawnLargeRoom, true);
	} //TODO: HAndle the case no exit room is unable to be path connected. in line 217 handle the case based on the initial selected room type 

	//TODO: You know this 2 line has to gone. 
	if (NextRoom)
	{
		NextRoomExitTag = NextRoom->ExitSocketDirection;
		NextRoomEnterTag = NextRoom->EnterSocketDirection;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Nextroom is null for some reason"));
		return nullptr;
	} 
	//Try to select all the available rooms if it colliding, if the chosen room is not colliding we don't need to move overlapped room anyway. 

	while (!NextRoom || IsColliding(NextRoom, SpawnLocation))
	{
		//If this returns, that means we successfully chosen a new location with a room not colliding. Keep trying until the array is emptied. 
		if (NextRoom && MoveOverlappedRoom(NextRoom, SpawnLocation))
		{
			OnlySpawnNoExit = true;
			break;
		}

		//Room selecting
		bool ShouldSpawnNoExit = NextRoom->NoExit || SpawnCounter + 1 == BranchLength;
		NextRoom = SelectRoomWithDirection(ExpectedDirection(ExpDirection), CanSpawnLargeRoom, ShouldSpawnNoExit,&CustomRoomDesigns);
		CustomRoomDesigns.Remove(NextRoom);

		//If couldn't find a valid room and array got emptied try to spawn no exit room destroying last spawned room 
		if (CustomRoomDesigns.IsEmpty() && IsColliding(NextRoom, SpawnLocation))
		{
			CustomRoomDesigns = CastedRooms; //Refill the array again
			NextRoom = SelectRoomWithDirection(SpawnedRooms.Last()->EnterSocketDirection, CanSpawnLargeRoom, true,&CustomRoomDesigns);
			SpawnLocation = SpawnedRooms.Last()->DoorSocketEnter->GetComponentLocation();
			SpawnCounter = BranchLength;
			OnlySpawnNoExit = true;
			UnBlockLastRoomItsCorridorAndDestroy();
			
			for (auto CustomRoomDesign : CustomRoomDesigns)
			{
				NextRoom = CustomRoomDesign;

				if (!IsColliding(NextRoom, SpawnLocation))
				{
					break;
				}
				else
				{
					if (MoveOverlappedRoom(NextRoom, SpawnLocation))
						break;
				}
			}

			//First time destroying last room and trying to spawn no exit room has been failed. Now repeat the process again. 
			while (!NextRoom || IsColliding(NextRoom, SpawnLocation))
			{
				if (SpawnedRooms.IsEmpty())
				{
					SpawnCounter = BranchLength;
					return nullptr;
				}
				NextRoom = SelectRoomWithDirection(SpawnedRooms.Last()->EnterSocketDirection, false, true,&CustomRoomDesigns);
				CustomRoomDesigns.Remove(NextRoom);

				if (NextRoom && MoveOverlappedRoom(NextRoom, SpawnLocation))
				{
					OnlySpawnNoExit = true;
					break;
				}

				//Unfortunately this destroying last spawned room trying to spawn no exit failed so I need to repeat this process again. Destroy again last spawned room, and repeat. 
				if (CustomRoomDesigns.IsEmpty() || IsColliding(NextRoom, SpawnLocation))
				{
					// return nullptr; //In while loop again select all again like in while loop above
					CustomRoomDesigns = CastedRooms;
					SpawnLocation = SpawnedRooms.Last()->DoorSocketEnter->GetComponentLocation();

					UnBlockLastRoomItsCorridorAndDestroy();

					if (SpawnedRooms.IsEmpty()) //LargeRoomSceneComp
					{
						NextRoom = SelectRoomWithDirection(LargeRoomSceneComp, false, true,&CustomRoomDesigns);
					}
					else
					{
						NextRoom = SelectRoomWithDirection(SpawnedRooms.Last()->EnterSocketDirection, false, true,&CustomRoomDesigns);
						SpawnedRooms.Pop()->Destroy();
					}

					//Last resort
					if (!IsColliding(NextRoom, SpawnLocation))
					{
						OnlySpawnNoExit = true;
						break;
					}
					else if (MoveOverlappedRoom(NextRoom, SpawnLocation))
					{
						OnlySpawnNoExit = true;
						break;
					}
					if (SpawnedRooms.IsEmpty())
					{
						
					}
				}
			}
		}
	}
	InitAndSpawnRoom(NextRoom, SpawnLocation, Rotation, OnlySpawnNoExit, true);
	SpawnedRooms.Add(LastSpawnedRoom);

	return NextRoom;
}

ARoomActor* AProceduralGen::SpawnFirstBranchRoom(Direction Direction, FVector SpawnLoc, int& SpawnCounter, TSharedPtr<TArray<ARoomActor*>> ManualBranchRooms)
{
	SpawnCounter = 0;
 	TArray<ARoomActor*> CustomRoomDesigns = CastedRooms;
	bool CanSpawnLargeRoom = LargeRoomCounter < MaxLargeRoomCount ? true : false;
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = SpawnLoc;
	ARoomActor* NextRoom = nullptr;

	//Try to select all the available rooms
	while (!NextRoom || IsColliding(NextRoom, NextRoomLocation))
	{
		NextRoom = SelectRoomWithDirection(ExpectedDirection(Direction), CanSpawnLargeRoom, false,&CustomRoomDesigns, ManualBranchRooms);
		CustomRoomDesigns.Remove(NextRoom);

		if (CustomRoomDesigns.IsEmpty() && IsColliding(NextRoom, NextRoomLocation))
		{
			return nullptr;
		}
	}

	InitAndSpawnRoom(NextRoom, NextRoomLocation, Rotation, false, true);
	SpawnedRooms.Add(LastSpawnedRoom);

	SpawnCounter++;
	return NextRoom;
}

void AProceduralGen::InitWorldTiles()
{
	SCOPE_CYCLE_COUNTER(STAT_InitWorldTiles);

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
	SCOPE_CYCLE_COUNTER(STAT_SpawnTestCollisionObjects);
	for (int i = 0; i < BlockRoomLocations.Num(); ++i)
	{
		ARoomActor* TestRoom = GetWorld()->SpawnActor<ARoomActor>(BlockRoom, BlockRoomLocations[i], FRotator(0.0f, 0.0f, -90.0f));
		SetTilesBlocked(TestRoom, BlockRoomLocations[i]);
		SetSocketExclusion(TestRoom, BlockRoomLocations[i]);
	}
}

void AProceduralGen::SpawnFirstRoom()
{
	SCOPE_CYCLE_COUNTER(STAT_SpawnFirstRoom);
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	ARoomActor* NextRoom = nullptr;
	//TODO: Later for first room spawning make first room array will pick random index from 4 directions. There won't be enter only exit.  
	if (DebugRoomSequence.IsEmpty())
	{
		NextRoom = Cast<ARoomActor>(CastedRooms[0]); //Later on we will make here completely random as well. Just for now spawn first index as first room as always.
	}
	else
	{
		NextRoom = Cast<ARoomActor>(DebugRoomSequence[0]->GetDefaultObject());
		CurrentIndex++;
	}

	FVector FirstRoomStartLoc = Tiles[MapSizeX / 2][MapSizeY / 2].Location + ZOffset;
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), FirstRoomStartLoc, Rotation);
	SetTilesBlocked(FirstRoom, FirstRoomStartLoc);
	SetSocketExclusion(FirstRoom, FirstRoomStartLoc);
	LastSpawnedRoom = FirstRoom;
	SpawnedRoomCount++;

	if (VisualizeEndSocketOverlapCheck) //Written to only make visualization for first room as well. 
	{
		IsEndSocketOverlapping(FirstRoom, FirstRoomStartLoc);
	}

	if (LastSpawnedRoom->LargeRoom)
	{
		LargeRooms.Add(LastSpawnedRoom);
	}
}

FRoomConnection AProceduralGen::CalculatePathInfo(ARoomActor* NextRoom)
{
	FRoomConnection Connection;
	Connection.StartPoint = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	Connection.EndPoint = NextRoom->DoorSocketEnter->GetComponentLocation();
	Connection.PathEndOffset = NextRoom->PathEndOffset;
	Connection.PathStartOffset = LastSpawnedRoom->PathStartOffset;
	Connection.MaxCheckAmount = FindCorridorPathLimit;
	Connection.RoomName = NextRoom->GetName();

	if (VisualizeBeginAndEndTiles)
	{
		VisualizeBeginEndTiles(NextRoom, Connection);
	}

	return Connection;
}

void AProceduralGen::SpawnNonOverlappedRoom(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom)
{
	InitAndSpawnRoom(NextRoom, NextRoomLocation, Rotation, false);
}

void AProceduralGen::SpawnOverlappedRoom(const FRotator& Rotation, FVector NextRoomLocation, ARoomActor*& NextRoom)
{
	if (MoveOverlappedRoom(NextRoom, NextRoomLocation)) //TODO: I believe if available space couldn't be found we need to do something in here.
	{
		InitAndSpawnRoom(NextRoom, NextRoomLocation, Rotation, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find available location in overlapped room %s aborted. If it seem possible to make a path connection, increase MaxOverlappedRoomIterate or decrease BufferSize "), *NextRoom->GetName());
		SpawnedRoomCount++;
	}
}

void AProceduralGen::SpawnDoors(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom, const bool OnlySpawnEnterDoor)
{
	ADoorActor* EnterDoor = GetWorld()->SpawnActor<ADoorActor>(NextRoom->EnterDoor, NextRoomLocation + ZOffset, Rotation);
	if (!OnlySpawnEnterDoor) GetWorld()->SpawnActor<ADoorActor>(NextRoom->ExitDoor, NextRoom->DoorSocketExit->GetComponentLocation() + ZOffset, Rotation);
	NextRoom->SetEnterDoorActor(EnterDoor);
}

//TODO: LATER MAKE ROTATIONS PROPER


void AProceduralGen::SpawnNoExitDoor(ARoomActor* LargeRoom, const FName& SceneTag, const FVector& SocketLocation)
{
	SCOPE_CYCLE_COUNTER(STAT_SpawnNoExitDoor);
	Direction TagDirection = TagToDirection(SceneTag);

	if (LastSpawnedRoom->NoExitHorizontalLeft || LastSpawnedRoom->NoExitHorizontalRight || LastSpawnedRoom->NoExitVerticalUp || LastSpawnedRoom->NoExitVerticalDown)
	{
		UE_LOG(LogTemp, Error, TEXT("No Exit Door is not given in the Blueprint"));
		return;
	}
	TMap<Direction, TPair<TSubclassOf<ADoorActor>, FRotator>> DoorMap;
	DoorMap.Add(HorizontalLeft, TPair<TSubclassOf<ADoorActor>, FRotator>(LargeRoom->NoExitHorizontalLeft, FRotator(0.0f, 0.0f, -90.0f)));
	DoorMap.Add(HorizontalRight, TPair<TSubclassOf<ADoorActor>, FRotator>(LargeRoom->NoExitHorizontalRight, FRotator(0.0f, 0.0f, -90.0f)));
	DoorMap.Add(VerticalUp, TPair<TSubclassOf<ADoorActor>, FRotator>(LargeRoom->NoExitVerticalUp, FRotator(0.0f, 0.0f, -90.0f)));
	DoorMap.Add(VerticalDown, TPair<TSubclassOf<ADoorActor>, FRotator>(LargeRoom->NoExitVerticalDown, FRotator(0.0f, 0.0f, -90.0f)));


	if (auto DoorPair = DoorMap.Find(TagDirection))
	{
		GetWorld()->SpawnActor<ADoorActor>(DoorPair->Key, SocketLocation + ZOffset, DoorPair->Value);
	}
}

bool AProceduralGen::IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc)
{
	SCOPE_CYCLE_COUNTER(STAT_IsEndSocketOverlapping);
	FVector ExitLoc = NextRoom->DoorSocketExit->GetRelativeLocation();
	SwapInvZYaxis(ExitLoc);
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
			// UE_LOG(LogTemp, Warning, TEXT("%s EndSocketOverlap ovelaps. It will act as if overlapped:"), *NextRoom->GetName());
			return true;
		}
	}
	return false; // The area around the End Socket is fre
}

bool AProceduralGen::IsColliding(ARoomActor* Room, const FVector& SpawnLoc)
{
	SCOPE_CYCLE_COUNTER(STAT_IsColliding);
	bool IsColliding = false;

	if (IsEndSocketOverlapping(Room, SpawnLoc)) return true;
	ForEachTileInRoom(Room, SpawnLoc, [&](const int X, const int Z)
	{
		if (Tiles[X][Z].Blocked)
		{
			IsColliding = true;
		}
	});


	return IsColliding;
}

TArray<FIntPoint> AProceduralGen::SetTilesBlocked(ARoomActor* Room, const FVector& SpawnLoc)
{
	TArray<FIntPoint> BlockedTiles;
	ForEachTileInRoom(Room, SpawnLoc, [&](const int X, const int Z)
	{
		Tiles[X][Z].Blocked = true;
		Tiles[X][Z].Visited = true;
		BlockedTileHolder.Add(FIntPoint(X, Z)); //TODO: Not sure enough if this BlockedTileHolder must be removed
		BlockedTiles.Add(FIntPoint(X, Z));
	});

	if (Room->IsA(TurnCorridorClass) || Room->IsA(StraightCorrClass)) //TODO: i Changed here take a look later
	{
		Room->BlockedCorTiles = BlockedTiles;
	}
	else
	{
		Room->BlockedRoomTiles = BlockedTiles;
	}

	return BlockedTiles;
}

void AProceduralGen::SetSocketExclusion(ARoomActor* Room, FVector SpawnLoc)
{
	if (!Room) return;

	//Enter exclusions
	FIntPoint StartIndex = WorldToIndex(SpawnLoc);
	SetExclusion(Room, StartIndex, Room->EnterExclusionOffset, Room->EnterExclusions);
	// SwapZYaxis(Test);

	FVector Test = Room->DoorSocketExit->GetRelativeLocation();
	SwapZYaxis(Test, SpawnLoc);
	//Exit Exclusions
	FIntPoint EndIndex = WorldToIndex(Test);
	SetExclusion(Room, EndIndex, Room->ExitExclusionOffset, Room->ExitExclusions);

	if (Room->LargeRoom)
	{
		SocketExclusionForLargeRoom(Room);
	}
}

//TODO: This deserves a real extracted method or lambd it's name must be like "GetEachFIntPointBPArray" or something like that


void AProceduralGen::SocketExclusionForLargeRoom(ARoomActor* Room)
{
	TArray<USceneComponent*> SceneComponents;
	Room->GetComponents<USceneComponent*>(SceneComponents);

	auto RemoveEnterExitSocketFromPool = [&]()
	{
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
	};

	auto GetAllSceneCompNameAddOffsetName = [&]()
	{
		TArray<FName> SceneCompNames;
		for (auto SceneComp : SceneComponents)
		{
			FString Name = SceneComp->GetFName().ToString();
			Name.Append(TEXT("_Exclude"));
			SceneCompNames.Add(FName(*Name));
		}
		return SceneCompNames;
	};

	auto GetOffsetFromGivenVarName = [&]()
	{
		for (TFieldIterator<FProperty> PropIt(Room->GetClass()); PropIt; ++PropIt)
		{
			FProperty* Prop = *PropIt;
			FStructProperty* StructProp = CastField<FStructProperty>(Prop);
			if (StructProp && StructProp->Struct == TBaseStructure<FIntPoint>::Get())
			{
				TArray<USceneComponent*> SceneComp;
				Room->GetComponents<USceneComponent*>(SceneComp);

				FIntPoint* IntPoint = StructProp->ContainerPtrToValuePtr<FIntPoint>(Room);
				FName ChoppedName = FName(*StructProp->GetName().LeftChop(7));
				for (auto SceneComponent : SceneComp)
				{
					if (ChoppedName == SceneComponent->GetFName())
					{
						return *IntPoint;
					}
				}
			}
		}
		return FIntPoint(0, 0);
	};

	RemoveEnterExitSocketFromPool();
	TArray<FName> SceneCompNames = GetAllSceneCompNameAddOffsetName();

	//Get the class of the Room
	UClass* RoomClass = Room->GetClass();

	// Iterate through all properties of the Room
	for (TFieldIterator<FProperty> PropIt(RoomClass); PropIt; ++PropIt)
	{
		FProperty* Prop = *PropIt;
		if (FArrayProperty* ArrayProp = CastField<FArrayProperty>(Prop))
		{
			FStructProperty* StructInnerProp = CastField<FStructProperty>(ArrayProp->Inner);
			if (StructInnerProp && StructInnerProp->Struct == TBaseStructure<FIntPoint>::Get())
			{
				for (auto Name : SceneCompNames)
				{
					if (StructInnerProp->GetFName() == Name)
					{
						// This is an array of FIntPoints. Do your logic here.
						FScriptArrayHelper_InContainer ArrayHelper(ArrayProp, Room);
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
										FIntPoint Offset = GetOffsetFromGivenVarName();

										int CurrentX = Index.X + Offset.X + IntPoint->X;
										int CurrentY = Index.Y + Offset.Y + IntPoint->Y;

										if (IsValid(CurrentX, CurrentY))
										{
											Tiles[CurrentX][CurrentY].Blocked = false;
											Tiles[CurrentX][CurrentY].Visited = false;
										}

										if (IsValid(CurrentX, CurrentY) && VisualizeAllExclusions)
										{
											DrawDebugBox(GetWorld(), Tiles[CurrentX][CurrentY].Location + FVector(TileSizeX / 2, TileSizeY / 2, 0), FVector(TileSizeX / 2, TileSizeY / 2, 0), FColor::Purple, true);
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

bool AProceduralGen::ConnectRoomsWithCorridors(ARoomActor*& Room)
{
	FRoomConnection Connection = CalculatePathInfo(Room);

	FIntPoint StartIndex = WorldToIndex(Connection.StartPoint);
	FIntPoint EndIndex = WorldToIndex(Connection.EndPoint);

	// Find a path from StartIndex to EndIndex:
	if (!FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y, Connection.PathStartOffset, Connection.PathEndOffset, SpawnCorridor, Connection.MaxCheckAmount, Room))
	{
		ResetAllVisited();
		return FindCorridorPath(StartIndex.X, StartIndex.Y, EndIndex.X, EndIndex.Y, Connection.PathStartOffset, Connection.PathEndOffset, SpawnCorridor, Connection.MaxCheckAmount, Room);
	}
	return true;
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

void AProceduralGen::SwapInvZYaxis(FVector& VectorToSwap)
{
	VectorToSwap.Y = -VectorToSwap.Z;
	VectorToSwap.Z = 0;
}

ARoomActor* AProceduralGen::SelectRoomWithDirection(const Direction EndSocketDirection, const bool CanSpawnLargeRoom, const bool OnlySpawnNoExit, TArray<ARoomActor*>* CustomArray, TSharedPtr<TArray<ARoomActor*>> ManualBranchRooms)
{
	SCOPE_CYCLE_COUNTER(STAT_SelectRoomWithDirection);
	//Lambda functions for condition checks
	auto IsLargeRoomAllowed = [&](const ARoomActor* Room) { return CanSpawnLargeRoom || !Room->LargeRoom; };
	auto IsNoExitStatusMatching = [&](const ARoomActor* Room) { return OnlySpawnNoExit == Room->NoExit; };

	TArray<ARoomActor*> IterateRoomDesigns = (CustomArray != nullptr) ? *CustomArray : CastedRooms;

	//Selection for side branch manual room selection
	if (ManualBranchRooms && !ManualBranchRooms->IsEmpty())
	{
		TArray<ARoomActor*> FirstDownCast = ManualBranchRooms.Get()[0];
		ARoomActor* FirstRoom = (FirstDownCast[0]);
		ManualBranchRooms->RemoveAt(0);
		if (CustomArray)
		{
			*CustomArray = *ManualBranchRooms.Get(); //Custom Array suppossed to be assigned by ref but not working. 
		}
		return FirstRoom;
	}
	
	//If DebugRoomSequence is given the sequence has to be selected in order. 
	if (!DebugRoomSequence.IsEmpty() && CurrentIndex < DebugRoomSequence.Num())
	{
		ARoomActor* SequenceRoom = Cast<ARoomActor>(DebugRoomSequence[CurrentIndex]->GetDefaultObject());
		CurrentIndex++;

		if (SequenceRoom->LargeRoom)
		{
			LargeRoomCounter++;
		}

		return SequenceRoom;
	}

	//Determine all the valid rooms could be selected 
	TArray<ARoomActor*> ValidRooms;
	for (auto RoomDesign : IterateRoomDesigns)
	{
		ARoomActor* RoomCandidate = Cast<ARoomActor>(RoomDesign);
		if (RoomCandidate && RoomCandidate->EnterSocketDirection == EndSocketDirection && IsLargeRoomAllowed(RoomCandidate) && IsNoExitStatusMatching(RoomCandidate))
		{
			ValidRooms.Add(RoomCandidate);
		}
		else if (CustomArray && !CustomArray->IsEmpty()) //For large room spawning. 
		{
			CustomArray->Remove(RoomCandidate);
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
	SCOPE_CYCLE_COUNTER(STAT_ForEachTileInRoom);
	if (!Room) return;

	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	SwapInvZYaxis(RelativeLoc);

	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent();

	if (Room->IsHorizontalStraightCorr)
	{
		int X = BoxExtends.X;
		int Z = BoxExtends.Z;
		BoxExtends = FVector(Z, BoxExtends.Y, X);
		WorldLoc -= FVector(TileSizeX, 0, 0);
	}

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

void AProceduralGen::SpawnCorridors(const int GoalX, const int GoalY, ARoomActor* OverlappedRoom)
{
	TArray<FVector> LocStack;
	TArray<FRotator> RotStack;
	TArray<EDirection2> DirStack;
	FTileStruct* Current = &Tiles[GoalX][GoalY];
	TArray<FTileStruct*> CurrentTracker;
	CurrentTracker.Add(Current);
	TSet<FTileStruct*> VisitedNodes;

	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;
	TArray<ARoomActor*> TurnCorridors;


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
					Corridor = GetWorld()->SpawnActor<ARoomActor>(StraightCorrClass, SpawnLoc, FirstCorrRot);
				}
				else
				{
					Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridorClass, SpawnLoc, FirstCorrRot);
					TurnCorridors.Add(Corridor);
				}
				SetTilesBlocked(Corridor, SpawnLoc);
				OverlappedRoom->OwnerCorridors.Add(Corridor);
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
			// Assuming TurnCorridorClass has the right rotation logic inside it
			FRotator TurnCorrRot = DetermineMiddleTurnRotation(CurrDir, NextDir);
			SpawnLoc.Z += 1;
			if (TurnCorrRot != FRotator(31, 31, 31))
			{
				ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridorClass, SpawnLoc, TurnCorrRot);
				TurnCorridors.Add(Corridor);
				SetTilesBlocked(Corridor, SpawnLoc);
				OverlappedRoom->OwnerCorridors.Add(Corridor);
				Corridor->IfCorridorOwnerRoom = OverlappedRoom;
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
			ARoomActor* Corridor = GetWorld()->SpawnActor<ARoomActor>(TurnCorridorClass, SpawnLoc, LastCorrRot);
			TurnCorridors.Add(Corridor);
			SetTilesBlocked(Corridor, SpawnLoc);
			OverlappedRoom->OwnerCorridors.Add(Corridor);
			Corridor->IfCorridorOwnerRoom = OverlappedRoom;

		}
	}
	LocStack.Pop();
	RotStack.Pop();
	CurrDir = NextDir;

	for (int i = 0; i < SpawnLocations.Num(); ++i)
	{
		// if (!IsColliding(StraightCorrClass->GetDefaultObject<ARoomActor>(),SpawnLocations[i]))
		{
			ARoomActor* NormalCorr = GetWorld()->SpawnActor<ARoomActor>(StraightCorrClass, SpawnLocations[i], SpawnRotations[i]);
			NormalCorr->IfCorridorOwnerRoom = OverlappedRoom;
			if (SpawnRotations[i] == FRotator(0, -90, -90))
			{
				NormalCorr->IsHorizontalStraightCorr = true;
			}

			SetTilesBlocked(NormalCorr, SpawnLocations[i]);
			OverlappedRoom->OwnerCorridors.Add(NormalCorr);

		}
	}
	for (auto TurnCorridor : TurnCorridors)
	{
		TArray<AActor*> OverlappingActors;
		TurnCorridor->GetOverlappingActors(OverlappingActors);
		for (auto OverlappingActor : OverlappingActors)
		{
			if (OverlappingActor->IsA(StraightCorrClass))
			{
				OverlappingActor->Destroy();
			}
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

	//For MoveOverlapRoomLocationTiles visualization
	if (VisualizeOverlappedRoomTiles)
	{ 
		for (int i = 0; i < MoveOverlapRoomLocationTiles.Num(); ++i)
		{
			FColor Color = (i == MoveOverlapRoomLocationTiles.Num() - 1) ? FColor::Red : FColor::White;
			const FIntPoint& Tile = MoveOverlapRoomLocationTiles[i];
			DrawDebugBox(GetWorld(), Tiles[Tile.X][Tile.Y].Location + TileBoxExtends, TileBoxExtends, Color,true);
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
	SCOPE_CYCLE_COUNTER(STAT_MoveOverlappedRoom);
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
				if (IsValid(x, y) && !VisitedTiles.Contains(FIntPoint(x, y)) &&
					(!IsColliding(NextRoom, Tiles[x][y].Location)) &&
					(!IsBufferZoneColliding(NextRoom, Tiles[x][y].Location)))
				{
					if (CanMakeCorridorPathBeforeSpawning(NextRoom, Tiles[x][y].Location))
					{
						NextRoomLocation = Tiles[x][y].Location;
						return true;
					}
				}
				++Attempts;
				VisitedTiles.Add(FIntPoint(x, y));
				MoveOverlapRoomLocationTiles.Add(FIntPoint(x,y));

				if (Attempts >= MaxMoveOverlappedRoomIterate)
				{
					UE_LOG(LogTemp, Warning, TEXT("Exceeded maximum attempts to find a valid spot for %s "), *NextRoom->GetName());
					return false; // This will exit the function early.
				}
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Nothing has been found"));
	return false; //TODO: I Think I need to create a dialog box telling that there is no available space for overlapped room
}

bool AProceduralGen::IsBufferZoneColliding(ARoomActor* Room, FVector SpawnLoc)
{
	int BufferX = BufferSize * TileSizeX;
	int BufferY = BufferSize * TileSizeY;
	//Box comp's World Location
	FVector RelativeLoc = Room->BoxComponent->GetRelativeLocation();
	SwapInvZYaxis(RelativeLoc);

	FVector WorldLoc = SpawnLoc + RelativeLoc;
	FVector BoxExtends = Room->BoxComponent->GetUnscaledBoxExtent() + FVector(BufferX, 0, BufferY);
	FVector TopLeftCorner = CalculateTopLeftCorner(WorldLoc, BoxExtends);
	FIntPoint StartIndex = WorldToIndex(TopLeftCorner);

	// Dimensions of each tile
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
				if (Tiles[CurrentTileX][CurrentTileZ].Blocked)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int AProceduralGen::MakeCorridorPathVisualization(ARoomActor* OverlappedRoom, FTileStruct* Current)
{
	FTileStruct* PrevNode = nullptr; // Keep track of the previous node
	FTileStruct* PathNode = Current;
	int PathCost = 0;

	while (PathNode != nullptr)
	{
		PathCost++;
		if (PathNode->Parent == PrevNode)
		{
			UE_LOG(LogTemp, Error, TEXT("Room %s Circular reference detected between nodes. Breaking out of loop."), *OverlappedRoom->GetName());
			break;
		}
		if (VisualizeCorridorPath)
		{
			DrawDebugBox(GetWorld(), Tiles[PathNode->X][PathNode->Y].Location + FVector(TileSizeX / 2, TileSizeY / 2, 0), FVector(TileSizeX / 2, TileSizeY / 2, TileSizeY), FColor::Red, true, -1, 0, 0);
		}
		PrevNode = PathNode;
		PathNode = PathNode->Parent;
	}
	return PathCost;
}

bool AProceduralGen::FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount, ARoomActor* OverlappedRoom)
{
	TArray<int> Row = {-1, 0, 0, 1};
	TArray<int> Col = {0, -1, 1, 0};
	TArray<FTileStruct*> OpenList;
	int SafeCheck = 0;
	int SecondCounter = 0;
	FoundPathCost = INT_MAX;


	auto ApplyOffsets = [&]()
	{
		StartX += StartOffset.X;
		StartY += StartOffset.Y;
		GoalX += EndOffset.X;
		GoalY += EndOffset.Y;
	};

	auto ShouldEarlyReturn = [&]()
	{
		if (!IsValid(StartX, StartY))
		{
			UE_LOG(LogTemp, Display, TEXT("Room %s Out of bound so I returned: %i, %i "), *OverlappedRoom->GetName(), StartX, StartY);
			return true;
		}
		if (!IsValid(GoalX, GoalY) || Tiles[GoalX][GoalY].Blocked)
		{
			UE_LOG(LogTemp, Error, TEXT("Room %s Goal tile is blocked or not valid. Disable visualize overlaps. Enable Visualize Begin and End tiles. Manually offset the Path End Offset."), *OverlappedRoom->GetName());
			return true;
		}
		return false;
	};

	auto SetFirstCorrRotation = [&](FTileStruct* Start)
	{
		if (LastSpawnedRoom->ExitSocketDirection == HorizontalRight || LastSpawnedRoom->ExitSocketDirection == HorizontalLeft)
			Start->Rotation = FRotator(0, 0, -90);
		else
		{
			Start->Rotation = FRotator(0, 90, -90); //(Pitch=0.000000,Yaw=90.000000,Roll=-90.000000)
		}
	};

	auto InitializeStartNode = [&]()
	{
		// StartX++;
		FTileStruct* Start = &Tiles[StartX][StartY];
		Start->Visited = true;
		Start->HCost = FPathNode::GetHCost(StartX, StartY, GoalX, GoalY);
		SetFirstCorrRotation(Start);
		OpenList.Add(Start);
	};

	//No sorting involved! 
	auto GetMinimumFCostTile = [&]()
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
		return Current;
	};

	auto FindNeighbor = [&](FTileStruct* Current)
	{
		for (int i = 0; i < 4; i++)
		{
			SecondCounter++;
			int NewX = Current->X + Row[i];
			int NewY = Current->Y + Col[i];
			FVector TileWorldPos = IndexToWorld(NewX, NewY);
			ARoomActor* Corridor = Cast<ARoomActor>(TurnCorridorClass->GetDefaultObject());

			if (IsValid(NewX, NewY) && !Tiles[NewX][NewY].Visited && !IsColliding(Corridor, TileWorldPos))
			{
				FTileStruct* Neighbour = &Tiles[NewX][NewY];
				int NewMovementCostToNeighbour = Current->GCost + 1; // assuming each move costs 1

				if (NewMovementCostToNeighbour < Neighbour->GCost || !OpenList.Contains(Neighbour))
				{
					Neighbour->GCost = NewMovementCostToNeighbour;
					Neighbour->HCost = FPathNode::GetHCost(NewX, NewY, GoalX, GoalY);
					Neighbour->Parent = Current;
					DeterminePathDirection(Current, NewX, NewY, Neighbour);
					OpenList.Add(Neighbour);
				}
				Tiles[NewX][NewY].Visited = true;
			}
		}
	};


	ApplyOffsets();
	if (ShouldEarlyReturn()) return false;
	InitializeStartNode();

	while (OpenList.Num() > 0 && SafeCheck < MaxIterationAmount)
	{
		FTileStruct* Current = GetMinimumFCostTile();

		if (Current->X == GoalX && Current->Y == GoalY)
		{
			if (SpawnCorr)
			{
				SpawnCorridors(GoalX, GoalY, OverlappedRoom);
			}
			else
			{
				ResetAllVisited();
			}

			OverlappedRoom->PathCost = MakeCorridorPathVisualization(OverlappedRoom, Current);
			UE_LOG(LogTemp, Error, TEXT("Safecheck: %i"), SafeCheck);
			return true;
		}
		else
		{
			FindNeighbor(Current);
			SafeCheck++;
		}
	}

	if (SafeCheck >= MaxIterationAmount)
		UE_LOG(LogTemp, Error, TEXT("Room %s No corridor path found Number of iteration is : %d, %d. If iteration is high, end path couldn't found. If iteration is small, (0-10 begin path not found"), *OverlappedRoom->GetName(), SafeCheck,
	       SecondCounter);

	if (SafeCheck < MaxIterationAmount)
		UE_LOG(LogTemp, Error, TEXT("Room %s No available path found. Iterated 4 times just 4 direction. Make sure Path Start is not overlapping. Disable Overlap Visualization and enable Start&End visualiztion"), *OverlappedRoom->GetName());

	UE_LOG(LogTemp, Error, TEXT("Safecheck: %i"), SafeCheck);
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
