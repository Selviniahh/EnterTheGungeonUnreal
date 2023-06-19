// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrolling2D/Globals.h"
#include "EnemyBase.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* FlipBook;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* HandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* HandSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	class UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	class UPaperZDAnimationComponent* AnimComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	class UHealthComponent* HealthComponent;
	

	//Variables
	//Actual direction vector ranging from -1 to 1
	UPROPERTY(BlueprintReadWrite, Category="Direction")
	FVector2D EnemyDirectionVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 6))
	float KnockBackMultiply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 7))
	float KnockBackSpeed;
	
	bool bShouldKnockBack;

	//Functions
	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetEnemyDirectionEnum();
	virtual void Death();
	virtual void JustPlayShootAnimation();
	virtual void Move();

	
	//Properties
	UPROPERTY()
	class AHero* Hero;
	
	float DistanceBetweenHero;
	FVector EnemyLocation;
	float EnemyAngle;
	bool CanSetDirection = true;
	FVector DeadDirection3D;
	FVector TargetLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector2D DeadDirection;

	
	//Just for Movement normalized Direction not actual direction for animation
	UPROPERTY(BlueprintReadWrite)
	FVector2D EnemyMovementDirection;
	

	//Direction ranges (0-30, 30-65, 65-100, 100-150, 150-185, 185-240, 240-280, 280-320)
	TArray<FRanges> Ranges;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EDirections> CurrentDirection;

	TMap<EDirections,FVector2D> SetDirectionBasedOnEnum;


private:
	
};
