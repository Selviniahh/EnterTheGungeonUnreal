// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RenderTarget.generated.h"

UCLASS()
class PROCEDURALMAPGENERATION_API ARenderTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARenderTarget();

	UPROPERTY()
	USceneCaptureComponent2D* SceneCaptureComponent2D;

	 UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
