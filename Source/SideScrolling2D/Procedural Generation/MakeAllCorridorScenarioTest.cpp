// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeAllCorridorScenarioTest.h"

#include "ProceduralGen.h"
#include "Components/BoxComponent.h"

UMakeAllCorridorScenarioTest::UMakeAllCorridorScenarioTest()
{
}

void UMakeAllCorridorScenarioTest::Initialize(AProceduralGen* InProceduralGenInstance, TArray<TSubclassOf<ARoomActor>> FixedTwoRoomActors)
{
	//Assign all the elements of the array
	for (int i = 0; i < 2; ++i)
	{
		FixedRoomActor.Add(Cast<ARoomActor>(FixedTwoRoomActors[i]->GetDefaultObject()));
	}

	ProGen = InProceduralGenInstance;
}

void UMakeAllCorridorScenarioTest::Start()
{
	TArray<TArray<FIntPoint>> AllScenarios;
	AllScenarios.Add(ProGen->VerticalUpToVerticalUp);
	AllScenarios.Add(ProGen->VerticalUpTurnRightToVerticalUp);

	for (auto AllScenario : AllScenarios)
	{
		FVector FirstRoomLoc;
		FIntPoint Result = FIntPoint(0,0);
		for (auto Pattern : AllScenario)
		{
			Result += Pattern;
		}

		if (LargestExtends != FIntPoint(0,0))
		{
			FirstRoomLoc = ProGen->LastSpawnedRoom->DoorSocketEnter->GetComponentLocation() + RoundVectorToTilePos(LargestExtends);
		}
		else
		{
			FirstRoomLoc = ProGen->Tiles[ProGen->MapSizeX / 2][ProGen->MapSizeY / 2].Location; 
		}
	
		FVector NextRoomLoc = ProGen->SwapZYaxis(FixedRoomActor[0]->DoorSocketExit->GetRelativeLocation(),FirstRoomLoc) + ProGen->IndexToWorld(Result.X,Result.Y);
		MakePathScenario(FirstRoomLoc,NextRoomLoc, AllScenario);
	}
	
	
}

void UMakeAllCorridorScenarioTest::SpawnSecondRoom(const FVector& NextRoomLocation, ARoomActor*& NextRoom)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	NextRoom = FixedRoomActor[1];

	//TODO: You know this 2 line has to gone. 
	ProGen->NextRoomExitTag = NextRoom->ExitSocketDirection;
	ProGen->NextRoomEnterTag = NextRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	//First cover horizontal up to horizontal up
	NextRoom = GetWorld()->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	FIntPoint BoxExtend = FIntPoint(NextRoom->BoxComponent->GetScaledBoxExtent().X, NextRoom->BoxComponent->GetScaledBoxExtent().Y);
	LargestExtends = FIntPoint(FMath::Max(BoxExtend.X, LargestExtends.X), FMath::Max(BoxExtend.Y, LargestExtends.Y));
	
	ProGen->SetTilesBlocked(NextRoom, NextRoomLocation);
	ProGen->SetSocketExclusion(NextRoom, NextRoomLocation);
}

