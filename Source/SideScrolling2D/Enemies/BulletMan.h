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
	virtual void BeginPlay() override;
	virtual void Tick(float DelatTime) override;
	void Move() override;
	virtual void JustPlayShootAnimation() override;
	virtual void ShootProjectile();
	virtual void CooldownFinished();


	//Follow the player until there's a this distance between player and enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Default Values", meta=(DisplayPriority = 2))
	float MoveRange; 

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle FireTimerHandle;

	//This can be used for charge animation duration
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle PlayAnimationTimerHandle;
	
	FVector MovementDir;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsShooting;

	UPROPERTY(BlueprintReadWrite)
	bool CanCharge;

	//Make sure that enemy can shoot in enough distance
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 3))
	float DistanceCannotShoot;

	//First play shoot gun animation and then shoot. Also it's cooldown for each shoot until ShootsLeft == 0
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 4))
	float ChargeShootAnimationLength;

	//The maximum number of shoots enemy can. After this over, enemy will have cooldown. It will shoot repetitively as ChargeShootAnimationLength 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 5))
	int ShootsLeft;

	 

	int MaxShoots;

	

	

protected:
	
	//Gun itself
	UPROPERTY()
	AGunBase* Gun;

	//Created to let manual shooting for subclasses. If you want to make enemy shoot manually, set this to false
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 10))
	bool ShouldBaseClassShoot = true;
};
