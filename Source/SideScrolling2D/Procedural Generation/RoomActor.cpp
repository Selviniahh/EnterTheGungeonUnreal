// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"
#include "PaperTileMap.h"

#include "PaperTileLayer.h"
#include "Components/BoxComponent.h"
#include "PaperTileMapComponent.h"


// Sets default values
ARoomActor::ARoomActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	
	//No need to give something in BP for now
	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));
	TileMapComponent->SetupAttachment(RootComponent);

	DoorSocketEnter = CreateDefaultSubobject<USceneComponent>(TEXT("DoorSocketEnter"));
	DoorSocketEnter->SetupAttachment(RootComponent);

	DoorSocketExit = CreateDefaultSubobject<USceneComponent>(TEXT("DoorSocketExit"));
	DoorSocketExit->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

