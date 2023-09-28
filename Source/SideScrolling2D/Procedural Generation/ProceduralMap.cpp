// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMap.h"
#include <stack>
#include "Components/BoxComponent.h"
#include "Door/DoorActor.h"


// Sets default values

AProceduralMap::AProceduralMap()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProceduralMap::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Delayer;
	GetWorldTimerManager().SetTimer(Delayer, this, &AProceduralMap::GenerateMap, 0.1f, false);
}

void AProceduralMap::GenerateMap()
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[0], FirstRoomStartLoc, Rotation);
	GetWorld()->SpawnActor<ADoorActor>(Door,FirstRoom->DoorSocketExit->GetComponentLocation(), Rotation);

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
	
	for (int x = 0; x < MapSizeX; ++x)
	{
		for (int y = 0; y < MapSizeY; ++y)
		{
			if (Tiles[x][y].Blocked)
			{
				DrawDebugBox(GetWorld(), Tiles[x][y].Location, TileBoxExtend, FColor::Red, true);
			}
		}
	}
}

void AProceduralMap::SetTilesBlocked(ARoomActor* Room, FVector SpawnLoc)
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

void AProceduralMap::SpawnRoom(FName Tag)
{
 	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	FVector NextRoomLocation = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
	int RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
	ARoomActor* NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	NextRoomExitTag = NextRoom->DoorSocketExit->ComponentTags[0];

	//Find a correct room. 
	while (!NextRoom->DoorSocketEnter->ComponentHasTag(Tag))
	{
		RandomIndex = FMath::RandRange(0, RoomDesigns.Num() - 1);
		NextRoom = Cast<ARoomActor>(RoomDesigns[RandomIndex]->GetDefaultObject());
	}
	
	//For main branch
	//First check if the room is correct and then check if it colliding if yes, it means it's time to spawn it in a loc doesn't overlap. 
	if (NextRoom->DoorSocketEnter->ComponentHasTag(Tag) && NextRoom->ActorHasTag("NoExit") == false)
	{
		//If room overlaps with previous room's door exit location
		if (!IsColliding(NextRoom, NextRoomLocation))
		{
			NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
			SpawnedRooms.Add(NextRoom); // Add this line after spawning the room.
			LastSpawnedRoom = NextRoom;
			GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
			
		}
		else
		{
			FVector ExitLoc = LastSpawnedRoom->DoorSocketExit->GetComponentLocation();
			InitializeGrid(LastSpawnedRoom, &ExitLoc);
			MoveOverlappedRoom(NextRoom, NextRoomLocation);
			NextRoom = GetWorld()->SpawnActor<ARoomActor>(RoomDesigns[RandomIndex], NextRoomLocation, Rotation);
			SpawnedRooms.Add(NextRoom);
			LastSpawnedRoom = NextRoom;
			GetWorld()->SpawnActor<ADoorActor>(Door,LastSpawnedRoom->DoorSocketExit->GetComponentLocation(), Rotation);
		}
	}
}

//For rooms checking if new room about to spawn is colliding with previous one
//TODO: MAKE A DECISION WHETHER TILESIZE BE 16X16 OR 64X64

