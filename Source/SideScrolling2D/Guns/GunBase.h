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

	void Shoot();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UPaperZDAnimationComponent* PaperZDAnimation;

	//This property is more important than anything. IT'S WORTH to describe this in detail. I will have many guns and projectiles. So I need to know which projectile to spawn. This variable letting me
	//Expose a projectile class in BP. I choose the projectile I want for different Gun classes and it will use that projectile in C++ code. PERFECT. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileBase> ProjectileType;

	UPROPERTY()
	class AHero* Hero;

	float PressedTimer;
};