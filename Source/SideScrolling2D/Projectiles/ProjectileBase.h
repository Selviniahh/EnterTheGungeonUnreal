// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UENUM(BlueprintType)
enum class EprojectileType : uint8
{
	PLAYER_PROJECTILE UMETA(DisplayName = "Player Projectile"),
	ENEMY_PROJECTILE UMETA(DisplayName = "Enemy Projectile")
};

UCLASS()
class SIDESCROLLING2D_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* FlipBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	class UPaperFlipbook* VerticalImpactFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	class UPaperFlipbook* HorizontalImpactFB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	class UPaperFlipbook* HitImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectile")
	EprojectileType ProjectileType = EprojectileType::ENEMY_PROJECTILE;

	float TravelledProjectileRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	float MaxProjectileRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	FVector StoredVelocity;
	FVector InitialLoc;

	//After traveled distance length > this value, it will be destroyed
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float LifeSpanDistance;

	

	

protected:
	UFUNCTION()
	virtual void OnFlipBookFinishedPlaying();
	void StopAndHit(AActor* OtherActor);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
