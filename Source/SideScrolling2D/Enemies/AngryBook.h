// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMan.h"
#include "SideScrolling2D/Globals.h"
#include "AngryBook.generated.h"



UCLASS()
class SIDESCROLLING2D_API AAngryBook : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAngryBook();
	virtual void ShootProjectile() override;

	virtual void Shoot();
	virtual void StartShooting();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ArrowComponent;

	//Current Projectile count that will increment each shoot
	int CurrentProjectileCount;

	//This is the Projectile that will be used for up an down directions. In short Special and different then above one
	int CurrentSpecialProjectileCount;

	//For RootArrow Y axis
	int RootYNeg;
	int RootYPos;
	
	FTimerHandle ShootTimer;
	FTimerHandle ShootingSequenceTimer;

	UPROPERTY(BlueprintReadWrite)
	bool PlayCharge;

	//if ShootRate < ChargeTime, PlayCharge = true
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxWalkSpeed;

	UPROPERTY()
	TEnumAsByte<EDirections> CurrentDirectionBeforeShoot;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	int NumberOfProjectiles;

	//Special one that will be used for up and down directions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	int NumberOfSpecialProjectiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float AngleBetweenProjectiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float ProjectileVelocity2;

	//Rate at spawning projectile 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float ProjectileSpawnRate = 0.05;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float Delay;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCharging;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;

	float AttackTimer;
	
	FVector GunProjectileVelocity;
	FVector EmptyProjectileVelocity = FVector(0,0,0);

	//How often it should start to generate all the projectiles in 0.05 second. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootRate;

	//Put the class name here 
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName GunTagName;
	
	bool DoOnce;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
