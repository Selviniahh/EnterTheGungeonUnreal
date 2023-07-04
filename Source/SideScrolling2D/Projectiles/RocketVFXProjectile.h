// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "RocketVFXProjectile.generated.h"

UCLASS()
class SIDESCROLLING2D_API ARocketVFXProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARocketVFXProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ApplyDamageKnockBack();
	
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	FTimerHandle KnockBackTimerHandle;
	bool bShouldKnockBack;
	FVector TargetLocation;
	FVector2D DeadDirection;
	FVector DeadDirection3D;
	FVector HeroTargetLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	double KnockBackMultiply;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float KnockBackSpeed;

	UPROPERTY()
	class AHero* Hero;
};
