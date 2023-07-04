// Fill out your copyright notice in the Description page of Project Settings.


#include "AngryBook.h"
#include "Components/ArrowComponent.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Hero/Hero.h"

// Sets default values

AAngryBook::AAngryBook()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootArrow = CreateDefaultSubobject<USceneComponent>(TEXT("RootArrow"));
	RootArrow->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetRelativeLocation(FVector(16,0,0));
	ArrowComponent->SetupAttachment(RootArrow);
}

void AAngryBook::BeginPlay()
{
	Super::BeginPlay();
	CurrentProjectileCount = 0;
	Gun->Tags.Add(GunTagName);
	//Call the function every 3 seconds which will shoot the projectile every 0.05 second
	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &AAngryBook::StartShooting,ShootRate,true);
}

//Shoot every 0.05 second

void AAngryBook::StartShooting()
{
	//Set everything to default state and then start timer again to make all shooting sequence again
	CurrentProjectileCount = 0;
	CurrentSpecialProjectileCount = 0;
	RootYNeg = 0;
	RootYPos = 0;
	bIsCharging = true;
	MovementComponent->MaxSpeed = 0;
	GetWorld()->GetTimerManager().SetTimer(ShootingSequenceTimer, this, &AAngryBook::Shoot, ProjectileSpawnRate, true);
	CurrentDirectionBeforeShoot = Hero->CurrentDirection;
	KnockBackMultiply = 10;
	KnockBackSpeed = 10;
}

void AAngryBook::Shoot()
{
	//If still normal spherical projectiles must spawn
	KnockBackMultiply = 0;
	KnockBackSpeed = 0;
	if (HealthComponent->IsDead || CurrentProjectileCount < NumberOfProjectiles)
	{
		float angle = (CurrentProjectileCount - NumberOfProjectiles / 2) * AngleBetweenProjectiles;
		RootArrow->SetRelativeRotation(FRotator(0,angle, 0));

		GunProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * ProjectileVelocity2, ArrowComponent->GetForwardVector().Y * ProjectileVelocity2, 0);
		Gun->Shoot(GunProjectileVelocity, ArrowComponent->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);

		CurrentProjectileCount++;
	}

	//If all the projectiles are spawned stop. And start spawning special ones
	else
	{
		//Start spawning
		if (CurrentSpecialProjectileCount < NumberOfSpecialProjectiles)
		{
			//if still in half spawn to up
			if (CurrentSpecialProjectileCount < NumberOfSpecialProjectiles/2)
			{
				RootArrow->SetRelativeRotation(FRotator(0,90,0));
				RootArrow->SetRelativeLocation(FVector(0,RootYNeg,0));
				GunProjectileVelocity = FVector(RootArrow->GetForwardVector().X * ProjectileVelocity2, RootArrow->GetForwardVector().Y * ProjectileVelocity2, 0);
				//I had to make - to velocity otherwise it's velocity was inverted but why? 
				Gun->Shoot(-GunProjectileVelocity, RootArrow->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
				CurrentSpecialProjectileCount++;
				RootYNeg -= 3;
			}
			//if above half start spawning to down direction.
			else if (CurrentProjectileCount > NumberOfSpecialProjectiles/2)
			{
				RootArrow->SetRelativeRotation(FRotator(0,270,0));
				RootArrow->SetRelativeLocation(FVector(0,RootYPos,0));

				GunProjectileVelocity = FVector(RootArrow->GetForwardVector().X * ProjectileVelocity2, RootArrow->GetForwardVector().Y * ProjectileVelocity2, 0);
				//I had to make - to velocity otherwise it's velocity was inverted but why? 
				Gun->Shoot(-GunProjectileVelocity, RootArrow->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
				CurrentSpecialProjectileCount++;
				RootYPos += 3;
			}
		}

		//If also all Special projectiles are spawned
		else
		{
			// Stop all the shooting sequence after all the projectiles are spawned
			RootArrow->SetRelativeRotation(FRotator(0,0,0));
			RootArrow->SetRelativeLocation(FVector(0,0,0));

			GetWorld()->GetTimerManager().ClearTimer(ShootingSequenceTimer);
		}
	}
}

// Called every frame
void AAngryBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GetWorld()->GetTimerManager().GetTimerRemaining(ShootingSequenceTimer) == -1)
	{
		bIsCharging = false;
		MovementComponent->MaxSpeed = MaxWalkSpeed;
	}

	//if it's dead clear timers and destroy the idle projectiles it was generating before death
	if (bIsDead)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShootingSequenceTimer);
		GetWorld()->GetTimerManager().ClearTimer(ShootTimer);
		FlipBook->SetVisibility(false);
		
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithTag(this, GunTagName, Actors);
		
		for (auto Actor : Actors)
		{
			AProjectileBase* Projectile = Cast<AProjectileBase>(Actor);
			if (Projectile->ProjectileMovement->Velocity.X == 0 && Projectile->ProjectileMovement->Velocity.Y == 0 )
			{
				Projectile->Destroy();
			}
		}
	}
}


// Called to bind functionality to input

void AAngryBook::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAngryBook::ShootProjectile()
{
	//Discard Shooting
}

