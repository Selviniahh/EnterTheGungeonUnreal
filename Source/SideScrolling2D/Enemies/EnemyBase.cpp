// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperZDAnimationComponent.h"
#include "Components/BoxComponent.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
#include "SideScrolling2D/Guns/GunBase.h"


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
	
	Ranges.Add(FRanges(1,35)); //Right
	Ranges.Add(FRanges(35,75)); //Front Hand Right
	Ranges.Add(FRanges(75,135)); //Front Hand Left
	Ranges.Add(FRanges(135,190)); //Left
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

	//Giving the defaults values
	HandCompLoc = FVector2D(9.0,7.0);
	HandCompLocFlip = FVector2D(-8.0,7.0);
	GunScale = FVector(1.0f,1.0f,1.0f);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
	Tags.Add("Enemy");
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBoxComponentBeginOverlap);
	BoxExtend = FVector(BoxCollision->GetScaledBoxExtent().X + PathTileBuffer,BoxCollision->GetScaledBoxExtent().Z + PathTileBuffer, BoxCollision->GetScaledBoxExtent().Y);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Hero) return;
	
	EnemyLocation = GetActorLocation();
	DistanceBetweenHero = FVector::Distance(EnemyLocation,Hero->GetActorLocation());
	
	if (CanSetDirection)
	{
		SetEnemyDirectionEnum();
	}
	
	//KnockBack
	if (bShouldKnockBack || HealthComponent->IsDead)
	{
		const FVector NewLocation = (FMath::VInterpTo(GetActorLocation(), EnemyTargetLocation, DeltaTime, KnockBackSpeed));
		SetActorLocation(NewLocation);
		Timer += DeltaTime;
		//Making sure KnockBack is finished
		if (NewLocation.Equals(EnemyTargetLocation,1.0f) || Timer > 0.5)
		{
			bShouldKnockBack = false;
			Timer = 0;
		}
	}
	SecTimer += DeltaTime;
	if (!bShouldKnockBack && SecTimer > 0.05) //50ms delay
	{
		FoundPath = PathFinding();
		SecTimer = 0;
	}
	MoveAlongPath(DeltaTime);

}

void AEnemyBase::Move()
{
	//Empty 
}

void AEnemyBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HealthComponent->IsDead && !OtherActor->ActorHasTag("EnemyGun") && !OtherActor->ActorHasTag("EnemyProjectile"))
	{
		//KnockBack logic                     //projectile
		DeadDirection3D = GetActorLocation() - OtherActor->GetActorLocation();
		DeadDirection3D.Normalize();
		DeadDirection = FVector2D(DeadDirection3D.X, DeadDirection3D.Y);
		//Target must be move away so it has to be location + dead direction 
		EnemyTargetLocation = GetActorLocation() + FVector(DeadDirection.X * KnockBackMultiply,DeadDirection.Y * KnockBackMultiply, 0);

		if (Cast<ARoomActor>(OtherActor) || OtherActor->ActorHasTag("EnemyProjectile"))
		{
			return;
		}
		
		bShouldKnockBack = true; 
	}
}

