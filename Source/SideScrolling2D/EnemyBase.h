// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyBase.generated.h"

//This struct is used to define the range of direction angles.
USTRUCT(BlueprintType)
struct FDirectionRange
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Range")
	float Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Range")
	float Max; 
};

UENUM()
enum EEnemyDirectionEnum
{
	Right, //0-30
	Front_Right, //30-65
	Front, //65-100
	Front_Left, //100-150
	Left, //160-185
	Back_Left, //185-240
	Back, //240-280
	Back_Right, //280-320
	Right2, //320-360
};

UCLASS()
class SIDESCROLLING2D_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DelatTime) override;

protected:
	virtual void BeginPlay() override;
	
	virtual void RotateEnemy(FVector Threshold);
	virtual void Death();
	virtual void Fire();
	virtual void Move();

	UPROPERTY()
	APaperZDCharacter* Player;
	
	float DistanceBetweenHero;
	FVector EnemyLocation;
	float EnemyAngle;
	
	//Just for Movement normalized Direction not actual direction for animation
	FVector EnemyMovementDirection;
	

	//Direction ranges (0-30, 30-65, 65-100, 100-150, 150-185, 185-240, 240-280, 280-320)
	UPROPERTY()
	TArray<FDirectionRange> DirectionRanges;

	TEnumAsByte<EEnemyDirectionEnum> EnemyDirectionEnum;

	TMap<EEnemyDirectionEnum, FVector2D> DirectionVectors;
	//Dictionary of direction vectors to assign current direction (-1 to 1)
	
	//Actual direction vector ranging from -1 to 1
	UPROPERTY(BlueprintReadWrite, Category="Direction")
	FVector2D EnemyDirectionVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement")
	UPaperZDAnimationComponent* AnimComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	UFloatingPawnMovement* MovementComponent;


private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* FlipBook;
};
