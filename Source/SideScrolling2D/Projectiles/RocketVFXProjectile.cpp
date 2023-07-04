// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketVFXProjectile.h"
#include "SideScrolling2D/Hero/Hero.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARocketVFXProjectile::ARocketVFXProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARocketVFXProjectile::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));
	
}

// Called every frame
void ARocketVFXProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//KnockBack
	if (bShouldKnockBack && Hero)
	{
		const FVector NewLocation = (FMath::VInterpTo(Hero->GetActorLocation(), HeroTargetLocation, GetWorld()->GetDeltaSeconds(), KnockBackSpeed));
		Hero->SetActorLocation(NewLocation);
        
        //Making sure KnockBack is finished
        if (NewLocation.Equals(HeroTargetLocation,1.0f))
        {
        	bShouldKnockBack = false;
        }
	}
}

void ARocketVFXProjectile::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetOwner() != Hero) return;
}

void ARocketVFXProjectile::ApplyDamageKnockBack()
{
	//Apply damage
	const auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	const auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	const auto DamageTypeClass = UDamageType::StaticClass();

	if (Hero)
	{
		UGameplayStatics::ApplyDamage(Hero, Damage, MyOwnerInstigator, this, DamageTypeClass);
	}
	
	//KnockBack logic                     //projectile
	DeadDirection3D = GetActorLocation() - Hero->GetActorLocation();
	DeadDirection3D.Normalize();
	DeadDirection = FVector2D(DeadDirection3D.X, DeadDirection3D.Y);
	TargetLocation = GetActorLocation() + FVector(DeadDirection.X * KnockBackMultiply,DeadDirection.Y * KnockBackMultiply, 0);

	FVector HeroDeadDirection3D = Hero->GetActorLocation() - GetActorLocation();
	HeroDeadDirection3D.Normalize();
	FVector2D HeroDeadDirection = FVector2D(HeroDeadDirection3D.X, HeroDeadDirection3D.Y);
	//I multiplied by 2 because for hero it was too low 
	HeroTargetLocation = Hero->GetActorLocation() + FVector(HeroDeadDirection.X * KnockBackMultiply * 2,HeroDeadDirection.Y * KnockBackMultiply * 2, 0);
	bShouldKnockBack = true;
}
