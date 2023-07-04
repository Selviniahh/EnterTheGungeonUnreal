// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletManShotGun.h"
#include "Components/ArrowComponent.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"


// Sets default values
ABulletManShotGun::ABulletManShotGun()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABulletManShotGun::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxComponentBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (HealthComponent->IsDead && ShootAfterDeathOnce)
	{
		ShootAfterDeathOnce = false;
		ShootAfterDeath();
	}
}

// Called when the game starts or when spawned

void ABulletManShotGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void ABulletManShotGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

//So good so perfect 
void ABulletManShotGun::ShootProjectile()
{
	Super::ShootProjectile();
	
	if (HealthComponent->IsDead) return;
	
	//Store the original rotation of the ArrowComponent
	const FRotator OriginalRotation = Gun->ArrowComponent->GetRelativeRotation(); //0

	//Define the number of projectiles and the angle between them
	const int numberOfProjectiles = 4;
	const float angleBetweenProjectiles = 10.0f;

	//Loop to spawn each projectile
	for (int i = 0; i < numberOfProjectiles; i++)
	{
		//Calculate the rotation for this projectile
		float angle = (i - numberOfProjectiles / 2) * angleBetweenProjectiles;
		Gun->ArrowComponent->SetRelativeRotation(FRotator(angle,0,0));

		//Calculate the velocity for this projectile
		const FVector ProjectileVelocity = FVector(Gun->ArrowComponent->GetForwardVector().X * Gun->Velocity, Gun->ArrowComponent->GetForwardVector().Y * Gun->Velocity, 0);


		// Fire the projectile
		Gun->Shoot(ProjectileVelocity);
	}
	
	// Reset the rotation of the ArrowComponent
	Gun->ArrowComponent->SetRelativeRotation(OriginalRotation);
}

//Copy pasted and a little modified from ShootProjectile()
void ABulletManShotGun::ShootAfterDeath() const
{
	const FRotator OriginalRotation = Gun->ArrowComponent->GetRelativeRotation(); //0

	const int numberOfProjectiles = 6;

	for (int i = 0; i < numberOfProjectiles; i++)
	{
		float angle = (i - numberOfProjectiles / 2) * AngleDeathProjectile;
		Gun->ArrowComponent->SetRelativeRotation(FRotator(angle,0,0));
		const FVector ProjectileVelocity = FVector(Gun->ArrowComponent->GetForwardVector().X * Gun->Velocity, Gun->ArrowComponent->GetForwardVector().Y * Gun->Velocity, 0);
		Gun->Shoot(ProjectileVelocity, GetActorLocation());
	}
	
	Gun->ArrowComponent->SetRelativeRotation(OriginalRotation);
}


// Called to bind functionality to input
void ABulletManShotGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


