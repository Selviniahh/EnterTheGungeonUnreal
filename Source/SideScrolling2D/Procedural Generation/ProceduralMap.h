// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMap.generated.h"

class ARoomActor;
class ADoorActor;
class UPaperTileMap;

UCLASS()
class SIDESCROLLING2D_API AProceduralMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProceduralMap();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<ARoomActor>> RoomDesigns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADoorActor> DoorBlueprint;

	UPROPERTY()
	UPaperTileMap* CurrentTilemap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfRooms;

private:
	void GenerateMap();




	
protected:
	// Called when the game starts or when spawned

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
