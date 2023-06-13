// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperZDAnimationComponent.h"

AEnemyBase::AEnemyBase()
{
	//Default Component definitions
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->InitBoxExtent(FVector(7.f,2.f,10.f));
	
	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	FlipBook->SetupAttachment(BoxCollision);

	AnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("AnimComponent"));
	AnimComponent->InitRenderComponent(FlipBook);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	//Adding Direction Ranges
	DirectionRanges = {
		{0.f, 30.f}, //Right
		{30.f, 65.f}, //Front Right
		{65.f, 100.f}, //Front
		{100.f, 160.f},//Front_Left
		{160.f, 185.f},//Back_Left
		{185.f, 240.f},//Left
		{240.f, 280.f},//Back
		{280.f, 320.f},//Back_Right
	};

	//Direction Dictionary
	DirectionVectors = {
		{Right, FVector2D(1,0)},
		{Left, FVector2D(-1,0)},
		{Back_Right, FVector2D(0,1)},
		{Front, FVector2D(0,-1)},
		{Back_Left, FVector2D(-1,-1)},
		{Front_Right, FVector2D(1,-1)},
		{Front_Left, FVector2D(-1,0)},
		{Back, FVector2D(0,1)},
	};


}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	//This may be problematic in the future
	Player = Cast<APaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));

}

void AEnemyBase::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
	EnemyLocation = GetActorLocation();
	DistanceBetweenHero = FVector::Distance(EnemyLocation,Player->GetActorLocation());

	//Temporary Fix for unknown reason enemy's Z axis is higher than player's Z axis
	SetActorLocation(FVector(EnemyLocation.X, EnemyLocation.Y, Player->GetActorLocation().Z));
	
	EnemyAngle = FMath::RadiansToDegrees(FMath::Atan2(Player->GetActorLocation().Y - EnemyLocation.Y, Player->GetActorLocation().X - EnemyLocation.X));
	if (EnemyAngle < 0)
		EnemyAngle += 360;
	
	 // Set Enemy Enum based on Direction
	 for (int i = 0; i < DirectionRanges.Num(); i++)
	 {
	 	if (EnemyAngle >= DirectionRanges[i].Min && EnemyAngle <= DirectionRanges[i].Max || (i == Right && EnemyAngle >= 320.f))
	 	{
	 		EnemyDirectionEnum = static_cast<EEnemyDirectionEnum>(i);
	 		EnemyDirectionVector = DirectionVectors[EnemyDirectionEnum];
	 		break;
	 	}
	 }
	//Set Right2 to Right because 320-360 must be right. 
	if (EnemyDirectionEnum == Right2)
		EnemyDirectionEnum = Right;

	//Just printing soon they will be gone
	// UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyDirectionEnum"), true);
	// if (!EnumPtr) return; 
	// FString EnumName = EnumPtr->GetNameByValue(static_cast<int32>(EnemyDirectionEnum)).ToString();
	// UE_LOG(LogTemp, Display, TEXT("EnemyDirection Direction: %s"), *EnumName);
	// UE_LOG(LogTemp, Display, TEXT("Angle: %f"), EnemyAngle);
	// UE_LOG(LogTemp, Display, TEXT("Direction: %s"), *EnemyDirectionVector.ToString());
	//
	// // UE_LOG(LogTemp, Display, TEXT("Direction: %f"), EnemyAngle);
}

void AEnemyBase::Move()
{
	// UE_LOG(LogTemp, Display, TEXT(Move"EnemyBase Function running now"));
}

void AEnemyBase::RotateEnemy(FVector Threshold)
{
	
}

void AEnemyBase::Death()
{
	
}

void AEnemyBase::Fire()
{
	
}



