// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SideScrolling2D/Projectiles/ProjectileBase.h"

#include "GunBase.generated.h"


UCLASS()
class SIDESCROLLING2D_API AGunBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGunBase();
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* FlipBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHero* Hero;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UPaperFlipbookComponent* MuzzleFlash;


	//These Variables are the things that will be highly customizable for gun's behavior.
	UPROPERTY()
	float PressTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxProjectileRange;

	float TimerForVelocity;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UArrowComponent* ArrowComponent;

	FTimerHandle LineTraceTimer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bShouldCheckLineTrace = true;

	FName GunTagName; 

	
	


	//Normal shoot both for enemy and hero. Also base function for down two
	void Shoot();

	//This is initially designed for BulletManShotGun different direction shooting
	void Shoot(const FVector& ProjectileVelocity);

	//This is initially designed for BulletManShotGun death shooting when it's dead
	void Shoot(const FVector& ProjectileVelocity, const FVector& Location);

	//shoow with designated Velocity location delay and also validate if last projectile has been shoot
	void Shoot(const FVector& ProjectileVelocity, const FVector& Location, float Delay, float CurrentProjectileCount, float NumberOfProjectiles);

	UFUNCTION(BlueprintCallable)
	void ApplyVelocityToProjectile();

	bool LineTrace() const;

	UPROPERTY()
	TArray<AProjectileBase*> Projectiles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;


	FTimerHandle UnusedHandle;


	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UPaperZDAnimationComponent* PaperZDAnimation;

	//This property is more important than anything. IT'S WORTH to describe this in detail. I will have many guns and projectiles. So I need to know which projectile to spawn. This variable letting me
	//Expose a projectile class in BP. I choose the projectile I want for different EnemyGun classes and it will use that projectile in C++ code. PERFECT. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	TSubclassOf<AProjectileBase> ProjectileType;
	
};