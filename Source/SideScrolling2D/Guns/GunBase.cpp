// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "SideScrolling2D/Hero/Hero.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/TransformCalculus3D.h"
#include "SideScrolling2D/Projectiles/ProjectileBase.h"

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

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
}

// Called every frame

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Hero)
	{
		PressedTimer += DeltaTime;
	}

}

void AGunBase::Shoot()
{
	const UWorld* World = GetWorld();
	if (PressedTimer > 0.3 && World)
	{
		PressedTimer = 0;

		//Define the spawn location and rotation
		const FVector Location = ArrowComponent->GetComponentLocation();
		const FRotator Rotation = FRotator(0,0,0);

		//Spawn
		if (ProjectileType && !Hero->IsDashingCpp)
		{
			AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, Rotation);

			//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 
			const FVector ProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * 400, ArrowComponent->GetForwardVector().Y * 400, 0);
			Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);
			Projectile->SetActorRotation(FRotator(0, Hero->MouseAngle, 0));
		}
	}
}

// Called to bind functionality to input

void AGunBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

