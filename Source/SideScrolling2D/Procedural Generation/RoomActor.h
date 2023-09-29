// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"


class UBoxComponent;
class UPaperTileMap;

UCLASS()
class SIDESCROLLING2D_API ARoomActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomActor();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int PathCost = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* RootScene;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* DoorSocketEnter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* DoorSocketExit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FIntPoint PathStartOffset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FIntPoint PathEndOffset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	TArray<FIntPoint> EnterExclusions;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	TArray<FIntPoint> ExitExclusions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	FIntPoint ExitSocketCheck; 

	//Just will be used with Branch Connection
	bool IsOverlapped;
	
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UPaperTileMapComponent* TileMapComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
