// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BulletMan.generated.h"

class AGunBase;
/**
 * 
 */
UCLASS()
class SIDESCROLLING2D_API ABulletMan : public AEnemyBase
{
	GENERATED_BODY()

public:
	ABulletMan();
	virtual void Tick(float DelatTime) override;
	void Move() override;
	virtual void JustPlayShootAnimation() override;
	virtual void ShootProjectile();


	//Follow the player until there's a this distance between player and enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Default Values", meta=(DisplayPriority = 2))
	float MoveRange; 
	
	FTimerHandle FireTimerHandle;
	FTimerHandle PlayAnimationTimerHandle;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsShooting;

	//How fast or slow the gun should shoot
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 4))
	float FireRate;

	//Make sure that enemy can shoot in enough distance
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 3))
	float DistanceCannotShoot;

	//To be able to easily play shoot animation before shooting projectile. Calculate shoot animation length and then set float value to here 
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 5))
	float ShootAnimationLength;

	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 1))
	TSubclassOf<AGunBase> EnemyGun;

	UPROPERTY()
	AGunBase* MagnumGun;
};
