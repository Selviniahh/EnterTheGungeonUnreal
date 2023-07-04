// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMan.h"
#include "Grenade.generated.h"

UCLASS()
class SIDESCROLLING2D_API AGrenade : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGrenade();
	virtual void JustPlayShootAnimation() override;
	virtual void Move() override;
	void LeapToPlayer();
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(BlueprintReadWrite)
	bool Leap;

	UPROPERTY(BlueprintReadWrite)
	bool Explode;

	bool bDoOnce = true;
	bool bDoOnceHeroLoc = true;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialHeroLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterpRate;

	float LerpAlpha;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
