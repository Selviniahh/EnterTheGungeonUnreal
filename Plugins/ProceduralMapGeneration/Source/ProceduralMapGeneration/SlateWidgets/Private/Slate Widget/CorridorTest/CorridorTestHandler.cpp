// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralMapGeneration/SlateWidgets/Public/Slate Widget/CorridorTest/CorridorTestHandler.h"
#include "Components/BoxComponent.h"

UCorridorTestHandler::UCorridorTestHandler()
{
	
}

void UCorridorTestHandler::Initialize(ARoomActor* FirstSelectedRoom, ARoomActor* SecondSelectedRoom)
{
	this->FirstRoom = FirstSelectedRoom;
	this->SecondRoom = SecondSelectedRoom;
	Setting = GetDefault<UPluginSettings>();

	FirstSecRoom.Add(FirstRoom);
	FirstSecRoom.Add(SecondRoom);
	
	World = GEditor->GetEditorWorldContext().World();
}

void UCorridorTestHandler::Start()
{
	//TODO: Not that hard to implement I just need to return the current direction pairs right here and loop those 
	TArray<TArray<FIntPoint>> AllScenarios;
	AllScenarios.Add(VerticalUpToVerticalUp);
	AllScenarios.Add(VerticalUpTurnRightToVerticalUp);
	AllScenarios.Add(VerticalUpTurnLeftToVerticalUp);
	AllScenarios.Add(DownDown);
	AllScenarios.Add(DownDown2);
	AllScenarios.Add(DownDown3);

	InitWorldChunks(AllScenarios);

	for (auto AllScenario : AllScenarios)
	{
		FVector InitialFirstRoomLoc;
		FIntPoint Result = FIntPoint(0,0);
		for (auto Pattern : AllScenario)
		{
			Result += Pattern;
		}
		
		InitialFirstRoomLoc = CenterOfEachChunk[0];
		CenterOfEachChunk.RemoveAt(0);
		
		//TODO: I really need to study so much time on these stuffs
		FVector FirstRoomExitRelativeLoc = FirstSecRoom[0]->DoorSocketExit->GetRelativeLocation();
		// FVector FirstRoomLoc = Setting->ProGenInst->SwapZYaxis(FirstRoomExitRelativeLoc, InitialFirstRoomLoc);
		FVector NextRoomOffset = Setting->ProGenInst->IndexToWorld(Result.X,Result.Y);
		//NOTE: I Guess I don't need these stuff here
		// FVector NextRoomLoc = New + Setting->ProGenInst->IndexToWorld(Result.X,Result.Y);
		// FVector NextRoomLoc = Setting->ProGenInst->SwapZYaxis(FirstSecRoom[0]->DoorSocketExit->GetRelativeLocation(),FirstRoomLoc) + Setting->ProGenInst->IndexToWorld(Result.X,Result.Y);
		// FVector NextRoomLoc = FirstRoomLoc + ProGen->IndexToWorld(Result.X,Result.Y);

		//I has to assign this room here first
		Setting->ProGenInst->LastSpawnedRoom = FirstSecRoom[0];
		MakePathScenario(InitialFirstRoomLoc, NextRoomOffset, AllScenario);
	}

}

