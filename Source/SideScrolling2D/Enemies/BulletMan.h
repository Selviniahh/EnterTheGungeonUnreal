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
	
	UFUNCTION(BlueprintCallable)
	bool BoxTraceForSlowDown();

	bool BoxTraceForStop();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DelatTime) override;
	void Move() override;
	virtual void JustPlayShootAnimation() override;
	virtual void ShootProjectile();
	virtual void CooldownFinished();


	 

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle FireTimerHandle;

	//This can be used for charge animation duration
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle PlayAnimationTimerHandle;

	


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

	//For Slowing Down
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForSlowDown", meta=(DisplayPriority = 1))
	float LineTraceStartLength;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForSlowDown", meta=(DisplayPriority = 2))
	float LineTraceLength;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForSlowDown", meta=(DisplayPriority = 3))
	FVector BoxHalfSizeSlow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForSlowDown", meta=(DisplayPriority = 4))
	FColor Color;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForSlowDown", meta=(DisplayPriority = 5))
	bool ShouldDrawDebugBox;

	
	//For Stopping
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForStop", meta=(DisplayPriority = 1))
	float BoxTraceStartLength;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForStop", meta=(DisplayPriority = 2))
	float BoxTraceLength;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForStop", meta=(DisplayPriority = 3))
	FVector BoxHalfSizeStop;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "BoxTraceForStop", meta=(DisplayPriority = 4))
	bool ShouldDrawDebugBoxStop;

	
	int MaxShoots;
	int InitialMovSpeed;
	bool SlowedDownOnce;

protected:
	
	

	//Created to let manual shooting for subclasses. If you want to make enemy shoot manually, set this to false
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 10))
	bool ShouldBaseClassShoot = true;
};
