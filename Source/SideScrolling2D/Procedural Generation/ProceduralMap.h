// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomActor.h"
#include "ProceduralMap.generated.h"

class ADoorActor;

UENUM()
enum EDirection2 : uint8
{
	Dir_Left,
	Dir_Right,
	Dir_Up,
	Dir_Down,
	Dir_None
};

USTRUCT()
struct FPathNode
{
	GENERATED_BODY()
	bool Visited = false;
	int X = 0;
	int Y = 0;
	int HCost = 0;
	int GCost = 0;
	FPathNode* Parent = nullptr;
	EDirection2 Direction = EDirection2::Dir_None;
	FRotator Rotation = FRotator(0,0,0);
	static int GetHCost(int StartX, int StartY, int GoalX, int GoalY)
	{
		return FMath::Abs(StartX - GoalX) + FMath::Abs(StartY - GoalY);
	}
	int FCost()
	{
		return GCost + HCost;
	}

};
//Merged Path Into Tile
USTRUCT()
struct FTileStruct
{
	GENERATED_BODY()
	bool Blocked = false;
	bool Path = false;
	FVector Location = FVector(0,0,0); //Rest is for pathfinding

	
	bool Visited = false;
	int X = 0;
	int Y = 0;
	int HCost = 0;
	int GCost = 0;
	FTileStruct* Parent;
	EDirection2 Direction = EDirection2::Dir_None;
	FRotator Rotation = FRotator(0,0,0);
	static int GetHCost(int StartX, int StartY, int GoalX, int GoalY)
	{
		return FMath::Abs(StartX - GoalX) + FMath::Abs(StartY - GoalY);
	}
	int FCost()
	{
		return GCost + HCost;
	}
};

