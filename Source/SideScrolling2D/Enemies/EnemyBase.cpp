// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperZDAnimationComponent.h"
#include "Components/BoxComponent.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Hero/Hero.h"

AEnemyBase::AEnemyBase()
{
	//Default Component definitions
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	FlipBook->SetupAttachment(RootComponent);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(FlipBook);
	BoxCollision->InitBoxExtent(FVector(7.f,2.f,10.f));

	HandComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("HandComponent"));
	HandComponent->SetupAttachment(RootComponent);

	HandSocket = CreateDefaultSubobject<USceneComponent>(TEXT("HandSocket"));
	HandSocket->SetupAttachment(HandComponent);

	AnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("AnimComponent"));
	AnimComponent->InitRenderComponent(FlipBook);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	
	Ranges.Add(FRanges(1,55)); //Right
	Ranges.Add(FRanges(55,75)); //Front Hand Right
	Ranges.Add(FRanges(75,115)); //Front Hand Left
	Ranges.Add(FRanges(115,190)); //Left
	Ranges.Add(FRanges(190,245)); //Diagonal_Left
	Ranges.Add(FRanges(245,265)); //Back_Hand_Left
	Ranges.Add(FRanges(265,290)); //Back_Hand_Right
	Ranges.Add(FRanges(290,310)); //Diagonal_Right


	SetDirectionBasedOnEnum = {
		{EDirections::Right, FVector2D(1.0, 0.0)},
		{EDirections::Front_Hand_Right, FVector2D(-1.0, -1.0)},
		{EDirections::Front_Hand_Left, FVector2D(-1.0, -1.0)},
		{EDirections::Left, FVector2D(-1.0, 0.0)},
		{EDirections::Back_Diagonal_Left, FVector2D(-1.0, 1.0)},
		{EDirections::Back_Hand_Left, FVector2D(0, 1.0)},
		{EDirections::Back_Hand_Right, FVector2D(0, 1.0)},
		{EDirections::Back_Diagonal_Right, FVector2D(1.0, 1.0)},
	};
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
	Tags.Add("Enemy");
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBoxComponentBeginOverlap);
}

void AEnemyBase::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
	EnemyLocation = GetActorLocation();
	if (!Hero) return;
	Move();
	
	DistanceBetweenHero = FVector::Distance(EnemyLocation,Hero->GetActorLocation());

	if (CanSetDirection)
	{
		SetEnemyDirectionEnum();
	}

	//KnockBack
	if (bShouldKnockBack || HealthComponent->IsDead)
	{
		const FVector NewLocation = (FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), KnockBackSpeed));
		SetActorLocation(NewLocation);

		if (NewLocation.Equals(TargetLocation,1.0f))
		{
			bShouldKnockBack = false;
		}
	}
}

void AEnemyBase::Move()
{
	//Later
}

void AEnemyBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HealthComponent->IsDead && !OtherActor->ActorHasTag("EnemyGun"))
	{
		// UE_LOG(LogTemp, Display, TEXT("Overlap is working %s "), *OtherActor->GetName());

		DeadDirection3D = GetActorLocation() - OtherActor->GetActorLocation();
		DeadDirection3D.Normalize();
		DeadDirection = FVector2D(DeadDirection3D.X, DeadDirection3D.Y);
		TargetLocation = GetActorLocation() + FVector(DeadDirection.X * KnockBackMultiply,DeadDirection.Y * KnockBackMultiply, 0);

		bShouldKnockBack = true; 
	}
}

void AEnemyBase::SetEnemyDirectionEnum()
{
	//Set direction and FlipBook based on the angle between the enemy and the hero
	EnemyAngle = FMath::RadiansToDegrees(FMath::Atan2(Hero->GetActorLocation().Y - EnemyLocation.Y, Hero->GetActorLocation().X - EnemyLocation.X));
	if (EnemyAngle < 0)
		EnemyAngle += 360;
	
		for (int i = 0; i < Ranges.Num(); ++i)
		{
			if (EnemyAngle >= Ranges[i].Min && EnemyAngle < Ranges[i].Max)
			{
			CurrentDirection = StaticCast<EDirections>(i);
				break;
			}
			if (EnemyAngle > 310 && EnemyAngle < 360)
			{
				CurrentDirection = Right;
			}
		}
		if (SetDirectionBasedOnEnum.Contains(CurrentDirection))
		{
			EnemyMovementDirection = SetDirectionBasedOnEnum[CurrentDirection];
		}

	if (CurrentDirection == Right || CurrentDirection == Front_Hand_Right || CurrentDirection == Back_Diagonal_Right || CurrentDirection == Back_Hand_Right)
	{
		FlipBook->SetRelativeScale3D(FVector(1.0,1.0,1.0));
		HandComponent->SetRelativeLocation(FVector(8.0,7,0.0));
		HandSocket->SetRelativeScale3D(FVector(1.0,1.0,1.0));
		HandSocket->SetRelativeRotation(FRotator(EnemyAngle * -1,0,90));
	}
	//Flip
	else
	{
		FlipBook->SetRelativeScale3D(FVector(-1.0,-1.0,1.0));
		HandComponent->SetRelativeLocation(FVector(-9.0,7,0.0));
		HandSocket->SetRelativeScale3D(FVector(1.0,-1.0,1.0));
		HandSocket->SetRelativeRotation(FRotator(EnemyAngle * -1,0,90));

	}
}

void AEnemyBase::Death()
{
	
}

void AEnemyBase::JustPlayShootAnimation()
{
	
}



