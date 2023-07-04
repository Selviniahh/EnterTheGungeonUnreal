// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMan.h"
#include "RubberBullet.generated.h"

UCLASS()
class SIDESCROLLING2D_API ARubberBullet : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARubberBullet();
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Discard this Function
	virtual void ShootProjectile() override;
	virtual void JustPlayShootAnimation() override;
	virtual void Move() override;
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle AttackTimerHandle;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;
	
	bool bAttackingFinished = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementDir")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementDir")
	float RunSpeed;

	UPROPERTY(BlueprintReadWrite)
	bool PlayCharge;

	UPROPERTY(BlueprintReadWrite)
	bool PlayImpact;

	UPROPERTY()
	AActor* OverlappedActor;
	FVector HeroTargetLocation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
