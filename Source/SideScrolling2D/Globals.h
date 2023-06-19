// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

UENUM()
enum EDirections : uint8
{
	//No hand directions specified you'll switch hands when angle is > or < something. 
	Right,
	Front_Hand_Right,
	Front_Hand_Left,
	Left,
	Back_Diagonal_Left,
	Back_Hand_Left,
	Back_Hand_Right,
	Back_Diagonal_Right,
};

#include "Globals.generated.h"

USTRUCT()
struct FRanges
{
	GENERATED_BODY()
	float Min;
	float Max;

	FRanges() : Min(0), Max(0)  // default constructor
	{}

	FRanges(float MinVal, float MaxVal) : Min(MinVal), Max(MaxVal)  // custom constructor that takes two arguments
	{}
	
};
UCLASS()
class SIDESCROLLING2D_API AGlobals : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGlobals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