void AProceduralMap::InitializeGrid(ARoomActor* LastSpawnRoom, FVector* SocketExitLoc)
{
	const FVector CenterLocation = *SocketExitLoc;
	StartLocation = CenterLocation - FVector((MapSizeX * TileSizeX) / 2.0f, (MapSizeY * TileSizeY) / 2.0f, 0.f);
	StartX = FMath::TruncToInt((SocketExitLoc->X - StartLocation.X) / TileSizeX);
	StartY = FMath::TruncToInt((SocketExitLoc->Y - StartLocation.Y) / TileSizeY);
	//resize tiles array
	Tiles.SetNum(MapSizeX);
	for (int i = 0; i < MapSizeX; ++i)
		Tiles[i].SetNum(MapSizeY);
	//resize Nodes
	FPathNodes.SetNum(MapSizeX);
	for (int i = 0; i < MapSizeX; ++i)
		FPathNodes[i].SetNum(MapSizeY);

	//Init the Tile structs
	for (int x = 0; x < MapSizeX; ++x)
	{
		for (int y = 0; y < MapSizeY; ++y)
		{
			//For each tile generation, visited must be set false by default. Otherwise, it will remain true for next tile generations. 
			FPathNodes[x][y].Visited = false;
			FPathNodes[x][y].Parent = nullptr;
			
			
			//Set Tiles blocked true and give all default init for PathNodes 
			FVector TileLocation = StartLocation + FVector(x * TileSizeX, y * TileSizeY, 0.f);
			Tiles[x][y].Blocked = false; // set everything to default values before starting
			if (IsColliding(TileLocation)) //If Tile is overlapping
			{
				Tiles[x][y].Blocked = true;
				FPathNodes[x][y].Visited = true;
			}

			Tiles[x][y].Location = TileLocation;
			FPathNodes[x][y].X = x;
			FPathNodes[x][y].Y = y;
		}
	}
}

//room
bool AProceduralMap::IsEndSocketColliding(const FVector& SpawnLoc)
{
	const FRotator Rotation = FRotator(0, 0, 0);
	const FQuat QuatRotation = Rotation.Quaternion();

	FVector BoxExtent = FVector(64,64,64);
	const FVector BoxCenter = SpawnLoc + FVector(TileSizeX / 2.0f, TileSizeY / 2.0f, 0);
	TArray<FOverlapResult> Overlaps;
	const bool bOverlaps = GetWorld()->OverlapMultiByChannel(Overlaps, BoxCenter, QuatRotation, ECC_GameTraceChannel2, FCollisionShape::MakeBox(BoxExtent));
	return bOverlaps;
}

bool AProceduralMap::IsColliding(ARoomActor* RoomActor, const FVector& SpawnLoc)
{
	const FRotator Rotation = FRotator(0, 0, -90);
	const FVector BoxExtent = RoomActor->BoxComponent->GetScaledBoxExtent();
	const FVector BoxRelativeLoc = RoomActor->BoxComponent->GetRelativeLocation();

	const FQuat QuatRotation = Rotation.Quaternion();
	const FVector BoxCenter = SpawnLoc + QuatRotation.RotateVector(BoxRelativeLoc);
	// DrawDebugBox(GetWorld(), BoxCenter, BoxExtent, QuatRotation, FColor::Emerald, true, 1000.0f);

	TArray<FOverlapResult> Overlaps;
	const bool bOverlaps = GetWorld()->OverlapMultiByChannel(Overlaps, BoxCenter, QuatRotation, ECC_GameTraceChannel2,
	                                                         FCollisionShape::MakeBox(BoxExtent));
	// if (IsEndSocketColliding(SpawnLoc))
	// {
	// 	return true; 
	// }
	return bOverlaps;
}

//tile
bool AProceduralMap::IsColliding(FVector& SpawnLoc)
{
	const FRotator Rotation = FRotator(0, 0, 0);
	const FVector BoxCenter = SpawnLoc + FVector(TileSizeX / 2.0f, TileSizeY / 2.0f,0);
	const FQuat QuatRotation = Rotation.Quaternion();

	TArray<FOverlapResult> Overlaps;
	const bool bOverlaps = GetWorld()->OverlapMultiByChannel(Overlaps, BoxCenter, QuatRotation, ECC_GameTraceChannel2, FCollisionShape::MakeBox(TileBoxExtend));
	return bOverlaps;
}