bool UMakeAllCorridorScenarioTest::MakeGivenPathFinding(TArray<FIntPoint>& CurrentPattern, ARoomActor* NextRoom)
{
	auto SetFirstCorrRotation = [&](FTileStruct* Start)
	{
		if (ProGen->LastSpawnedRoom->ExitSocketDirection == HorizontalRight || ProGen->LastSpawnedRoom->ExitSocketDirection == HorizontalLeft)
			Start->Rotation = FRotator(0, 0, -90);

		else if (ProGen->LastSpawnedRoom->ExitSocketDirection == VerticalUp || ProGen->LastSpawnedRoom->ExitSocketDirection == VerticalDown)
		{
			Start->Rotation = FRotator(0, 90, -90); //(Pitch=0.000000,Yaw=90.000000,Roll=-90.000000)
		}
	};
	
	//Pathfinding logic is here
	FRoomConnection Connection = ProGen->CalculatePathInfo(NextRoom);

	TArray<int> Row = {-1, 0, 0, 1};
	TArray<int> Col = {0, -1, 1, 0};
	TArray<FTileStruct*> OpenList;
	
	FIntPoint LastRoomEnd = ProGen->WorldToIndex(ProGen->LastSpawnedRoom->DoorSocketExit->GetComponentLocation());
	FIntPoint OverlappedRoomLoc = ProGen->WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());

	int StartX = Connection.PathStartOffset.X + LastRoomEnd.X;
	int StartY = Connection.PathStartOffset.Y + LastRoomEnd.Y;
	int GoalX = Connection.PathEndOffset.X + OverlappedRoomLoc.X;
	int GoalY = Connection.PathEndOffset.Y + OverlappedRoomLoc.Y;

	FTileStruct* Start = &ProGen->Tiles[StartX][StartY];
	SetFirstCorrRotation(Start);
	OpenList.Add(Start);

	while (OpenList.Num() > 0)
	{
		FTileStruct* Current = FillGivenCorrPattern(OpenList, CurrentPattern);
		if (Current->X == GoalX && Current->Y == GoalY)
		{
			ProGen->MakeCorridorPathVisualization(ProGen->LastSpawnedRoom, Current);
			ProGen->SpawnCorridors(GoalX, GoalY, ProGen->LastSpawnedRoom, false);
			return true;
		}
	}
	
	return false;
}

void UMakeAllCorridorScenarioTest::MakePathScenario(const FVector& FirstRoomLoc, const FVector& NextRoomLocation, TArray<FIntPoint>& CurrentPattern)
{
	SpawnFirstRoom(FirstRoomLoc);

	ARoomActor* NextRoom;
	SpawnSecondRoom(NextRoomLocation, NextRoom);
	
	if (MakeGivenPathFinding(CurrentPattern, NextRoom)) return;
}

void UMakeAllCorridorScenarioTest::SpawnFirstRoom(const FVector& FirstRoomLoc)
{
	if (!ProGen) return;
	
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	// FVector FirstRoomLoc = ProGen->Tiles[ProGen->MapSizeX / 2][ProGen->MapSizeY / 2].Location + ProGen->ZOffset; //TODO: Later decide how to determine first room loc when you spawn all the other scenarios
	ARoomActor* FirstRoom = GetWorld()->SpawnActor<ARoomActor>(FixedRoomActor[0]->GetClass(), FirstRoomLoc, Rotation);
	LargestExtends = FIntPoint(FirstRoom->BoxComponent->GetScaledBoxExtent().X, FirstRoom->BoxComponent->GetScaledBoxExtent().Y);
	
	//TODO: You know this 2 line has to gone. 
	ProGen->NextRoomExitTag = FirstRoom->ExitSocketDirection;
	ProGen->NextRoomEnterTag = FirstRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	ProGen->SetTilesBlocked(FirstRoom, FirstRoomLoc);
	ProGen->SetSocketExclusion(FirstRoom, FirstRoomLoc);
	ProGen->LastSpawnedRoom = FirstRoom;
	ProGen->SpawnedRoomCount++;

	if (ProGen->VisualizeEndSocketOverlapCheck) //Written to only make visualization for first room as well.
		ProGen->IsEndSocketOverlapping(FirstRoom, FirstRoomLoc);
}

FTileStruct* UMakeAllCorridorScenarioTest::FillGivenCorrPattern(TArray<FTileStruct*>& RoomList, TArray<FIntPoint>& CurrentPattern)
{
	//For now let's just go 10 times up
	FIntPoint CurrentPatternIndex = CurrentPattern[0];
	CurrentPattern.RemoveAt(0);

	FIntPoint NewIndex = FIntPoint(RoomList.Top()->X + CurrentPatternIndex.X, RoomList.Top()->Y + CurrentPatternIndex.Y); //Go up each iteration 
	FTileStruct* LastTile = RoomList.Top();
	FTileStruct* Neighbour = &ProGen->Tiles[NewIndex.X][NewIndex.Y];
	Neighbour->Parent = LastTile;
	ProGen->DeterminePathDirection(LastTile, NewIndex.X, NewIndex.Y, Neighbour);
	RoomList.Add(Neighbour);
	return Neighbour;
}
