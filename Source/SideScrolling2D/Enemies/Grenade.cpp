

#include "Grenade.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "SideScrolling2D/Actor Components/HealthComponent.h"
#include "SideScrolling2D/Guns/GunBase.h"
#include "SideScrolling2D/Hero/Hero.h"


// Sets default values
AGrenade::AGrenade()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned

void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame

void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (Leap)
	{
		LeapToPlayer();
	}
	else if (FVector::Distance(Hero->GetActorLocation(), GetActorLocation()) < 75 && bDoOnce)
	{
		Leap = true;
	}
}

// Called to bind functionality to input

void AGrenade::JustPlayShootAnimation()
{
	
}

//I don't want it to move if it's leaping so if it's leaping it won't inherit anything. 

void AGrenade::Move()
{
	if (!Leap)
	{
		Super::Move();
	}
}

void AGrenade::LeapToPlayer()
{
	const int RandomValue = FMath::RandRange(0,150);

	//In order to avoid chasing, I got hero location once and used it 
	if (bDoOnceHeroLoc)
		InitialHeroLoc = Hero->GetActorLocation() + Gun->ArrowComponent->GetForwardVector() * RandomValue;
		bDoOnceHeroLoc = false;
	
	// FVector NewLocation = FMath::VInterpTo(GetActorLocation(), InitialHeroLoc, GetWorld()->GetDeltaSeconds(), InterpRate);

	LerpAlpha += GetWorld()->GetDeltaSeconds() / 9;
	if (LerpAlpha > 1.0f) LerpAlpha = 1.0f;
	
	SetActorLocation(FMath::LerpStable(GetActorLocation(),InitialHeroLoc,LerpAlpha));
	
	if (FVector::Distance(Hero->GetActorLocation(), GetActorLocation()) <= 1.0f)
	{
		Leap = false;
		bDoOnce = false;
		Explode = true;
	}
	
}

//Apply damage
void AGrenade::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBoxComponentBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	//Apply damage
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	auto MyOvnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10, MyOvnerInstigator, this, DamageTypeClass);
	}
}

void AGrenade::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