void AEnemyBase::SetEnemyDirectionEnum()
{
	if (!bCanSetDirectionAndFlip) return;
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
		HandComponent->SetRelativeLocation(FVector(HandCompLoc.X,HandCompLoc.Y,0.0));
		HandSocket->SetRelativeScale3D(FVector(1.0,1.0,1.0));
		HandSocket->SetRelativeRotation(FRotator(EnemyAngle * -1,0,90));
	}
	//Flip
	else
	{
		FlipBook->SetRelativeScale3D(FVector(-1.0,-1.0,1.0));
		HandComponent->SetRelativeLocation(FVector(HandCompLocFlip.X,HandCompLocFlip.Y,0.0));
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

TArray<FVector> AEnemyBase::PathFinding()
{
	TArray<TSharedPtr<FMovementNode>> OpenList;
	TArray<TSharedPtr<FMovementNode>> VisitedNodes; //Closed list
	int IterationCount = 0; 
	
	FVector2D StartIndex = WorldToIndex(GetActorLocation()); //Start from your own location
	FVector2D EndIndex = WorldToIndex(Hero->GetActorLocation()); //Start from your own location
	TSharedPtr<FMovementNode> StartNode = MakeShared<FMovementNode>(StartIndex.X,StartIndex.Y);
	TSharedPtr<FMovementNode> EndNode = MakeShared<FMovementNode>(EndIndex.X,EndIndex.Y);

 	StartNode->Hcost =FMovementNode::GetHCost(StartIndex.X,StartIndex.Y,EndIndex.X,EndIndex.Y);
	
	OpenList.Add(StartNode);
	VisitedNodes.Add(StartNode);

	while (OpenList.Num() > 0)
	{
		IterationCount++;
		if (OpenList.Num() > 1)
			Algo::Sort(OpenList, [StartNode,EndNode](TSharedPtr<FMovementNode>& A, TSharedPtr<FMovementNode>& B) {
			if (A->FCost() == B->FCost()) {
			if (A->Hcost == B->Hcost) {
				// Calculate the distance to the line from start to end for each node
				float DistA = FMath::PointDistToLine(A->Location, EndNode->Location - StartNode->Location, StartNode->Location);
				float DistB = FMath::PointDistToLine(B->Location, EndNode->Location - StartNode->Location, StartNode->Location);
				return DistA < DistB;
			}
			return A->Hcost < B->Hcost;
		}
		return A->FCost() < B->FCost();
		});
		
		TSharedPtr<FMovementNode> CurrentNode = OpenList[0];
		OpenList.RemoveAt(0);

		if (OpenList.Num() >= 10000)
		{
			break;
		}
		
		if (OpenList.Num() > 300 || IterationCount > MaxIterationAmount || (CurrentNode->X == EndNode->X && CurrentNode->Y == EndNode->Y))
		{
			UE_LOG(LogTemp, Display, TEXT("OpenList: %d"), OpenList.Num());
			UE_LOG(LogTemp, Display, TEXT("Iteration Count: %d"), IterationCount);
			UE_LOG(LogTemp, Display, TEXT("Path Cost: %d"), CurrentNode->GCost);

			//We reached to destination now we need to backtrack, make a stack that will backtrack first and then get it's first element and try to move to it's destination and so on.
			TArray<FVector> Path;
			while (CurrentNode->Parent != nullptr)
			{
				Path.Add(CurrentNode->Parent->Location);
				DrawDebugBox(GetWorld(),CurrentNode->Parent->Location ,BoxExtend, FQuat::Identity, FColor::Green, false, 0.06f, 0, 1.0f);
				CurrentNode = CurrentNode->Parent;
			}
			
			Algo::Reverse(Path);
			return Path; //look here
		}

		for (int i = 0; i < Row.Num(); ++i)
		{
			int NewX = CurrentNode->X + Row[i];
			int NewY = CurrentNode->Y + Col[i];

			TSharedPtr<FMovementNode> Neighbour = MakeShared<FMovementNode>(NewX,NewY);
			if (IsWalkable(NewX,NewY) && !Contains(VisitedNodes, Neighbour)) //!Contain(VisitedNodes,Neighbour)
			{
				int CostToMove = CurrentNode->GCost + 1; //Since every iteration it moving one tile, it costs +1 more for every neighbour.

				if (CostToMove < Neighbour->GCost || !OpenList.Contains(Neighbour)) //You can ignore this block
				{
					Neighbour->GCost = CostToMove;
					Neighbour->Hcost = FMovementNode::GetHCost(NewX,NewY,EndNode->X,EndNode->Y);
					Neighbour->Parent = CurrentNode;
					OpenList.Add(Neighbour);
					VisitedNodes.Add(Neighbour);
				}
			}
		}

	}
	return {};
}

bool AEnemyBase::IsWalkable(int X, int Y)
{
	FVector WorldLocation = IndexToWorld(X,Y);

	TArray<FOverlapResult> Overlaps;
	
	FCollisionQueryParams ColParams;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	if (Gun)
	{
		ActorsToIgnore.Add(Gun);
	}
	ColParams.AddIgnoredActors(ActorsToIgnore);
	bool bHasOverlap = GetWorld()->OverlapMultiByChannel(Overlaps,WorldLocation,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeBox(BoxExtend), ColParams);
	if (bHasOverlap)
	{
		DrawDebugBox(GetWorld(),WorldLocation ,BoxExtend, FQuat::Identity, FColor::Red, false, 0.05f, 0, 1.0f);
	}
	return !bHasOverlap;
	
}

bool AEnemyBase::Contains(TArray<TSharedPtr<FMovementNode>> VisitedNodes, TSharedPtr<FMovementNode> Neighbour)
{
	for (auto Node : VisitedNodes)
	{
		if (Node->X == Neighbour->X && Node->Y == Neighbour->Y)
		{
			return true;
		}
	}
	return false;
}

void AEnemyBase::MoveAlongPath(float DeltaTime)
{
	if (FoundPath.Num() == 0 || CurrentPathIndex >= FoundPath.Num() || bShouldKnockBack)
	{
		return; // No path or reached the end
	}
	FVector TargetLocation = FoundPath[CurrentPathIndex];
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	// UE_LOG(LogTemp, Display, TEXT("Direction: %s"), *Direction.ToString());
	float DistanceToTarget = (TargetLocation - GetActorLocation()).Size();

	if (DistanceToTarget > 7) // Use a small radius for acceptance
		{
			MovementComponent->AddInputVector(Direction * DeltaTime * 500, true);
		}
	else
	{
		CurrentPathIndex++; // Move to the next point in the path only if we are close enough to the current target (DebugBox) 
	}
}


