// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderTarget.h"

#include "Components/SceneCaptureComponent2D.h"


// Sets default values
ARenderTarget::ARenderTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneCaptureComponent2D);
}

// Called when the game starts or when spawned
void ARenderTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARenderTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