UCLASS()
class SIDESCROLLING2D_API AProceduralMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralMap();
	
	UPROPERTY()
	ARoomActor* LastSpawnedRoom;

	UPROPERTY()
	ARoomActor* LastSpawnedBranchRoom;
	
	UPROPERTY()
	TArray<FVector> CorridorTiles;

	FName NextRoomExitTag;

	UPROPERTY()
	TArray<ARoomActor*> SpawnedRooms;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<ARoomActor>> RoomDesigns;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> StraightCorr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> TurnCorridor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ADoorActor> Door;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector FirstRoomStartLoc;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector TileBoxExtend;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfRooms = 30;
	int SpawnedRoomCount;
	int SpawnedBranchRoomCount;

	//How long the tile must be. 50x50 is too low and it might have infinite loop
	//I considered to make all the Map overlap logic with tiles but for 3D compatibility, I decided to entire room actor collision check with it's box collision. 
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MapSizeX = 300;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MapSizeY = 300;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int TileSizeX = 64;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int TileSizeY = 64;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector> Results;

	/*
	 How much space there must be when moving overlapped room. 
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int TileOffset = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CorridorOffset = 1;


	TArray<TArray<FTileStruct>> Tiles;
	TArray<TArray<FPathNode>> FPathNodes;
	
	//Relative Locations for Tile indexes
	int StartX;
	int StartY;

	/*
	 Start Location for tiles. Center location is the area where tiles and all collision checks must be done. But All the tiles would spawn top left corner of the collision check.
	 In order to center all of my spawned tiles at the center of the collision check, I had to offset their initial spawn location. This Vector is the location of first offset location. 
	 */
	FVector StartLocation;


	/*
	 Main function. Based on previous spawned rooms exit socket tag, it will try to spawn a room with correct corresponded tag. 
	 */
	void GenerateMap();

	void SetTilesBlocked(ARoomActor* Room, FVector SpawnLoc);
	/*
	 Place where most of the functions are used. It'll try to spawn if not collided. If collided, Make all the collision & tile checks and spawn corridor to connect them.
	 */
	void SpawnRoom(FName Tag);

	/*
	 This will make a raycast around box component. For rooms checking if new room about to spawn is colliding with previous one
	 */
	bool IsColliding(ARoomActor* RoomActor, const FVector& SpawnLoc); //For rooms
	bool IsEndSocketColliding(const FVector& SpawnLoc); //For rooms

	/*
	 *Collision check for corridors
	 */
	bool IsColliding(FVector& SpawnLoc);


	/*
	 Initialized Tiles and nodes. If One of tiles are overlapped, set them as visited. Last SpawnedROom has been added because for other branches and main branch, I need to determine which is which
	 */
	void InitializeGrid(ARoomActor* LastSpawnRoom, FVector* SocketExitLoc);

	bool FindCorridorPath(int goalX, int goalY);
	void SpawnCorridors(int goalX, int goalY);
	void DrawPath();

	/*
	 When overlapped, it will try to find a tile position where it doesn't overlap anymore. It'll do this with iterative expansion lookup pattern. And if it found, it'll also offset minimum
	 2 times on X and Y axis to give minimum space to connect corridors. 
	 */
	void MoveOverlappedRoom(ARoomActor* NextRoom, FVector& NextRoomLocation);

	/*
	 * FIX THIS WEIRD LOGIC. LOGIC MUSTN'T WORK BUT SOMEHOW THIS WORKS

	 */
	bool IsAdjacentTilesColliding(ARoomActor* Room, int X, int Y);
	bool IsAdjacentCorrColliding(int X, int Y);

	void StartNewBranch(ARoomActor* NextBranchRoom, FVector& NextRoomLocation, int RandomValue);

	
	inline bool IsValid(int x, int y)
	{
		return x >= 0 && x < MapSizeX && y >= 0 && y < MapSizeY;
	}

	inline FIntPoint WorldToIndex(FVector WorldLocation)
	{
		int TileX = FMath::RoundToInt(WorldLocation.X / TileSizeX);
		int TileY = FMath::RoundToInt(WorldLocation.Y / TileSizeY);
		return FIntPoint(TileX,TileY);
	}

	/*
	 Convert Index 2D array position to World location. 
	 */
	inline FVector IndexToWorldPosition(int xIndex, int yIndex) {
		return StartLocation + FVector(xIndex * TileSizeX, yIndex * TileSizeY, 0.f);
	}

	inline void DeterminePathDirection(FPathNode* Current, int X, int Y, FPathNode* Node)
	{
		if (X > Current->X)
		{
			Node->Direction = EDirection2::Dir_Right;
			Node->Rotation = FRotator(0, 0.0f, -90.0f);
		}

		else if (X < Current->X)
		{
			Node->Direction = EDirection2::Dir_Left;
			Node->Rotation = FRotator(0, 0.0f, -90.0f);
		}

		// Moving vertically
		if (Y > Current->Y)
		{
			Node->Direction = EDirection2::Dir_Down;
			Node->Rotation = FRotator(0, -90.0f, -90.0f);
		}
		else if (Y < Current->Y)
		{
			Node->Direction = EDirection2::Dir_Up;
			Node->Rotation = FRotator(0, -90.0f, -90.0f);
		}
	}

	inline void DetermineStartPathDirection(FPathNode* Start)
	{
		FName Tag = LastSpawnedRoom->DoorSocketExit->ComponentTags[0];
		if (Tag == "SideRight") 
		{
			Start->Rotation = FRotator(0, 0.0f, -90.0f);
			Start->Direction = EDirection2::Dir_Right;
			StartX += 1;
		}
		else if (Tag == "SideLeft")
		{
			Start->Rotation = FRotator(0, 0.0f, -90.0f);
			Start->Direction = EDirection2::Dir_Left;
			StartY -= 1;
		}
		else if (Tag == "StraightUp") // Moving vertically
			{
			Start->Rotation = FRotator(0, -90.0f, -90.0f);
			Start->Direction = EDirection2::Dir_Up;
			StartY += 1;
			}
		else if (Tag == "StraightDown")
		{
			Start->Rotation = FRotator(0, -90.0f, -90.0f);
			Start->Direction = EDirection2::Dir_Down;
			StartY -= 1;

		}
	}
	inline FRotator DetermineFirstTurnRotation(EDirection2 NextDir)
	{
		if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideRight"))
		{
			if (NextDir == EDirection2::Dir_Up)
			{
				return FRotator(0, 180, -90);
			}
			else if (NextDir == EDirection2::Dir_Down)
			{
				return FRotator(0, 90, -90);
			}
		}

		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideLeft"))
		{
			if (NextDir == EDirection2::Dir_Down)
			{
				return FRotator(0, 0, -90);
			}
			else if (NextDir == EDirection2::Dir_Up)
			{
				//(Pitch=0.000000,Yaw=-89.999999,Roll=-90.000000)
				return FRotator(0, -90, -90);
			}
		}

		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightUp"))
		{
			if (NextDir == EDirection2::Dir_Right)
			{
				return FRotator(0, 0, -90);
			}
			else if (NextDir == EDirection2::Dir_Left)
			{
				return FRotator(0, -270, -90);
			}
		}

		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightDown"))
		{
			if (NextDir == EDirection2::Dir_Right)
			{
				return  FRotator(0, -90, -90);
			}
			else if (NextDir == EDirection2::Dir_Left)
			{
				return FRotator(0, 180, -90);
			}
		}
		return FRotator(31,31,31);
	}
	inline FRotator DetermineTurnRotation(EDirection2 CurrDir, EDirection2 NextDir)
	{
		if (CurrDir == EDirection2::Dir_Up && NextDir == EDirection2::Dir_Left)
		{
			return FRotator(0,-270,-90);
		}
		if (CurrDir == EDirection2::Dir_Down && NextDir == EDirection2::Dir_Right)
		{
			return  FRotator(0,-90,-90);
		}
		if (CurrDir == EDirection2::Dir_Left && NextDir == EDirection2::Dir_Up)
		{
			return  FRotator(0,-90,-90);
		}
		if (CurrDir == EDirection2::Dir_Up && NextDir == EDirection2::Dir_Right)
		{
			return  FRotator(0,0,-90);
		}
		if (CurrDir == EDirection2::Dir_Right && NextDir == EDirection2::Dir_Up)
		{
			return  FRotator(0,-180,-90);
		}
		if (CurrDir == EDirection2::Dir_Right && NextDir == EDirection2::Dir_Down)
		{
			return  FRotator(0,90,-90);
		}
		if (CurrDir == EDirection2::Dir_Down && NextDir == EDirection2::Dir_Left)
		{
			return  FRotator(0,180,-90);
		}
		if (CurrDir == EDirection2::Dir_Left && NextDir == EDirection2::Dir_Down)
		{
			return  FRotator(0,0,-90);
		}
		return FRotator(31,31,31);
	}

	inline FRotator DetermineLastCorrRotation(EDirection2 LastDir)
	{
		if (LastDir == EDirection2::Dir_Up && NextRoomExitTag == "SideLeft") return FRotator(0, -270, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomExitTag == "SideRight") return FRotator(0, -90, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomExitTag == "StraightUp") return FRotator(0, -90, -90);
		if (LastDir == EDirection2::Dir_Up && NextRoomExitTag == "SideRight") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Right && NextRoomExitTag == "StraightUp") return FRotator(0, -180, -90);
		if (LastDir == EDirection2::Dir_Right && NextRoomExitTag == "StraightDown") return FRotator(0, 90, -90);
		if (LastDir == EDirection2::Dir_Right && NextRoomExitTag == "SideLeft") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomExitTag == "SideRight") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomExitTag == "StraightUp") return FRotator(0, 90, -90);
		if (LastDir == EDirection2::Dir_Up && NextRoomExitTag == "StraightDown") return FRotator(0, 90, -90);
		return FRotator(31, 31, 31);
	}
	inline EDirection2 ConvertNextRoomExitTagToDirection()
	{
		if (NextRoomExitTag == "SideRight") return EDirection2::Dir_Right;
		if (NextRoomExitTag == "SideLeft")	return EDirection2::Dir_Left;
		if (NextRoomExitTag == "StraightUp") return EDirection2::Dir_Up;
		if (NextRoomExitTag == "StraightDown") return EDirection2::Dir_Down;
		return EDirection2::Dir_None;
	}
	inline FName ExpectedTag(FName Name)
	{
		if (Name == "SideRight") return "SideLeft";
		if (Name == "SideLeft") return "SideRight";
		if (Name == "StraightUp") return "StraightDown";
		if (Name == "StraightDown") return "StraightUp";
		return "Dir_None";
	}


	

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
