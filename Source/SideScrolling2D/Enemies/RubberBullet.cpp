// Fill out your copyright notice in the Description page of Project Settings.


#include "RubberBullet.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ARubberBullet::ARubberBullet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//DistanceCannotShoot = 0;
	//Move Range = 0;
}

// Called when the game starts or when spawned
void ARubberBullet::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("RubberBullet");
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ARubberBullet::ShootProjectile, ChargeShootAnimationLength, false);
	
}

//Attack for RubberBullet. Don't let it fool you by function name
void ARubberBullet::ShootProjectile()
{
	//Discard this function by not calling SUPER

	//Charge animation is played in justPlayShootAnimation function and then this function hit
	bIsAttacking = true;
	
}

void ARubberBullet::JustPlayShootAnimation()
{
	//empty
}

void ARubberBullet::Move()
{
	if (bIsAttacking)
	{
		if (bAttackingFinished)
		{
			//Start attacking to hero direction. Determine direction for once until it got hit by something.
			if (Hero && !HealthComponent->IsDead && bAttackingFinished)
			{
				MovementDir = Hero->GetActorLocation() - GetActorLocation();
				MovementDir.Normalize();
				MovementComponent->MaxSpeed = AttackSpeed;
				MovementComponent->Acceleration = AttackSpeed;

				MovementComponent->AddInputVector(MovementDir);
				bCanSetDirectionAndFlip = false;
			}
			bAttackingFinished = false;
		}
		else
		{
			MovementComponent->AddInputVector(MovementDir);
		}
		
	}
	
	else 
	{
		//Move normal if it's not attacking already
		MovementComponent->MaxSpeed = RunSpeed;
		MovementComponent->Acceleration = RunSpeed;
		bCanSetDirectionAndFlip = true;
		Super::Move();
	}
	
}

void ARubberBullet::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//For now discard parent logic

	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ARubberBullet::ShootProjectile, CooldownTimer, false);
	bAttackingFinished = true;
	
	if (bIsAttacking)
	{
		OverlappedActor = OtherActor;
		DeadDirection3D = GetActorLocation() - OtherActor->GetActorLocation();
		DeadDirection3D.Normalize();
		DeadDirection = FVector2D(DeadDirection3D.X, DeadDirection3D.Y);
		EnemyTargetLocation = GetActorLocation() + FVector(DeadDirection.X * KnockBackMultiply,DeadDirection.Y * KnockBackMultiply, 0);

		FVector HeroDeadDirection3D = Hero->GetActorLocation() - GetActorLocation();
		HeroDeadDirection3D.Normalize();
		FVector2D HeroDeadDirection = FVector2D(HeroDeadDirection3D.X, HeroDeadDirection3D.Y);
		//I multiplied by 2 because for hero it was too low 
		HeroTargetLocation = Hero->GetActorLocation() + FVector(HeroDeadDirection.X * KnockBackMultiply * 2,HeroDeadDirection.Y * KnockBackMultiply * 2, 0);

	}
	bIsAttacking = false;
}


// Called every frame
void ARubberBullet::Tick(float DeltaTime)
{
	//Scarped Tick and copy pasted to things that need it
	Super::Tick(DeltaTime);
	//End of copy paste

	//KnockBack both enemy and player
	if (bShouldKnockBack && OverlappedActor)
	{
		//KnockBack Hero
		if (OverlappedActor == Hero || OverlappedActor->GetOwner() == Hero)
		{
			const FVector NewLocation = (FMath::VInterpTo(Hero->GetActorLocation(), HeroTargetLocation, GetWorld()->GetDeltaSeconds(), KnockBackSpeed));
			Hero->SetActorLocation(NewLocation);

			//Making sure KnockBack is finished
			if (NewLocation.Equals(HeroTargetLocation,1.0f))
			{
				bShouldKnockBack = false;
			}

			//KnockBack Enemy
			const FVector NewLocation2 = (FMath::VInterpTo(GetActorLocation(), EnemyTargetLocation, GetWorld()->GetDeltaSeconds(), KnockBackSpeed));
			SetActorLocation(NewLocation2);

			//Making sure KnockBack is finished
			if (NewLocation2.Equals(EnemyTargetLocation,1.0f))
			{
				bShouldKnockBack = false;
			}
		}

		//If overlap is not enemy, just knockback self
		else
		{
			const FVector NewLocation = (FMath::VInterpTo(GetActorLocation(), EnemyTargetLocation, GetWorld()->GetDeltaSeconds(), KnockBackSpeed));
			SetActorLocation(NewLocation);

			//Making sure KnockBack is finished
			if (NewLocation.Equals(EnemyTargetLocation,1.0f))
			{
				bShouldKnockBack = false;
			}
		}
	}

	// >4.6 and != -1
	if (GetWorld()->GetTimerManager().GetTimerRemaining(AttackTimerHandle) > 4.6 && GetWorld()->GetTimerManager().GetTimerRemaining(AttackTimerHandle) != -1.0)
		PlayImpact = true;
	else
		PlayImpact = false;

	// < 1.0 and != -1
	if (GetWorld()->GetTimerManager().GetTimerRemaining(AttackTimerHandle) < 1.0 && GetWorld()->GetTimerManager().GetTimerRemaining(AttackTimerHandle) != -1.0)
		PlayCharge = true;
	else
		PlayCharge = false;
}

// Called to bind functionality to input
void ARubberBullet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

