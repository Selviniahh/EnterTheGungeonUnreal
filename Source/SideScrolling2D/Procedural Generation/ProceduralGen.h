// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralGeneration.h"
#include "RoomActor.h"
#include "GameFramework/Actor.h"
#include "ProceduralGen.generated.h"

struct FRoomConnection;
enum Direction : int;
struct FTileStruct;
class ARoomActor;

UCLASS()
class SIDESCROLLING2D_API AProceduralGen : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralGen();
	virtual void Tick(float DeltaTime) override;

	/*Add all the rooms to be randomly select and spawned.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 1))
	TArray<TSubclassOf<ARoomActor>> RoomDesigns;
	TArray<TArray<FTileStruct>> Tiles;

	Direction NextRoomExitTag;
	Direction NextRoomEnterTag;

	/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 4))
	int MapSizeX = 1000;
	/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 5))
	int MapSizeY = 1000;
	/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/
	int TileSizeX = 16;
	/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 7))
	int TileSizeY = 16;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 7))
	int MaxAttemptForRoomMoving = 10000000;
	
	/*Total number of rooms to be spawned*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 2))
	int NumberOfRooms = 10;


	/*For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 2))
	TArray<FVector> BlockRoomLocations;

	/*Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 1))
	TArray<TSubclassOf<ARoomActor>> DebugRoomSequence;

	/*Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps. */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 3))
	TSubclassOf<ARoomActor> BlockRoom;

	TArray<FIntPoint> BlockedTileHolder;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> StraightCorr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ARoomActor> TurnCorridor;

	/*Which room set as blocked*/
	TMap<TWeakObjectPtr<ARoomActor>, TArray<FIntPoint>> RoomExclusions;

	FVector ZOffset = FVector(0,0,3);

	/*for IsEndSocketOverlapping*/
	UPROPERTY()
	ARoomActor* LastCheckedRoom = nullptr;
	
	/*All excluded tiles are purple*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 8))
	bool VisualizeAllExclusions = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 4))
	bool VisualizeOverlaps = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 5))
	bool VisualizeVisited = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 10))
	bool VisualizeEndSocketOverlapCheck = false;

	/*Path visualization color is red*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 7))
	bool VisualizeCorridorPath = true;

	/* Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)*/
	UPROPERTY()
	ARoomActor* LastSpawnedRoom;
	
	TArray<FRoomConnection> RoomConnections;


	/*Room spawn counter. It will increment as new rooms are spawned*/
	int SpawnedRoomCount;
	int LargeRoomCounter = 0;

	FVector TileBoxExtends;

	int CurrentIndex = 0;

	/* Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.
		 * A larger value will create a larger distance from other rooms.*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 8))
	int BufferSize = 6;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 10))
	int NormalRoomMaxSafeCheck = 5000;

	/*When room is moved, this is the one to check never mind update here later*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="General Map settings", meta=(DisplayPriority = 11))
	int LargeRoomMaxSafeCheck = 2000;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 11))
	bool SpawnCorridor = true;

	/*Begin and End socket visualization color is Cyan*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Debugging", meta=(DisplayPriority = 6))
	bool VisualizeBeginAndEndTiles = true;
	
	int FoundPathCost;

	void GenerateMap();
	void InitWorldTiles();
	void SetTilesBlocked(ARoomActor* Room, const FVector& SpawnLoc);
	bool IsColliding(const ARoomActor* Room, const FVector& SpawnLoc);
	static FVector CalculateTopLeftCorner(const FVector& WorldLoc, const FVector& BoxExtends);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	bool MoveOverlappedRoom(ARoomActor* NextRoom, FVector& NextRoomLocation);
	void ConnectRoomsWithCorridors();
	
	/*After pathfinding is finished, it will spawn the corridors on the found path*/
	void SpawnCorridors(int goalX, int goalY);

	/**Checks if the buffer zone around a given room collides in the world. //Same as IsColliding. Just setting given indexes to be blocked.*/
	bool IsBufferZoneColliding(ARoomActor* Room, FVector SpawnLoc);

	/*After a room is overlapped and it moved to another position where it doesn't overlap anymore, a path will be try to be found from previous room's door socket exit to new room's door socket enter with using a* pathfinding. */
	bool FindCorridorPath(int StartX, int StartY, int GoalX, int GoalY, FIntPoint StartOffset, FIntPoint EndOffset, bool SpawnCorr, int MaxIterationAmount, FString RoomName, int* PathCost = nullptr);

	void VisualizeBeginEndTiles(ARoomActor* NextRoom, const FRoomConnection& Connection);
	void SpawnRoom(Direction EndSocketDirection);
	
	/**For Socket enter and exit, given amounts will be discarded from tiles and unmark as blocked.*/
	void SetSocketExclusion(ARoomActor* Room);
	void ResetAllVisited();

	void SetExclusion(ARoomActor* Room, const FIntPoint& Index, const FIntPoint& ExclusionOffset, TArray<FIntPoint> Exclusions);

	/*There might be always edge cases where a room is spawned without overlap but there's not enough space left to make a connection from end socket to another room's enter socket. To prevent this problem,
	 *it will be checked end socket has minimum 3 available tile buffer width. If not, the room will be acted as overlapped*/
	bool IsEndSocketOverlapping(ARoomActor* NextRoom, const FVector& SpawnLoc);

	/*Room actors are 90 degree rotated to be top down in BP. Therefore swapping is required*/
	static void SwapZYaxis(FVector& VectorToSwap);

	ARoomActor* SelectRoomWithDirection(Direction EndSocketDirection);
	
	void VisualizeTiles();

	int DetermineSafeCheckAmount(ARoomActor* NextRoom) const
    {
    	if (NextRoom->ActorHasTag("LargeRoom"))
    		return LargeRoomMaxSafeCheck;
    	else
    		return NormalRoomMaxSafeCheck;
    }
    
	/*Convert given world position to relative index points */
	inline FVector IndexToWorld(const int X, const int Y) const
	{
		return FVector(X * TileSizeX, Y * TileSizeY, 0);
	}
	
	/*Convert given relative index points to world location */
	inline FIntPoint WorldToIndex(const FVector& WorldLocation) const
	{
		int TileX = FMath::RoundToInt(WorldLocation.X / TileSizeX);
		int TileY = FMath::RoundToInt(WorldLocation.Y / TileSizeY);
		
		return FIntPoint(TileX,TileY);
	}

	inline bool IsValid(const int X, const int Y) const
	{
		return X >= 0 && X < MapSizeX && Y >= 0 && Y < MapSizeY;
	}

	static inline Direction ExpectedTag(const Direction Tag)
	{
		if (Tag == HorizontalRight) return HorizontalLeft;
		if (Tag == HorizontalLeft) return HorizontalRight;
		if (Tag == VerticalUp) return VerticalDown;
		if (Tag == VerticalDown) return VerticalUp;
		return {};
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
		if (LastSpawnedRoom->ExitSocketDirection == HorizontalRight) 
		{
			if (NextDir == Dir_Up) return FRotator(0, 0, -90);
			if (NextDir == Dir_Down) return FRotator(0, -90, -90);
		}
		else if (LastSpawnedRoom->ExitSocketDirection == HorizontalRight) 
		{
			if (NextDir == Dir_Down) return FRotator(0, -180, -90);
			if (NextDir == Dir_Up) return FRotator(0, -90, -90);
			if (NextDir == Dir_Left) return FRotator(0, 0, -90); //(Pitch=0.000000,Yaw=0.000000,Roll=-90.000000)
		}

		else if (LastSpawnedRoom->ExitSocketDirection == VerticalUp) 
		{
			if (NextDir == Dir_Right) return FRotator(0, 0, -90);
			if (NextDir == Dir_Left) 	return FRotator(0, -90, -90);
		}

		else if (LastSpawnedRoom->ExitSocketDirection == VerticalDown) 
		{
			if (NextDir == Dir_Right)	return  FRotator(0, -270, -90);
			if (NextDir == Dir_Left) 	return FRotator(0, 0, -90);
		}
		return FRotator(31,31,31);
	}
	inline EDirection2 DetermineFirstDirection(EDirection2 NextDir)
	{
		if (LastSpawnedRoom->ExitSocketDirection == HorizontalRight)
		{
			if (NextDir == Dir_Right) return Dir_Right;
			if (NextDir == Dir_Down) return Dir_Left;
		}
		return Dir_None;
	}
	inline FRotator DetermineMiddleTurnRotation(EDirection2 CurrDir, EDirection2 NextDir)
	{
		if (CurrDir == Dir_Up && NextDir == Dir_Left)		return FRotator(0,270,-90);
		if (CurrDir == Dir_Down && NextDir == Dir_Right) 	return  FRotator(0,90,-90);
		if (CurrDir == Dir_Left && NextDir == Dir_Up) 		return  FRotator(0,-270,-90);
		if (CurrDir == Dir_Up && NextDir == Dir_Right) 		return  FRotator(0,-180,-90);
		if (CurrDir == Dir_Right && NextDir == Dir_Up) 		return  FRotator(0,0,-90);
		if (CurrDir == Dir_Right && NextDir == Dir_Down) 	return  FRotator(0,270,-90);
		if (CurrDir == Dir_Down && NextDir == Dir_Left) 	return  FRotator(0,0,-90);
		if (CurrDir == Dir_Left && NextDir == Dir_Down) 	return  FRotator(0,180,-90);
		return FRotator(31,31,31);
	}
	inline FRotator DetermineLastCorrRotation(EDirection2 LastDir)
	{
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == HorizontalLeft) return FRotator(0, 180, -90); 
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == HorizontalRight) return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == VerticalUp) return FRotator(0, -180, -90);
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == HorizontalRight) return FRotator(0, -90, -90); //This has been changed
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == VerticalUp) return FRotator(0, -180, -90);
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == VerticalDown) return FRotator(0, 0, -90); 
		if (LastDir == EDirection2::Dir_Right && NextRoomEnterTag == HorizontalLeft) return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == HorizontalRight) return FRotator(0, 0, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == VerticalUp) return FRotator(0, 180, -90);
		if (LastDir == EDirection2::Dir_Down && NextRoomEnterTag == HorizontalLeft) return FRotator(0, 90, -90); 
		if (LastDir == EDirection2::Dir_Up && NextRoomEnterTag == VerticalDown) return FRotator(0, 90, -90);
		if (LastDir == EDirection2::Dir_Left && NextRoomEnterTag == VerticalDown) return FRotator(0, 90, -90);
		return FRotator(31, 31, 31);
	}
	inline EDirection2 ConvertNextRoomExitTagToDirection()
	{
		if (NextRoomExitTag == HorizontalRight) return EDirection2::Dir_Right;
		if (NextRoomExitTag == HorizontalLeft)	return EDirection2::Dir_Left;
		if (NextRoomExitTag == VerticalUp) return EDirection2::Dir_Up;
		if (NextRoomExitTag == VerticalDown) return EDirection2::Dir_Down;
		return EDirection2::Dir_None;
	}
	inline EDirection2 ConvertNextRoomEnterTagToDirection()
	{
		if (NextRoomEnterTag == HorizontalRight) return EDirection2::Dir_Right;
		if (NextRoomEnterTag == HorizontalLeft)	return EDirection2::Dir_Left;
		if (NextRoomEnterTag == VerticalUp) return EDirection2::Dir_Up;
		if (NextRoomEnterTag == VerticalDown) return EDirection2::Dir_Down;
		return EDirection2::Dir_None;
	}

	static inline bool LastCorrException(EDirection2 CurrDir, EDirection2 NextRoomEnterDir)
	{
		if (CurrDir == Dir_Down && NextRoomEnterDir == Dir_Up) return true;
		if (CurrDir == Dir_Up && NextRoomEnterDir == Dir_Down) return true;
		if (CurrDir == Dir_Right && NextRoomEnterDir == Dir_Left) return true;
		if (CurrDir == Dir_Left && NextRoomEnterDir == Dir_Right) return true;

		return false;
	}

	static inline FName DirectionToTag(EDirection2 Direction)
	{
		if (Direction == Dir_Right) return "SideRight";
		if (Direction == Dir_Left) return "SideLeft";
		if (Direction == Dir_Up) return "StraightUp";
		if (Direction == Dir_Down) return "StraightDown";
		return "Null";
	}

	//Pathfinding
	bool SetupPathFinding(int& StartX, int& StartY, int& GoalX, int& GoalY, const FIntPoint& StartOffset, const FIntPoint& EndOffset, const FString& RoomName);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnFirstRoom();
	void CalculatePathInfo(ARoomActor* NextRoom);
	void SpawnNonOverlappedRoom(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom);
	void SpawnDoors(const FRotator& Rotation, const FVector& NextRoomLocation, ARoomActor*& NextRoom);
	void SpawnOverlappedRoom(const FRotator& Rotation, FVector NextRoomLocation, ARoomActor*& NextRoom);
	void SpawnTestCollisionObjects();

private:
	void ForEachTileInRoom(const ARoomActor* Room, const FVector& SpawnLoc, const TFunction<void(int X, int Z)>& TileAction);
};
