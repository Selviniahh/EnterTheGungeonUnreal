// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "SideScrolling2D/Globals.h"
#include "Hero.generated.h"

UCLASS()
class SIDESCROLLING2D_API AHero : public APawn
{
	GENERATED_BODY()

public:
	AHero();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsShooting;

	UPROPERTY(BlueprintReadWrite)
	bool IsDashingCpp = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseAngle;

protected:
	virtual void BeginPlay() override;
	void FlipComponents();
	void Dash(float DeltaTime);
	void GetAngle();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* FlipBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperZDAnimationComponent* HeroAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperFlipbookComponent* HandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* HandSocket;


	//Input mapping and other stuff
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ShootAction;

	void Move(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void SetShootFalse(const FInputActionValue& Value);

	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetMouseDirectionEnum();


	//Properties
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MouseDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EDirections> CurrentDirection;

	TArray<FRanges> Ranges;

	TMap<EDirections,FVector2D> SetDirectionBasedOnEnum;
	
	float LastMouseX, LastMouseY;
	float DashTimer;

	
	
	bool StartDashTimer = false;

	UPROPERTY(BlueprintReadWrite)
	class AGunBase* Gun = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MoveDirection; 
};
