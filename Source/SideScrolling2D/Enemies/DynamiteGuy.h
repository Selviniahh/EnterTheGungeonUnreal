// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMan.h"
#include "DynamiteGuy.generated.h"

UCLASS()
class SIDESCROLLING2D_API ADynamiteGuy : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADynamiteGuy();
	void Attack();
	void ExplodeAndDie();


	//Properties
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle AttackTimer;
	FTimerHandle DeathTimer;
	int OffsetMultiplyer;

	UPROPERTY(BlueprintReadWrite)
	bool CanExplode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
