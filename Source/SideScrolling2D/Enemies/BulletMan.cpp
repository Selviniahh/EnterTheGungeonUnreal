// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletMan.h"

#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "SideScrolling2D/Guns/Magnum.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"

ABulletMan::ABulletMan()
{
		
}

void ABulletMan::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyGun)
	{
		Tags.Add("Enemy");
		//Spawn diminish a little and then set owner to let make checks if the gun is owned by the player or enemy? 
		MagnumGun = GetWorld()->SpawnActor<AGunBase>(EnemyGun, HandSocket->GetComponentLocation(), HandSocket->GetComponentRotation());
		MagnumGun->Tags.Add("EnemyGun");
		MagnumGun->SetActorScale3D(GunScale);
		MagnumGun->SetOwner(this);

		//Attach gun to hand socket
		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		MagnumGun->AttachToComponent(HandSocket, AttachmentTransformRules);
		MagnumGun->SetActorRelativeLocation(AfterAttachRelativeLoc);
		
		//Set timer
		GetWorldTimerManager().SetTimer(FireTimerHandle,this, &ABulletMan::JustPlayShootAnimation, FireRate, true);

		//Get the health component
		HealthComponent = FindComponentByClass<UHealthComponent>();
		
	}
}

void ABulletMan::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
	CooldownTime += DelatTime;

	//Make Shooting cooldown 
	if (CooldownTime > CooldownTimer) //5 
	{
		GetWorld()->GetTimerManager().PauseTimer(FireTimerHandle);
		CooldownDuration += DelatTime;
		if (CooldownDuration > CooldownDurationTimer)
		{
			CooldownTime = 0;
			CooldownDuration = 0;
			GetWorld()->GetTimerManager().UnPauseTimer(FireTimerHandle);
		}
	}

	//Extra check to prevent null pointer
	if (HealthComponent == nullptr) return;

	//MagnumGun rotation
	FVector Direction = Hero->GetActorLocation() - GetActorLocation();
	float Degree =FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
	MagnumGun->SetActorRotation(FRotator(0,Degree,0));

	//Setting is shooting false by default in tick
	IsShooting = false;

	//If Dead
	if (HealthComponent != nullptr)
	{
		if (!HealthComponent->IsDead) return;
		if (MagnumGun)
		{
			MagnumGun->Destroy();
			HandComponent->SetVisibility(false);
			CanSetDirection = false; 
		}
	}
	
	//Lastly Move
	Move();
}

void ABulletMan::Move()
{
	Super::Move();
	if (Hero && !HealthComponent->IsDead && !bShouldKnockBack)
	{
		FVector Movement = Hero->GetActorLocation() - GetActorLocation();
		Movement.Normalize();

		if (DistanceBetweenHero > MoveRange)
		{
			MovementComponent->AddInputVector(Movement);	
		}
	}
}

void ABulletMan::JustPlayShootAnimation()
{
	Super::JustPlayShootAnimation();
	//Make sure that enemy can shoot in enough distance
	if (DistanceCannotShoot < DistanceBetweenHero && HealthComponent->IsDead) return;
	

	if (MagnumGun && GetWorld())
	{
		//Set timer to shoot after gun shoot animation
		IsShooting = true;
		
		GetWorldTimerManager().SetTimer(PlayAnimationTimerHandle,this, &ABulletMan::ShootProjectile, ShootAnimationLength, false);
	}
}

void ABulletMan::ShootProjectile()
{
	if (!HealthComponent->IsDead)
	{
		MagnumGun->Shoot();
	}
}