bool AProceduralMap::FindCorridorPath(int goalX, int goalY)
{
	TArray<int> row = {-1, 0, 0, 1};
	TArray<int> col = {0, -1, 1, 0};
	TArray<FPathNode*> OpenList;

	
	if (!IsValid(StartX,StartY))
	{
		UE_LOG(LogTemp, Display, TEXT("Out of bound so I returned: %i, %i "), StartX, StartY);
		return false;
	}
	// StartX++;
	FPathNode* Start = &FPathNodes[StartX][StartY];
	DetermineStartPathDirection(Start);
	Start = &FPathNodes[StartX][StartY];
	
	Start->Visited = true;
	Start->HCost = FPathNode::GetHCost(StartX, StartY, goalX, goalY);
	OpenList.Add(Start);

	while (OpenList.Num() > 0)
	{
		// Find the node with the smallest FCost
		int minIndex = 0;
		for (int i = 1; i < OpenList.Num(); ++i)
		{
			if (OpenList[i]->FCost() < OpenList[minIndex]->FCost())
				minIndex = i;
		}

		FPathNode* Current = OpenList[minIndex];
		OpenList.RemoveAt(minIndex);

		if (Current->X == goalX && Current->Y == goalY)
		{
			SpawnCorridors(goalX,goalY);
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			int newX = Current->X + row[i];
			int newY = Current->Y + col[i];
			FVector TileWorldPos = IndexToWorldPosition(newX,newY);
			
			if (IsValid(newX, newY) && !FPathNodes[newX][newY].Visited && !IsColliding(TileWorldPos) && !IsAdjacentCorrColliding(newX,newY))
			{
				
				FPathNode* Neighbour = &FPathNodes[newX][newY];
				int newMovementCostToNeighbour = Current->GCost + 1; // assuming each move costs 1

				if (newMovementCostToNeighbour < Neighbour->GCost || !OpenList.Contains(Neighbour))
				{
					Neighbour->GCost = newMovementCostToNeighbour;
					Neighbour->HCost = FPathNode::GetHCost(newX, newY, goalX, goalY);
					Neighbour->Parent = Current;

					// Set rotation based on direction of movement

					// Moving horizontally
					CorridorTiles.Add(TileWorldPos);
					DeterminePathDirection(Current, newX, newY, Neighbour);
					OpenList.Add(Neighbour);
				}

				FPathNodes[newX][newY].Visited = true;
			}
		}
	}
	return false; 

}

void AProceduralMap::SpawnCorridors(int goalX, int goalY)
{
	std::stack<FVector> LocStack;
	std::stack<FRotator> RotStack;
	std::stack<EDirection2> DirStack;
	FPathNode* Current = &FPathNodes[goalX][goalY];

	TSet<FPathNode*> VisitedNodes;

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
		DirStack.push(FPathNodes[Current->X][Current->Y].Direction);
		RotStack.push(FPathNodes[Current->X][Current->Y].Rotation);
		Current = Current->Parent;
	}

	
	//First assign CurrDir and pop it from DirStack
	EDirection2 CurrDir = DirStack.top();
	DirStack.pop();

	//Secondly peek next dir after popping CurrDir previously
	EDirection2 NextDir = DirStack.top();

	// First corridor logic
	if (!LocStack.empty())
	{
		//Check first current and next corr dir and spawn straight if not spawn turned in else 
		FVector SpawnLoc = LocStack.top() - FVector(TileSizeX / 2, TileSizeY / 2, 0);
		if (CurrDir == NextDir)
		{
			GetWorld()->SpawnActor(StraightCorr, &SpawnLoc, &RotStack.top());
		}
		else
		{
			//First corridor is not straight. It will be turned. 
			FRotator FirstCorrRot = DetermineFirstTurnRotation(NextDir);
			
			//Assigning rot is done. Now spawn turned corr
			GetWorld()->SpawnActor(TurnCorridor, &SpawnLoc, &FirstCorrRot);
		}
		
		Results.Add(LocStack.top());
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
			NextDir = EDirection2::Dir_None;
		}

		FVector SpawnLoc = LocStack.top() - FVector(TileSizeX /2, TileSizeY / 2, 0);
		if (CurrDir == NextDir)
		{
			GetWorld()->SpawnActor(StraightCorr, &SpawnLoc, &RotStack.top());
		}
		else
		{
			// Assuming TurnCorridor has the right rotation logic inside it
			FRotator TurnCorrRot = DetermineTurnRotation(CurrDir, NextDir);
			GetWorld()->SpawnActor(TurnCorridor, &SpawnLoc, &TurnCorrRot);
		}
		Results.Add(LocStack.top());
		LocStack.pop();
		RotStack.pop();
		CurrDir = NextDir;
	}
	
	//Last corridor logic. After while loop over last corridor will be left
	FVector SpawnLoc = LocStack.top() - FVector(TileSizeX / 2, TileSizeY /2, 0);
	FRotator LastCorrRot = DetermineLastCorrRotation(CurrDir);
	
	if (CurrDir == ConvertNextRoomExitTagToDirection())
		GetWorld()->SpawnActor(StraightCorr, &SpawnLoc, &RotStack.top());
	else
		GetWorld()->SpawnActor(TurnCorridor, &SpawnLoc, &LastCorrRot);
	
	Results.Add(LocStack.top());
	LocStack.pop();
	RotStack.pop();
	CurrDir = NextDir;
	
	DrawPath();
}

