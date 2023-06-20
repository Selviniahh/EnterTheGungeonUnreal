// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	FlipBook = CreateDefaultSubobject<UPaperFlipbookComponent>("FlipBook");
	FlipBook->SetupAttachment(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(FlipBook);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	MaxProjectileRange = 700;
}

// Called when the game starts or when spawned

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Projectile");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AProjectileBase::OnBoxComponentBeginOverlap);
	FlipBook->OnFinishedPlaying.AddDynamic(this, &AProjectileBase::OnFlipBookFinishedPlaying);
	
}

void AProjectileBase::OnFlipBookFinishedPlaying()
{
	Destroy();
}

void AProjectileBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//For Projectiles fired by enemies 
	if (ProjectileType == EprojectileType::ENEMY_PROJECTILE)
	{
		//if projectile fired by enemy hit the player
		if (OtherActor->ActorHasTag("Enemy"))
		{
			// UE_LOG(LogTemp, Display, TEXT("This is Enemy shooting itself: "));
			return;
			//Don't do anything
		}
		
		if (OtherActor->ActorHasTag("Hero"))
		{
			// UE_LOG(LogTemp, Display, TEXT("This is Enemy projectile: "));
			StopAndHit(OtherActor);
		}

		//if projectile fired by enemy hit himself
	}

	//This is projectile that player is shooting
	else if (ProjectileType == EprojectileType::PLAYER_PROJECTILE)
	{
		//DO something when the projectile Hits an enemy
		if (OtherActor->ActorHasTag("Enemy"))
		{
			// UE_LOG(LogTemp, Display, TEXT("This is player projectile: %s "), *OtherActor->GetName());
			StopAndHit(OtherActor);
		}
	}
}

void AProjectileBase::StopAndHit(AActor* OtherActor)
{
	//Stop the projectile and play the hit animation
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0,0,0));
	FlipBook->SetFlipbook(HitImpact);
	FlipBook->SetLooping(false);

	//Apply damage
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	auto MyOvnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOvnerInstigator, this, DamageTypeClass);
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, -240));
	TravelledProjectileRange = ProjectileMovement->Velocity.Length();


	if (TravelledProjectileRange > MaxProjectileRange)
	{
		// ProjectileMovement->SetVelocityInLocalSpace(FVector(0,0,0));
		FlipBook->SetFlipbook(HitImpact);
		FlipBook->SetLooping(false);
		ProjectileMovement->SetVelocityInLocalSpace(FVector(0,0,0));

	}
	Super::Tick(DeltaTime);
}

