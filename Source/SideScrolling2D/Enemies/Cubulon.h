// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AngryBook.h"
#include "BulletMan.h"
#include "Cubulon.generated.h"

UCLASS()
class SIDESCROLLING2D_API ACubulon : public AAngryBook
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubulon();
	virtual void Shoot() override;
	virtual void StartShooting() override;

	//Maximum values
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RightUpProjectileCount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RightDownProjectileCount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LeftUpProjectileCount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LeftDownProjectileCount = 10;


	//Current values
	int CurrentRightUpProjectile;
	int CurrentRightDownProjectile;
	int CurrentLeftUpProjectile;
	int CurrentLeftDownProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cubulon Projectile")
	float ProjectileVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cubulon Projectile")
	float ProjectileOffset;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool ShouldProjectileMoveUp() const;

private:
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
