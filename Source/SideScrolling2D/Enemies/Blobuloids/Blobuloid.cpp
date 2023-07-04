// Fill out your copyright notice in the Description page of Project Settings.


#include "Blobuloid.h"

#include "PaperFlipbookComponent.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ABlobuloid::ABlobuloid()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ABlobuloid::BeginPlay()
{
	Super::BeginPlay();
}


void ABlobuloid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	//This will return true when Death animation is finished
	if (CanSpawn)
	{
		GetWorld()->SpawnActor<ABlobuloid>(Blobuloid,FirstSpawnLocation,FRotator::ZeroRotator);
		GetWorld()->SpawnActor<ABlobuloid>(Blobuloid,SecondSpawnLocation,FRotator::ZeroRotator);
		Destroy();
	}
}

void ABlobuloid::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABlobuloid::JustPlayShootAnimation()
{
	//Discard Everything
}