void UCorridorTestHandler::InitWorldChunks(TArray<TArray<FIntPoint>>& AllScenarios)
{
	int TotalChunkCount = AllScenarios.Num();
	int MaxBoxExtent = 0;
	int LongestScenarioLength = 0;
	int Offset = 4;

	//Find the longest extends among all the rooms
	for (auto RoomActor : FirstSecRoom)
	{
		FVector BoxExtent = RoomActor->BoxComponent->GetScaledBoxExtent();
		MaxBoxExtent = FMath::Max(MaxBoxExtent, static_cast<int>(FMath::Max(BoxExtent.X, BoxExtent.Z)));
	}

	//Find the longest length of the scenarios 
	for (auto Scenario : AllScenarios)
	{
		LongestScenarioLength = FMath::Max(LongestScenarioLength, Scenario.Num());
	}

	//Step 2: Calculate exact chunk dimension
	int ChunkDimension = (MaxBoxExtent * 4) + (LongestScenarioLength * Setting->ProGenInst->TileSizeX);
	ChunkDimension += (ChunkDimension); // needed to add half of it because we already make all the spawning at the center of the chunk 
	int ChunksPerRow = FMath::CeilToInt(FMath::Sqrt(static_cast<float>(TotalChunkCount))); //If there's 10 scenario then sqrt of 10 is 3.16. So 4x4 chunks will be created
	Setting->ProGenInst->MapSizeX = ChunksPerRow * ChunkDimension; // Total width of the map //TODO: I am unsure to change revert back the changes later on 
	Setting->ProGenInst->MapSizeY = ChunksPerRow * ChunkDimension; // Total height of the map

	//Now say ChunkDimension is 500. So width and height is 500x500. Readjust the Map Size to cover this scenario
	Setting->ProGenInst->InitWorldTiles();

	CenterOfEachChunk.Empty(); // Clear any existing data

	for (int ChunkX = Offset; ChunkX < ChunksPerRow + Offset; ++ChunkX)
	{
		for (int ChunkY = Offset; ChunkY < ChunksPerRow + Offset; ++ChunkY)
		{
			// Calculate the top-left corner of the chunk, Study later on how to calculate all these 4 corners
			FVector ChunkTopLeft = FVector(ChunkX * ChunkDimension,ChunkY * ChunkDimension, 0);
			FVector ChunkTopRight = ChunkTopLeft + FVector(ChunkDimension, 0.0f, 0.0f);
			FVector ChunkBottomLeft = ChunkTopLeft + FVector(0.0f, ChunkDimension, 0.0f);
			FVector ChunkBottomRight = ChunkTopLeft + FVector(ChunkDimension, ChunkDimension, 0.0f);
			
			// Calculate the center of the chunk
			FVector ChunkCenter = ChunkTopLeft + FVector(ChunkDimension / 2, ChunkDimension / 2, 0);
			RoundNearestTilePos(ChunkCenter);
			
			// Draw lines for each side of the chunk
			DrawDebugLine(World, ChunkTopLeft, ChunkTopRight, FColor::Red, true, -1, 0, 5);
			DrawDebugLine(World, ChunkTopRight, ChunkBottomRight, FColor::Red, true, -1, 0, 5);
			DrawDebugLine(World, ChunkBottomRight, ChunkBottomLeft, FColor::Red, true, -1, 0, 5);
			DrawDebugLine(World, ChunkBottomLeft, ChunkTopLeft, FColor::Red, true, -1, 0, 5);
			DrawDebugBox(World, ChunkCenter, FVector(Setting->ProGenInst->TileSizeX,Setting->ProGenInst->TileSizeX,Setting->ProGenInst->TileSizeX), FColor::Red, true, -1, 0, 5);

			// Add the chunk center to the array
			CenterOfEachChunk.Add(ChunkCenter);
		}
	}

	//Set Render View first
	FVector Center = FVector(0,0,0);
	for (auto Chunk : CenterOfEachChunk)
		Center += Chunk;
	
	Center = Center / CenterOfEachChunk.Num();
	Setting->SceneCapActorInst.Get()->SetActorLocation(Center);
	Setting->SceneCapActorInst.Get()->SetActorLocation(FVector(Center.X, Center.Y, 500));
}

void UCorridorTestHandler::MakePathScenario(const FVector& FirstRoomLoc, FVector& NextRoomLocation, TArray<FIntPoint>& CurrentPattern)
{
	SpawnFirstRoom(FirstRoomLoc);
	ARoomActor* NextRoom;
	
	NextRoomLocation += FirstSecRoom[0]->DoorSocketExit->GetComponentLocation();
	SpawnSecondRoom(NextRoomLocation, NextRoom);
	MakeGivenPathFinding(CurrentPattern, NextRoom, NextRoomLocation, FirstRoomLoc);
}

void UCorridorTestHandler::SpawnFirstRoom(const FVector& FirstRoomLoc)
{
	if (!Setting->ProGenInst.Get()) return;
	
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	// FVector FirstRoomLoc = ProGen->Tiles[ProGen->MapSizeX / 2][ProGen->MapSizeY / 2].Location + ProGen->ZOffset; //TODO: Later decide how to determine first room loc when you spawn all the other scenarios
	ARoomActor* FirstLocalRoom = World->SpawnActor<ARoomActor>(FirstSecRoom[0]->GetClass(), FirstRoomLoc, Rotation);
	CurrChunkActorLocs.Add(FirstRoomLoc);
	FirstSecRoom[0] = FirstLocalRoom;
	LargestExtends = FIntPoint(FirstLocalRoom->BoxComponent->GetScaledBoxExtent().X, FirstLocalRoom->BoxComponent->GetScaledBoxExtent().Z); //TODO: If I were doing this in side scrolling, this axises would be highly inverted. I don't have any idea how but later make these stuff based on criterias to determine only option based on the rotation of the actor etc, (Top down is different side scrolling is different in this case)
	
	//TODO: You know this 2 line has to gone. 
	Setting->ProGenInst->NextRoomExitTag = FirstLocalRoom->ExitSocketDirection;
	Setting->ProGenInst->NextRoomEnterTag = FirstLocalRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	Setting->ProGenInst->SetTilesBlocked(FirstLocalRoom, FirstRoomLoc, Rotation);
	Setting->ProGenInst->SetSocketExclusion(FirstLocalRoom, FirstRoomLoc);
	Setting->ProGenInst->LastSpawnedRoom = FirstLocalRoom;
	Setting->ProGenInst->SpawnedRoomCount++;
	

	if (Setting->ProGenInst->VisualizeEndSocketOverlapCheck) //Written to only make visualization for first room as well.
		Setting->ProGenInst->IsEndSocketOverlapping(FirstLocalRoom, FirstRoomLoc);
}

