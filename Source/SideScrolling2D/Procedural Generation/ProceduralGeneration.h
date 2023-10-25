// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "ProceduralGeneration.generated.h"

struct FTileStruct;
class ADoorActor;
class ARoomActor;

USTRUCT()
struct FRoomConnection
{
	GENERATED_BODY()

	FVector StartPoint;  // The exit point of a room
	FVector EndPoint;    // The entry point of the next room
	FIntPoint PathStartOffset; 
	FIntPoint PathEndOffset;
	int MaxCheckAmount;

	FString RoomName;
};

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
class SIDESCROLLING2D_API AProceduralGeneration : public AActor
{
	GENERATED_BODY()

public:
	AProceduralGeneration();
	
	/* Meant to be changed later on*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> StraightCorr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> TurnCorridor;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite)
	// TSubclassOf<ADoorActor> Door;

	UPROPERTY()
	TArray<ARoomActor*> LargeRooms;

	/*Add all the rooms to be randomly select and spawned.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 1))
	TArray<TSubclassOf<ARoomActor>> RoomDesigns;
	
	/*Total number of rooms to be spawned*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 2))
	int NumberOfRooms = 10;

	/*Valid for both main and side branching*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 3))
	int MaxLargeRoomCount = 5;
	
	/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 4))
	int MapSizeX = 1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 5))
	/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/
	int MapSizeY = 1000;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 6))
	/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/
	int TileSizeX = 16;
	/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 7))
	int TileSizeY = 16;

	/* Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.
	 * A larger value will create a larger distance from other rooms.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 8))
	int BufferSize = 6;

	/*Not yet implemented*/
	// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 9))
	// int MaxPathCostLimit = 1000;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 10))
	int NormalRoomMaxSafeCheck = 5000;

	/*When room is moved, this is the one to check never mind update here later*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 11))
	int LargeRoomMaxSafeCheck = 2000;

	/*How many side branch room in total should it spawn when side branching*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Side Branching", meta=(DisplayPriority = 1))
	int MaxSideBranchRoom = 50;

	/*The max branch length for side branching*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Side Branching", meta=(DisplayPriority = 2))
	int BranchLength = 4;

	/*Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 1))
	TArray<int32> RoomSequence;

	/*For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 2))
	TArray<FVector> BlockRoomLocations;
	
	/*Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 3))
	TSubclassOf<ARoomActor> BlockRoom;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 4))
	bool VisualiseOverlaps = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 5))
	bool VisualiseVisited = false;
	
	/*Begin and End socket visualization color is Cyan*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 6))
	bool VisualizeBeginAndEndTiles = true;

	/*Path visualization color is red*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 7))
	bool VisualizeCorridorPath = true;
	
	/*All excluded tiles are purple*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 8))
	bool VisualizeAllExclusions = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 10))
	bool VisualizeEndSocketOverlapCheck = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 11))
	bool SpawnCorridor = true;
	
	
	/* Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)*/
	UPROPERTY()
	ARoomActor* LastSpawnedRoom;
	
	/* Stored to make calculations for Last Spawned LARGE Room.*/
	UPROPERTY()
	ARoomActor* LastSpawnLargeRoom;

	/*for IsEndSocketOverlapping, don't display message box more than once for same rooms*/
	UPROPERTY()
	ARoomActor* LastCheckedRoom = nullptr;

	/*Which room set as blocked*/
	TMap<TWeakObjectPtr<ARoomActor>, TArray<FIntPoint>> RoomExclusions;

	/*2D tiles array for make all the tile checks like assigning each tile as blocked or finding a* costs.*/
	TArray<TArray<FTileStruct>> Tiles;
	
	/*For determining Corridor directions, rotations */
	FName NextRoomExitTag;
	FName NextRoomEnterTag;
	TArray<FRoomConnection> RoomConnections;
	
	int CurrentIndex = 0;
	int RecursiveCallAmount = 0;
	
	/*Room spawn counter. It will increment as new rooms are spawned*/
	int SpawnedRoomCount;
	
	int NumOfSideBranchRoom;
	
	float CurrentDistance;
	float PreviousDistance = FLT_MAX;  // start with a very large value
	int FoundPathCost;
	
	int LargeRoomCounter = 0;

	TArray<FIntPoint> BlockedTileHolder;

	/*First room Start location is set to be center of the map (map size /2). Later on make it */
	FVector FirstRoomStartLoc;
	int SafeCheckAmount;
	bool DrawOnce = true;

	/*After the overlapped room is moved to appropriate location, with given necessary information, it will make pathfinding from previous room's exit socket to new spawned overlapped room's enter location
	 * Responsible to call FindCorridorPath
	 */
	
	/*Based on previous spawned rooms exit socket tag, it will try to spawn a room with correct corresponded tag.  */
	void GenerateMap();

	/*Before spawning any room, Tiles array that will be used for entire checks will be initialized. */
	void InitWorldTiles();

