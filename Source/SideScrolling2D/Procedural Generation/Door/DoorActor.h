// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;

UCLASS()
class SIDESCROLLING2D_API ADoorActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* RootComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbookComponent* DoorFBRight;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbookComponent* DoorFBLeft;	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
