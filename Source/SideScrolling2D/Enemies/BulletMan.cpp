// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletMan.h"

#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "SideScrolling2D/Guns/Magnum.h"

ABulletMan::ABulletMan()
{
	//Giving Default values
	MoveRange = 100.0f;
	DistanceCannotShoot = 300.0f;
	ChargeShootAnimationLength = 0.5f;
	ShootsLeft = 1;
	CooldownTimer = 3.0f;
	KnockBackSpeed = 10.0f;
	KnockBackMultiply = 10.0f;
	ShouldBaseClassShoot = true;
	
	//This is not default
	MaxShoots = ShootsLeft;
	//Don't forget to set gun object, animBP
}

#include "SideScrolling2D/Actor Components/HealthComponent.h"

void ABulletMan::BeginPlay()
{
	Super::BeginPlay();
	MaxShoots = ShootsLeft;
	Tags.Add("Enemy");
	
	if (EnemyGun)
	{
		//Spawn adjust  and then set owner to let make checks if the gun is owned by the player or enemy? 
		Gun = GetWorld()->SpawnActor<AGunBase>(EnemyGun, HandSocket->GetComponentLocation(), HandSocket->GetComponentRotation());
		// Gun->Tags.Add("EnemyGun");
		Gun->SetActorScale3D(GunScale);
		Gun->SetOwner(this);

		//Attach gun to hand socket
		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		Gun->AttachToComponent(HandSocket, AttachmentTransformRules);
		Gun->SetActorRelativeLocation(AfterAttachRelativeLoc);
		
		JustPlayShootAnimation();

		//Get the health component
		HealthComponent = FindComponentByClass<UHealthComponent>();
	}
}

void ABulletMan::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
	CooldownTime += DelatTime;
	// UE_LOG(LogTemp, Display, TEXT("Cooldown: %f"), CooldownTime);


	//Check Timer for setting charging bool
	if (GetWorld()->GetTimerManager().IsTimerActive(PlayAnimationTimerHandle))
		CanCharge = true;
	else {CanCharge = false;}


	//Extra check to prevent null pointer
	if (!HealthComponent || !Gun) return;

	//Gun rotation
	FVector Direction = Hero->GetActorLocation() - GetActorLocation();
	float Degree =FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
	Gun->SetActorRotation(FRotator(0,Degree,0));

	//Setting is shooting false by default in tick 
	IsShooting = false;

	//Dead implementations
	if (HealthComponent != nullptr)
	{
		if (!HealthComponent->IsDead) return;
		if (Gun)
		{
			Gun->Destroy();
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
	if (Hero && !HealthComponent->IsDead && !bShouldKnockBack && !Spawning)
	{
		MovementDir = Hero->GetActorLocation() - GetActorLocation();
		MovementDir.Normalize();

		if (DistanceBetweenHero > MoveRange)
		{
			MovementComponent->AddInputVector(MovementDir);	
		}
	}
}

void ABulletMan::JustPlayShootAnimation()
{
	Super::JustPlayShootAnimation();
	//Make sure that enemy can shoot in enough distance
	if (DistanceCannotShoot < DistanceBetweenHero && HealthComponent->IsDead) return;


	if (Gun && GetWorld())
	{
		//Set timer to shoot after gun shoot animation
		IsShooting = true;

		//Gun animation will play and when it over it will hit ShootProjectile function.
		GetWorldTimerManager().SetTimer(PlayAnimationTimerHandle,this, &ABulletMan::ShootProjectile, ChargeShootAnimationLength, false);
	}
}

void ABulletMan::ShootProjectile()
{
	if (!HealthComponent->IsDead && ShouldBaseClassShoot)
	{
		const FVector ProjectileVelocity = FVector(Gun->ArrowComponent->GetForwardVector().X * Gun->Velocity, Gun->ArrowComponent->GetForwardVector().Y * Gun->Velocity, 0);
		Gun->Shoot(ProjectileVelocity);

		//Decrement ShootsLeft and start cooldown if it reaches 0
		ShootsLeft --;
		if (ShootsLeft == 0)
		{
			ShootsLeft = MaxShoots; //reset for the next round
			//Stop shooting timer and start cooldown timer
			GetWorldTimerManager().ClearTimer(FireTimerHandle);
			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ABulletMan::CooldownFinished, CooldownTimer, false);
		}
		else
		{
			JustPlayShootAnimation();
		}
	}
}

void ABulletMan::CooldownFinished()
{
	JustPlayShootAnimation();
}


