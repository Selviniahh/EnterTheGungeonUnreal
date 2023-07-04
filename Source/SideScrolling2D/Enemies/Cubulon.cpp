// Fill out your copyright notice in the Description page of Project Settings.


#include "Cubulon.h"
#include "Components/ArrowComponent.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"

// Sets default values
ACubulon::ACubulon()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACubulon::Shoot()
{
	//Start spawning
	if (HealthComponent->IsDead) return;
	if (CurrentRightUpProjectile < RightUpProjectileCount)
	{
		ArrowComponent->AddRelativeLocation(FVector(-ProjectileOffset,-ProjectileOffset,0));
		GunProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * ProjectileVelocity, ArrowComponent->GetForwardVector().Y * ProjectileVelocity, 0);

		//Move Up 
		if (ShouldProjectileMoveUp())
			GunProjectileVelocity = FVector(0,-150,0);
		//Move Right
		else
			GunProjectileVelocity = FVector(150,0,0);
	

		Gun->Shoot(GunProjectileVelocity, ArrowComponent->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
		CurrentRightUpProjectile ++;
	}
	
	else if (CurrentLeftUpProjectile < LeftUpProjectileCount)
	{
		ArrowComponent->SetRelativeRotation(FRotator(0,-180,0));
		ArrowComponent->AddRelativeLocation(FVector(-ProjectileOffset,ProjectileOffset,0));

		if (ShouldProjectileMoveUp())
			GunProjectileVelocity = FVector(0,-150,0);
		else
			GunProjectileVelocity = FVector(-150,0,0);
		
		Gun->Shoot(GunProjectileVelocity, ArrowComponent->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
		CurrentLeftUpProjectile ++;
	}
	else if (CurrentLeftDownProjectile < LeftDownProjectileCount)
	{
		ArrowComponent->SetRelativeRotation(FRotator(0,-180,0));
		ArrowComponent->AddRelativeLocation(FVector(ProjectileOffset,ProjectileOffset,0));

		if (ShouldProjectileMoveUp())
			GunProjectileVelocity = FVector(0,150,0);
		else
			GunProjectileVelocity = FVector(-150,0,0);
		
		Gun->Shoot(GunProjectileVelocity, ArrowComponent->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
		CurrentLeftDownProjectile ++;
	}

	else if (CurrentRightDownProjectile < RightDownProjectileCount)
	{
		ArrowComponent->SetRelativeRotation(FRotator(0,0,0));
		ArrowComponent->AddRelativeLocation(FVector(ProjectileOffset,-ProjectileOffset,0));

		if (ShouldProjectileMoveUp())
			GunProjectileVelocity = FVector(0,150,0);
		else
			GunProjectileVelocity = FVector(150,0,0);
		
		Gun->Shoot(GunProjectileVelocity, ArrowComponent->GetComponentLocation(), Delay, CurrentProjectileCount, NumberOfProjectiles);
		CurrentRightDownProjectile ++;
	}
	
	else
	{
		// Stop all the shooting sequence after all the projectiles are spawned
		RootArrow->SetRelativeRotation(FRotator(0,0,0));
		RootArrow->SetRelativeLocation(FVector(0,0,0));

		GetWorld()->GetTimerManager().ClearTimer(ShootingSequenceTimer);
	}
}

void ACubulon::StartShooting()
{
	//Reset everything
	Super::StartShooting();
	CurrentRightUpProjectile = 0;
	CurrentRightDownProjectile = 0;
	CurrentLeftUpProjectile = 0;
	CurrentLeftDownProjectile = 0;
}

// Called when the game starts or when spawned
void ACubulon::BeginPlay()
{
	Super::BeginPlay();
	Gun->GunTagName = "Cubulon";
	
}

bool ACubulon::ShouldProjectileMoveUp() const
{
	return CurrentDirectionBeforeShoot == Front_Hand_Right 
		|| CurrentDirectionBeforeShoot == Front_Hand_Left 
		|| CurrentDirectionBeforeShoot == Back_Diagonal_Right 
		|| CurrentDirectionBeforeShoot == Back_Diagonal_Left 
		|| CurrentDirectionBeforeShoot == Back_Hand_Left 
		|| CurrentDirectionBeforeShoot == Back_Hand_Right;
}

// Called every frame
void ACubulon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACubulon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

