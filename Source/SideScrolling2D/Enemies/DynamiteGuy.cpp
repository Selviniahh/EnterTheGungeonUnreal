// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamiteGuy.h"

#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "Components/BoxComponent.h"


// Sets default values
ADynamiteGuy::ADynamiteGuy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned

void ADynamiteGuy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADynamiteGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (FVector::Distance(Hero->GetActorLocation(), GetActorLocation()) < 50 || HealthComponent->Health <= 70)
	{
		//Play explode anim after 0.5 make invisible 
		CanExplode = true;
		MovementComponent->Velocity = FVector::ZeroVector;
		if(!GetWorld()->GetTimerManager().IsTimerActive(DeathTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(DeathTimer,this,&ADynamiteGuy::ExplodeAndDie, 0.5f,false);
		}

		//Shoot every 0.07 seconds for 5 times
		if(!GetWorld()->GetTimerManager().IsTimerActive(AttackTimer)) 
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &ADynamiteGuy::Attack, 0.07f, true);
		}
	}

	if (OffsetMultiplyer > 120)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
		
		HealthComponent->IsDead = true;
		KnockBackMultiply = 0;
	}
}


void ADynamiteGuy::Attack()
{
	if (!Gun) return;
	const FVector Location = Gun->ArrowComponent->GetComponentLocation();
	Gun->Shoot(FVector::Zero(), Location + FVector(Gun->ArrowComponent->GetForwardVector().X * OffsetMultiplyer,Gun->ArrowComponent->GetForwardVector().Y *OffsetMultiplyer,0));
		
	OffsetMultiplyer += 35;
}

void ADynamiteGuy::ExplodeAndDie()
{
	HealthComponent->IsDead = true;
	FlipBook->SetVisibility(false);
}


// Called to bind functionality to input
void ADynamiteGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

