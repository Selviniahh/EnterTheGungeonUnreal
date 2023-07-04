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
#include "SideScrolling2D/Projectiles/ProjectileBase.h"
#include "DrawDebugHelpers.h"

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
	BoxComponent->InitBoxExtent(FVector(9,2,3));

	MuzzleFlash = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MuzzleFlash"));
	MuzzleFlash->SetupAttachment(BoxComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxComponent);
	ArrowComponent->SetRelativeLocation(FVector(25,0,2));

	PaperZDAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperZDAnimation"));
	PaperZDAnimation->InitRenderComponent(FlipBook);

	//Giving default values 
	PressTime = 0.3f;
	Velocity = 400.f;
	MaxProjectileRange = 5000.f;

	
	
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
	MuzzleFlash->SetVisibility(false);
	MuzzleFlash->SetLooping(false);
	
}

// Called every frame

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


void AGunBase::Shoot()
{
	
	//first check if the owner is player (Maybe this gun is equipped from enemy) If hero is dashing or after the dash if cooldown (Run Timer) is <1 than DON'T SHOOT! 
	if (GetOwner() == (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		if (Hero->IsDashingCpp || 0.1 >= Hero->RunTimer) return;
	}
	
	if (GetWorld())
	{
		//Define the spawn location and rotation
		const FVector Location = ArrowComponent->GetComponentLocation();
		const FRotator Rotation = FRotator(0,0,0);

		//Spawn for enemy Base function that has been copy pasted many times
		if (GetOwner() != (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
		{
			if (LineTrace() && bShouldCheckLineTrace) return;
			AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, Rotation);
			Projectile->Tags.Add("EnemyProjectile");
			Projectile->ProjectileType = EprojectileType::ENEMY_PROJECTILE;
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
			Projectile->ProjectileType = EprojectileType::PLAYER_PROJECTILE;

			Projectile->MaxProjectileRange = MaxProjectileRange;

			//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 
			const FVector ProjectileVelocity = FVector(ArrowComponent->GetForwardVector().X * Velocity, ArrowComponent->GetForwardVector().Y * Velocity, 0);


			Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);
			Hero->GetAngle();
			Projectile->SetActorRotation(FRotator(0, Hero->MouseAngle, 0));
		}
	}
}

//Extra shoot function for cool shootings 2. copy
void AGunBase::Shoot(const FVector& ProjectileVelocity)
{
	const FVector Location = ArrowComponent->GetComponentLocation();

	if (GetOwner() != (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		if (LineTrace() && bShouldCheckLineTrace) return;
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, FRotator(0,0,0));
		Projectile->Tags.Add("EnemyProjectile");
		Projectile->ProjectileType = EprojectileType::ENEMY_PROJECTILE;
		Projectile->SetOwner(this);
		Projectile->MaxProjectileRange = MaxProjectileRange;

		//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 

		Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);

		Projectile->SetActorRotation(FRotator(0, Hero->MouseAngle, 0));
	}
}

//Extra shoot function for cool shootings including location 3. copy
void AGunBase::Shoot(const FVector& ProjectileVelocity, const FVector& Location)
{

	if (GetOwner() != (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		if (LineTrace() && bShouldCheckLineTrace) return;
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, FRotator(0,0,0));
		Projectile->Tags.Add("EnemyProjectile");
		Projectile->ProjectileType = EprojectileType::ENEMY_PROJECTILE;
		Projectile->SetOwner(this);
		Projectile->MaxProjectileRange = MaxProjectileRange;

		//Set the velocity assign velocity to projectile movement comp and then set the rotation of the projectile same as the gun rotation. 

		Projectile->ProjectileMovement->SetVelocityInLocalSpace(ProjectileVelocity);
		Hero->GetAngle(); //remove this line later

		Projectile->SetActorRotation(FRotator(0, 0, 0));
	}
}

//Extra shoot function for cool shootings including location and delay 4. copy
void AGunBase::Shoot(const FVector& ProjectileVelocity, const FVector& Location, float Delay, float CurrentProjectileCount, float NumberOfProjectiles)
{

	if (GetOwner() != (UGameplayStatics::GetPlayerPawn(GetWorld(),0)))
	{
		if (LineTrace() && bShouldCheckLineTrace) return;
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileType, Location, FRotator(0,0,0));
		Projectile->Tags.Add(Tags[0]);
		Projectile->ProjectileType = EprojectileType::ENEMY_PROJECTILE;
		Projectile->SetOwner(this);
		Projectile->MaxProjectileRange = MaxProjectileRange;

		//Initially, set the projectile's velocity to zero.
		Projectile->ProjectileMovement->SetVelocityInLocalSpace(FVector(0,0,0));
		Projectile->SetActorRotation(FRotator(0, 0, 0));
		bIsAttacking = false;
		Projectile->StoredVelocity = ProjectileVelocity;

		Projectiles.Add(Projectile);
		//Only set the timer if the current projectile count is last projectile
		if (CurrentProjectileCount -1 <= NumberOfProjectiles)
		{
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUObject(this, &AGunBase::ApplyVelocityToProjectile);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Delay, false);	
		}
	}
	
}

//Projectile velocity was 0 now it will be changed
void AGunBase::ApplyVelocityToProjectile()
{
	for (const auto Projectile : Projectiles)
	{
		if (Projectile != nullptr && Projectile->IsValidLowLevel())
		{
			bIsAttacking = true;
			Projectile->ProjectileMovement->SetVelocityInLocalSpace(Projectile->StoredVelocity);

		}
	}
	Projectiles.Empty();
}

bool AGunBase::LineTrace() const
{
	if (GetWorld())
	{
		FVector StartLocation = GetActorLocation();
		FVector EndLocation = GetActorLocation() + ArrowComponent->GetForwardVector() * 1000; 
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.bTraceComplex = true;
		TArray<FHitResult> HitResults;
        
		bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults,StartLocation,EndLocation,ECC_Visibility,Params);
		
		for (auto Hit : HitResults)
		{
			AActor* ActorHit = Hit.GetActor();

			if (ActorHit && ActorHit->ActorHasTag("Enemy"))
			{
				UE_LOG(LogTemp, Display, TEXT("TRUE"));

				return true;
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("FALSE"));
	return false;
}


// Called to bind functionality to input
void AGunBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

