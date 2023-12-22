// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h" // For GetTypeHash
#include "Containers/ContainerAllocationPolicies.h" // For HashCombine
#include "Misc/Crc.h"
#include "EnemyBase.generated.h"


class AGunBase;

USTRUCT()
struct FRanges
{
	GENERATED_BODY()
	float Min;
	float Max;

	FRanges() : Min(0), Max(0)  {} // default constructor
	FRanges(const float MinVal, const float MaxVal) : Min(MinVal), Max(MaxVal) {} // custom constructor that takes two arguments
};

USTRUCT()
struct FMovementNode
{
	GENERATED_BODY();
	float X;
	float Y;
	TSharedPtr<FMovementNode> Parent;

	//A* implementation
	int Hcost;
	int GCost;
	int FCost() { return Hcost + GCost; }
	int TileSize; 
	FVector Location;

	static float GetHCost(float x1, float y1, float x2, float y2)
	{
		return FMath::Sqrt(FMath::Square((float)(x1 - x2)) + FMath::Square((float)(y1 - y2)));
	}
	
	FMovementNode(int X, int Y): Parent(nullptr), Hcost(0), GCost(0), TileSize(16)
	{
		this->X = X;
		this->Y = Y;
		Location = FVector(X * TileSize, Y * TileSize,0); 
	}

	//Default constructor
	FMovementNode() : X(0), Y(0), Parent(nullptr), Hcost(0), GCost(0), TileSize(16)
	{
		Location = FVector(X * TileSize, Y * TileSize,0); 
	}
};

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

UCLASS()
class SIDESCROLLING2D_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MovementDir")
	class UHealthComponent* HealthComponent;
	float Timer;
	float SecTimer;

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

	//EnemyGun
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 1))
	TSubclassOf<AGunBase> EnemyGun;
	
	//Knockbacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 8))
	float KnockBackMultiply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default Values", meta=(DisplayPriority = 7))
	float KnockBackSpeed;

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

	UPROPERTY(BlueprintReadWrite)
	FVector MovementDir;

	//Follow the player until there's a this distance between player and enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Default Values", meta=(DisplayPriority = 2))
	float MoveRange;

	UPROPERTY()
	AGunBase* Gun;


	UPROPERTY()
	class AHero* Hero;
	
	//Spawn bool to not let it move when spawning
	UPROPERTY(BlueprintReadWrite)
	bool Spawning;

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
	
	float CooldownTime;
	
	TArray<FVector> CurrentPath;
	int CurrentTargetIndex;
	float PathUpdateTimer;
	FVector TargetLoc;

	
	static TArray<FMovementNode> NodeMap;
	// inline static TArray<int> Row = { -1, 1, 0, 0 };  // Up, Down, Left, Right
	// inline static TArray<int> Col = { 0, 0, -1, 1 };  // Up, Down, Left, Right

	// 8 directions: Up, Down, Left, Right, Up-Left, Up-Right, Down-Left, Down-Right
	inline static TArray<int> Row = { -1, 1, 0, 0, -1, -1, 1, 1 };
	inline static TArray<int> Col = { 0, 0, -1, 1, -1, 1, -1, 1 };

	
	int TileSizeX = 16;
	int TileSizeY = 16;
	
	bool TestOnce = true;
	FVector MovDirection;
	FVector FirstLoc;

	TArray<FVector> FoundPath;
	int32 CurrentPathIndex;
	FVector BoxExtend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PathFinding")
	int MaxIterationAmount =  100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "PathFinding")
	int PathTileBuffer = 3;


	
	inline FVector2D WorldToIndex(FVector WorldLocation)
	{
		int TileX = FMath::RoundToInt(WorldLocation.X / TileSizeX);
		int TileY = FMath::RoundToInt(WorldLocation.Y / TileSizeY);
		
		return FVector2D(TileX,TileY);
	}

	/*Convert given world position to relative index points */
	inline FVector IndexToWorld(int X, int Y)
	{
		return FVector(X * TileSizeX, Y * TileSizeY, 0);
	}

	bool IsWalkable(int X, int Y);
	
	UFUNCTION()
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetEnemyDirectionEnum();
	virtual void Death();
	virtual void JustPlayShootAnimation();
	TArray<FVector> PathFinding();
	virtual void Move();
	bool Contains(TArray<TSharedPtr<FMovementNode>> VisitedNodes, TSharedPtr<FMovementNode> Neighbour);
	void MoveAlongPath(float DeltaTime);


private:
	
};
