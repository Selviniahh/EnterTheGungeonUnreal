// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMan.h"
#include "BulletManShotGun.generated.h"

UCLASS()
class SIDESCROLLING2D_API ABulletManShotGun : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABulletManShotGun();
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void ShootProjectile() override;

	void ShootAfterDeath() const;

	//Run ShootAfterDeath just for once 
	bool ShootAfterDeathOnce = true;
	float ShootAfterDeathOnceTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Death")
	float AngleDeathProjectile; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
