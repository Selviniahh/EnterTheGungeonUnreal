// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	FlipBook->SetupAttachment(DefaultSceneRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(FlipBook);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxComponent);

	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperZDAnimation"));
	PaperZDAnimation->InitRenderComponent(FlipBook);
	
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Gun");
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGunBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

