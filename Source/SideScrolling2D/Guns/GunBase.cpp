//1.  First determine if the gun is equipped by enemy or gun. Because I will make the logic separate between if the gun equipped from player or enemy. (Use Owner) 
//2. No need to think how can you set owner to the nemey or player. 

#include "GunBase.h"

#include "SideScrolling2D/Hero/Hero.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/TransformCalculus3D.h"
#include "SideScrolling2D/Projectiles/ProjectileBase.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	FlipBook->SetupAttachment(DefaultSceneRoot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(FlipBook);

	MuzzleFlash = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MuzzleFlash"));
	MuzzleFlash->SetupAttachment(BoxComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxComponent);

	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperZDAnimation"));
	PaperZDAnimation->InitRenderComponent(FlipBook);

	//Delete all of these later on
	PressTime = 0.3f;
	Velocity = 400.f;
	MaxProjectileRange = 150.f;
	
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Gun");

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
	MuzzleFlash->SetVisibility(false);
	MuzzleFlash->SetLooping(false);
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Hero)
	{
		PressedTimer += DeltaTime;
	}

	//I deleted here and it worked.
	// if (GetOwner() == (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	// {
	// 	if (Hero->IsDashingCpp || !Hero->IsShooting)
	// 	{
	// 		MuzzleFlash->SetLooping(false);
	// 		MuzzleFlash->SetVisibility(false);
	// 	}
	// }
	// else
	// {
	// 	//if gun's owner is not player than disable muzzle flash 
	// 	MuzzleFlash->SetLooping(false);
	// 	MuzzleFlash->SetVisibility(false);
	// }

}

void AGunBase::Shoot()
{

	//first check if the owner is player (Maybe this gun is equipped from enemy) If hero is dashing or after the dash if cooldown (Run Timer) is <1 than DON'T SHOOT! 
	if (GetOwner() == (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		if (Hero->IsDashingCpp || 0.1 >= Hero->RunTimer) return;
	}
	
	if (PressedTimer > PressTime && GetWorld())
	{
		PressedTimer = 0;

		//Define the spawn location and rotation
		const FVector Location = ArrowComponent->GetComponentLocation();
		const FRotator Rotation = FRotator(0,0,0);

		//Spawn for enemy
		if (GetOwner() != (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
		{
			AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, Rotation);
			Projectile->SetOwner(this);
			Projectile->MaxProjectileRange = MaxProjectileRange;

			//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 
			const FVector ProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * Velocity, ArrowComponent->GetForwardVector().Y * Velocity, 0);

			Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);
			Hero->GetAngle();
			Projectile->SetActorRotation(FRotator(0, Hero->MouseAngle, 0));
		}

		//Spawn for hero
		else if (ProjectileType && !Hero->IsDashingCpp)
		{
			AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, Rotation);
			Projectile->SetOwner(this);
			Projectile->MaxProjectileRange = MaxProjectileRange;

			//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 
			const FVector ProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * Velocity, ArrowComponent->GetForwardVector().Y * Velocity, 0);

			Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);
			Hero->GetAngle();
			Projectile->SetActorRotation(FRotator(0, Hero->MouseAngle, 0));
		}
	}
}

// Called to bind functionality to input
void AGunBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

