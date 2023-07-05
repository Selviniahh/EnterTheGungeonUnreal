// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrolling2D/Globals.h"
#include "EnemyBase.generated.h"

class AGunBase;
struct FRanges;

UCLASS()
class SIDESCROLLING2D_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DelatTime) override;



protected:
	virtual void BeginPlay() override;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementDir")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* FlipBook;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* HandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* HandSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementDir")
	class UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MovementDir")
	class UPaperZDAnimationComponent* AnimComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementDir")
	class UHealthComponent* HealthComponent;

	
	

	//Functions
	UFUNCTION()
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetEnemyDirectionEnum();
	virtual void Death();
	virtual void JustPlayShootAnimation();
	virtual void Move();
	
	//Variables
	//Actual direction vector ranging from -1 to 1

	//EnemyGun
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 1))
	TSubclassOf<AGunBase> EnemyGun;

	UPROPERTY()
	class AHero* Hero;
	
	//Knockbacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 8))
	float KnockBackMultiply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 7))
	float KnockBackSpeed;
	
	bool bShouldKnockBack;
	bool bCanSetDirectionAndFlip = true;
	
	float DistanceBetweenHero;
	FVector EnemyLocation;
	float EnemyAngle;
	bool CanSetDirection = true;
	FVector DeadDirection3D;
	FVector EnemyTargetLocation;

	//When Dead play animation based on this direction
	UPROPERTY(BlueprintReadWrite)
	FVector2D DeadDirection;

	//Spawn bool to not let it move when spawning
	UPROPERTY(BlueprintReadWrite)
	bool Spawning; 

	
	//Direction ranges struct (0-30, 30-65, 65-100, 100-150, 150-185, 185-240, 240-280, 280-320)
	TArray<FRanges> Ranges;

	//Enum itself
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EDirections> CurrentDirection;

	//Dictionary for setting direction based on enum
	TMap<EDirections,FVector2D> SetDirectionBasedOnEnum;

	//Just for MovementDir normalized Direction not actual direction for animation
	UPROPERTY(BlueprintReadWrite)
	FVector2D EnemyMovementDirection;

	//Actual Direction Vector2D
	UPROPERTY(BlueprintReadWrite, Category="Direction")
	FVector2D EnemyDirectionVector;

	//Flipping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flipping", meta=(DisplayPriority = 1))
	FVector2D HandCompLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flipping", meta=(DisplayPriority = 2)) 
	FVector2D HandCompLocFlip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flipping", meta=(DisplayPriority = 2)) 
	FVector GunScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flipping", meta=(DisplayPriority = 2)) 
	FVector AfterAttachRelativeLoc; //0,-1,-1

	
	//Cooldown duration when shoots left == 0
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 6))
	float CooldownTimer;

	float CooldownTime;



private:
	
};