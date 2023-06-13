// Fill out your copyright notice in the Description page of Project Settings.


#include "Globals.h"


// Sets default values
AGlobals::AGlobals()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGlobals::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