bool UCorridorTestHandler::MakeGivenPathFinding(TArray<FIntPoint>& CurrentPattern, ARoomActor* NextRoom, const FVector& NextRoomLoc, const FVector& FirstRoomLoc)
{
	auto SetFirstCorrRotation = [&](FTileStruct* Start)
	{
		if (Setting->ProGenInst->LastSpawnedRoom->ExitSocketDirection == HorizontalRight || Setting->ProGenInst->LastSpawnedRoom->ExitSocketDirection == HorizontalLeft)
			Start->Rotation = FRotator(0, 0, -90);

		else if (Setting->ProGenInst->LastSpawnedRoom->ExitSocketDirection == VerticalUp || Setting->ProGenInst->LastSpawnedRoom->ExitSocketDirection == VerticalDown)
		{
			Start->Rotation = FRotator(0, 90, -90); //(Pitch=0.000000,Yaw=90.000000,Roll=-90.000000)
		}
	};

	//TODO: his is required for a reason I don't know as well I have to find it's reason and fix this shit 
	int Offset = -1;
	
	//Pathfinding logic is here
	FRoomConnection Connection = Setting->ProGenInst->CalculatePathInfo(NextRoom);
	Connection.StartPoint = FirstRoomLoc;
	Connection.EndPoint = NextRoomLoc;

	//TODO: Later on disable this shit. If necessary
	Connection.PathStartOffset = FIntPoint(0,0);
	Connection.PathEndOffset = FIntPoint(0,0);
	
	TArray<FTileStruct*> OpenList;
	
	FIntPoint FirstRoomEnd = Setting->ProGenInst->WorldToIndex(FirstSecRoom[0]->DoorSocketExit->GetComponentLocation());
	// FIntPoint OverlappedRoomLoc = Setting->ProGenInst->WorldToIndex(NextRoom->DoorSocketEnter->GetComponentLocation());

	int StartX = Connection.PathStartOffset.X + FirstRoomEnd.X + Offset;
	int StartY = Connection.PathStartOffset.Y + FirstRoomEnd.Y;
	int GoalX = Connection.PathEndOffset.X + Setting->ProGenInst->WorldToIndex(NextRoomLoc).X + Offset;
	int GoalY = Connection.PathEndOffset.Y + Setting->ProGenInst->WorldToIndex(NextRoomLoc).Y;

	FTileStruct* Start = &Setting->ProGenInst->Tiles[StartX][StartY];
	SetFirstCorrRotation(Start);
	OpenList.Add(Start);

	while (OpenList.Num() > 0)
	{
		FTileStruct* Current = FillGivenCorrPattern(OpenList, CurrentPattern);
		if (Current->X == GoalX && Current->Y == GoalY)
		{
			Setting->ProGenInst->MakeCorridorPathVisualization(Setting->ProGenInst->LastSpawnedRoom, Current);
			Setting->ProGenInst->SpawnCorridors(GoalX, GoalY, Setting->ProGenInst->LastSpawnedRoom, false);
			return true;
		}
	}
	
	return false;
}

FTileStruct* UCorridorTestHandler::FillGivenCorrPattern(TArray<FTileStruct*>& RoomList, TArray<FIntPoint>& CurrentPattern)
{
	//For now let's just go 10 times up
	FIntPoint CurrentPatternIndex = CurrentPattern[0];
	CurrentPattern.RemoveAt(0);

	FIntPoint NewIndex = FIntPoint(RoomList.Top()->X + CurrentPatternIndex.X, RoomList.Top()->Y + CurrentPatternIndex.Y); //Go up each iteration 
	FTileStruct* LastTile = RoomList.Top();
	FTileStruct* Neighbour = &Setting->ProGenInst->Tiles[NewIndex.X][NewIndex.Y];
	Neighbour->Parent = LastTile;
	Setting->ProGenInst->DeterminePathDirection(LastTile, NewIndex.X, NewIndex.Y, Neighbour);
	RoomList.Add(Neighbour);
	return Neighbour;
}

void UCorridorTestHandler::SpawnSecondRoom(const FVector& NextRoomLocation, ARoomActor*& NextRoom)
{
	const FRotator Rotation(0.0f, 0.0f, -90.0f);
	NextRoom = FirstSecRoom[1];
	//TODO: You know this 2 line has to gone. 
	Setting->ProGenInst->NextRoomExitTag = NextRoom->ExitSocketDirection;
	Setting->ProGenInst->NextRoomEnterTag = NextRoom->EnterSocketDirection; //Just useful to spawning corridors. Nothing to do with rooms

	//First cover horizontal up to horizontal up
	
	NextRoom = World->SpawnActor<ARoomActor>(NextRoom->GetClass(), NextRoomLocation, Rotation);
	NextRoom = FirstSecRoom[1];  //IDK what I am doing here 
	FIntPoint BoxExtend = FIntPoint(NextRoom->BoxComponent->GetScaledBoxExtent().X, NextRoom->BoxComponent->GetScaledBoxExtent().Y);
	LargestExtends = FIntPoint(FMath::Max(BoxExtend.X, LargestExtends.X), FMath::Max(BoxExtend.Y, LargestExtends.Y));
	
	Setting->ProGenInst->SetTilesBlocked(NextRoom, NextRoomLocation, NextRoom->Rotation);
	Setting->ProGenInst->SetSocketExclusion(NextRoom, NextRoomLocation);
}
