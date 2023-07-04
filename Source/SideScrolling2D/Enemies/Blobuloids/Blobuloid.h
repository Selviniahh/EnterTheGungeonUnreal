// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SideScrolling2D/Enemies/BulletMan.h"
#include "Blobuloid.generated.h"

UCLASS()
class SIDESCROLLING2D_API ABlobuloid : public ABulletMan
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlobuloid();

	virtual void JustPlayShootAnimation() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ABlobuloid> Blobuloid; 
	
	UPROPERTY(BlueprintReadWrite)
	bool CanSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector FirstSpawnLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector SecondSpawnLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
