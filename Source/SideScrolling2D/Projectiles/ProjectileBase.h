// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

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

	float TravelledProjectileRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Projectiles")
	float MaxProjectileRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage; 

protected:
	UFUNCTION()
	void OnFlipBookFinishedPlaying();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