void AProceduralMap::DrawPath()
{
	for (auto Result : Results)
	{
		FVector boxSize = FVector(TileSizeX / 2.0f, TileSizeY / 2.0f, 50); // Half the tile size in each direction
		FVector DrawResult = Result - FVector(TileSizeX / 2.0f, TileSizeY / 2.0f, -5);
		DrawDebugBox(GetWorld(), DrawResult, boxSize, FColor::Green, true, 10, 0, 0);
	}
}

//IF GRID SIZE IS TOO LOW LIKE 50X50 IT POSSIBLE IT CANNOT FIND ANYTHING AND STUCK INFINITE LOOP Also this is iterative expansion 


void AProceduralMap::MoveOverlappedRoom(ARoomActor* NextRoom, FVector& NextRoomLocation)
{
	const int MAX_ATTEMPTS = 10000;
	int attempts = 0;

	int centerX = MapSizeX / 2;
	int centerY = MapSizeY / 2;
	int maxDistance = FMath::Max(MapSizeX, MapSizeY);

	for (int dist = 1; dist <= maxDistance; ++dist) 
	{
		for (int x = centerX - dist; x <= centerX + dist; ++x) 
		{
			for (int y = centerY - dist; y <= centerY + dist; ++y) 
			{
				// Ensure the positions are within the grid bounds
				if (IsValid(x, y)) 
				{
					if (!IsColliding(NextRoom, Tiles[x][y].Location) && !IsAdjacentTilesColliding(NextRoom, x, y)) 
					{
						if (FindCorridorPath(x,y))
						{
							NextRoomLocation = Tiles[x][y].Location;
							return;
						}
					}
				}

				++attempts;
				if (attempts >= MAX_ATTEMPTS)
				{
					UE_LOG(LogTemp, Warning, TEXT("Exceeded maximum attempts to find a valid spot!"));
					return; // This will exit the function early.
				}
			}
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Nothing has been found"));
	// If you reach here, no valid spot was found. Handle this scenario as needed.
}


bool AProceduralMap::IsAdjacentTilesColliding(ARoomActor* Room, int X, int Y)
{
	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};

	for (int dir = 0; dir < 4; ++dir)
	{
		for (int offset = 1; offset <= TileOffset; ++offset) 
		{
			int NewX = X + (dx[dir] * offset);
			int NewY = Y + (dy[dir] * offset);

			// Ensure the positions are within the grid bounds
			if (IsValid(NewX, NewY))
				if (IsColliding(Room, Tiles[NewX][NewY].Location))
					return true;
		}
	}
	return false;
}

bool AProceduralMap::IsAdjacentCorrColliding(int X, int Y)
{
	int dx[4] = {1,-1,0,0};
	int dy[4] = {0,0,1,-1};

	for (int dir = 0; dir < 4; ++dir)
	{
		for (int i = 0; i < CorridorOffset; ++i)
		{
			int NewX = X + (dx[dir] * CorridorOffset);
			int NewY = Y + (dy[dir] * CorridorOffset);
			
			//Ensure the positions are withing the grid bounds
			if (IsValid(NewX,NewY))
				if (IsColliding(Tiles[NewX][NewY].Location))
					return true;
		}
	}
	return false; 
}


// Called when the game starts or when spawned

// Called every frame
void AProceduralMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


