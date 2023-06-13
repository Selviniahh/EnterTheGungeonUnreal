// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("FlipBook");
	FlipBook->SetupAttachment(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(FlipBook);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, -240));
	Super::Tick(DeltaTime);
}