	/*Place where most of the functions are used. It'll try to spawn if not collided. If collided, Make all the collision & tile checks and spawn corridor to connect them.*/
	void SpawnRoom(FName Tag);

	
	/*Collision check with calculating the given room actor's box component's area that will occupy before spawning the room. If the area the room is meant to spawn already marked as "Blocked" from Tiles array, true will be returned */
	bool IsColliding(ARoomActor* Room, FVector SpawnLoc);

	/*There might be always edge cases where a room is spawned without overlap but there's not enough space left to make a connection from end socket to another room's enter socket. To prevent this problem,
	 *it will be checked end socket has minimum 3 available tile buffer width. If not, the room will be acted as overlapped*/
	bool IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc);

	/**Checks if the buffer zone around a given room collides in the world. //Same as IsColliding. Just setting given indexes to be blocked.*/
	bool IsBufferZoneColliding(ARoomActor* Room, FVector SpawnLoc);

	/*After the room is spawned, set the spawned room's occupied positions as blocked for tile array indexes.*/
	void SetTilesBlocked(ARoomActor* Room, FVector SpawnLoc);
	
	/**For Socket enter and exit, given amounts will be discarded from tiles and unmark as blocked.*/
	void SetSocketExclusion(ARoomActor* Room);

	/*After it overlapped with a room, the room will be moved to non overlapping position.*/
	bool MoveOverlappedRoom(ARoomActor* NextRoom,  FVector& NextRoomLocation);

	void ConnectRoomsWithCorridors();

	/*After a room is overlapped and it moved to another position where it doesn't overlap anymore, a path will be try to be found from previous room's door socket exit to new room's door socket enter with using a* pathfinding. */
	bool FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount, FString RoomName, int* PathCost = nullptr);

	/*After pathfinding is finished, it will spawn the corridors on the found path*/
	void SpawnCorridors(int goalX, int goalY);

	/*Number of how many checks it should make for different kind of rooms. If the given amount is exceed, IsColliding function will abort */
	int DetermineSafeCheckAmount(ARoomActor* NextRoom) const;

	/*Similar how SpawnRoom works but meant to spawn a room for eventually making a connection from one LargeRoom's scene comp to closest LargeRoom's scene comp*/
	ARoomActor* SpawnFirstBranchRoom(FName Tag, FVector SpawnLoc, USceneComponent* SceneComponent, ARoomActor* LargeRoom, TArray<ARoomActor*>& RoomsToBeAdded);
	
	ARoomActor* SpawnBranchRoom(FName Tag, int SpawnCounter, TArray<ARoomActor*>& RoomsToBeAdded, bool& EndBranch);

	/*For large rooms that has multiple exits, to make socket exclusion, in BP editor declare an IntPoint named "SceneComponentName_Exclude" and give exclusions.*/
	void SocketExclusionForLargeRoom(ARoomActor* Room);
	
	void MakeSideBranchFromLargeRoom();

	void MakeBranchConnection();


	/*Not working correct. I'll take a look later on. */
	void OffsetLargeRoomSceneComps(ARoomActor* Room, USceneComponent& SceneComp1,USceneComponent& SceneComp2, FIntPoint& Start, FIntPoint& End);


	void SpawnRoomForBranchConnection(FName Tag, FIntPoint StartIndex, FIntPoint EndIndex);


	/*Same as SetTilesBlocked. But it returns blocked ones to be reverted back shortly. Designed to be used with SpawnRoomForBranchConnection*/
	TArray<FIntPoint> BlockAndRetrieveTiles(ARoomActor* Room, FVector SpawnLoc);

	//Visualizing
	void VisualizeBeginEndTiles(ARoomActor* NextRoom, FRoomConnection Connection);

	/*Bypass debug spawning NoExitRoom */
	inline bool CanIgnoreExitRoomSpawning(ARoomActor* NextRoom)
	{
		if (RoomSequence.Num() > 0)
		{
			return true; 
		}
		
		if (NextRoom->ActorHasTag("NoExit"))
		{
			return false;
		}
		return true;
	}

	/*After a path found, it's required to reset all visited for A* pathfinding*/
	inline void ResetAllVisited()
	{
		for (int x = 0; x < MapSizeX; ++x)
		{
			for (int y = 0; y < MapSizeY; ++y)
			{
				Tiles[x][y].Visited = false;
			}
		}
	};
		
	/*Extra check if the calculated areas are exist in tiles array*/
	inline bool IsValid(int x, int y)
	{
		return x >= 0 && x < MapSizeX && y >= 0 && y < MapSizeY;
	}

	/*Convert given relative index points to world location */
	inline FIntPoint WorldToIndex(FVector WorldLocation)
	{
		int TileX = FMath::RoundToInt(WorldLocation.X / TileSizeX);
		int TileY = FMath::RoundToInt(WorldLocation.Y / TileSizeY);

		// int TileX = FMath::CeilToInt(WorldLocation.X / TileSizeX);
		// int TileY = FMath::CeilToInt(WorldLocation.Y / TileSizeY);
		
		return FIntPoint(TileX,TileY);
	}

	/*Convert given world position to relative index points */
	inline FVector IndexToWorld(int X, int Y)
	{
		return FVector(X * TileSizeX, Y * TileSizeY, 0);
	}

	//These all for spawning corridors for found path. 
	inline void DeterminePathDirection(FTileStruct* Current, int X, int Y, FTileStruct* Node)
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
	inline FRotator DetermineFirstTurnRotation(EDirection2 NextDir)
	{
		if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideRight"))
		{
			if (NextDir == Dir_Up) return FRotator(0, 0, -90);
			if (NextDir == Dir_Down) return FRotator(0, -90, -90);
		}
		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideLeft"))
		{
			if (NextDir == Dir_Down) return FRotator(0, -180, -90);
			if (NextDir == Dir_Up) return FRotator(0, -90, -90);
		}

		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightUp"))
		{
			if (NextDir == Dir_Right) return FRotator(0, 0, -90);
			if (NextDir == Dir_Left) 	return FRotator(0, -90, -90);
		}

		else if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("StraightDown"))
		{
			if (NextDir == Dir_Right)	return  FRotator(0, -270, -90);
			if (NextDir == Dir_Left) 	return FRotator(0, 0, -90);
		}
		return FRotator(31,31,31);
	}
	inline EDirection2 DetermineFirstDirection(EDirection2 NextDir)
	{
		if (LastSpawnedRoom->DoorSocketExit->ComponentHasTag("SideRight"))
		{
			if (NextDir == Dir_Right) return Dir_Right;
			if (NextDir == Dir_Down) return Dir_Left;
		}
		return Dir_None;
	}
	inline FRotator DetermineMiddleTurnRotation(EDirection2 CurrDir, EDirection2 NextDir)
	{
		if (CurrDir == Dir_Up && NextDir == Dir_Left)
		{
			return FRotator(0,270,-90);
		}
		if (CurrDir == Dir_Down && NextDir == Dir_Right)
		{
			return  FRotator(0,90,-90);
		}
		if (CurrDir == Dir_Left && NextDir == Dir_Up)
		{
			return  FRotator(0,-270,-90);
		}
		if (CurrDir == Dir_Up && NextDir == Dir_Right)
		{
			return  FRotator(0,-180,-90);
		}
		if (CurrDir == Dir_Right && NextDir == Dir_Up)
		{
			return  FRotator(0,0,-90);
		}
		if (CurrDir == Dir_Right && NextDir == Dir_Down)
		{
			return  FRotator(0,270,-90);
		}
		if (CurrDir == Dir_Down && NextDir == Dir_Left)
		{
			return  FRotator(0,0,-90);
		}
		if (CurrDir == Dir_Left && NextDir == Dir_Down)
		{
			return  FRotator(0,180,-90);
		}
		return FRotator(31,31,31);
	}
	inline FRotator DetermineLastCorrRotation(EDirection2 LastDir)
	{
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == "SideLeft") return FRotator(0, 180, -90); 
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == "SideRight") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == "StraightUp") return FRotator(0, -180, -90);
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == "SideRight") return FRotator(0, -90, -90); //This has been changed
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == "StraightUp") return FRotator(0, -180, -90);
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == "StraightDown") return FRotator(0, 0, -90); 
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == "SideLeft") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == "SideRight") return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == "StraightUp") return FRotator(0, 180, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == "SideLeft") return FRotator(0, 90, -90); 
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == "StraightDown") return FRotator(0, 90, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == "StraightDown") return FRotator(0, 90, -90);
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
	inline EDirection2 ConvertNextRoomEnterTagToDirection()
	{
		if (NextRoomEnterTag == "SideRight") return EDirection2::Dir_Right;
		if (NextRoomEnterTag == "SideLeft")	return EDirection2::Dir_Left;
		if (NextRoomEnterTag == "StraightUp") return EDirection2::Dir_Up;
		if (NextRoomEnterTag == "StraightDown") return EDirection2::Dir_Down;
		return EDirection2::Dir_None;
	}
	inline bool LastCorrException(EDirection2 CurrDir, EDirection2 NextRoomEnterDir)
	{
		if (CurrDir == Dir_Down && NextRoomEnterDir == Dir_Up) return true;
		if (CurrDir == Dir_Up && NextRoomEnterDir == Dir_Down) return true;
		if (CurrDir == Dir_Right && NextRoomEnterDir == Dir_Left) return true;
		if (CurrDir == Dir_Left && NextRoomEnterDir == Dir_Right) return true;

		return false;
	}
	inline FName DirectionToTag(EDirection2 Direction)
	{
		if (Direction == EDirection2::Dir_Right) return "SideRight";
		if (Direction == EDirection2::Dir_Left) return "SideLeft";
		if (Direction == EDirection2::Dir_Up) return "StraightUp";
		if (Direction == EDirection2::Dir_Down) return "StraightDown";
		return "Null";
	}
	inline FName ExpectedTag(FName Name)
	{
		if (Name == "SideRight") return "SideLeft";
		if (Name == "SideLeft") return "SideRight";
		if (Name == "StraightUp") return "StraightDown";
		if (Name == "StraightDown") return "StraightUp";
		return "Dir_None";
	}

	inline bool CanSpawnLargeRoom()
	{
		return LargeRoomCounter < MaxLargeRoomCount;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void VisualizeOverlaps();
	void VisualizeVisited();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
