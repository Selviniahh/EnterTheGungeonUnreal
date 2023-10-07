// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"


class ADoorActor;
class UBoxComponent;
class UPaperTileMap;

UCLASS()
class SIDESCROLLING2D_API ARoomActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomActor();
	bool CheckFirstTagValid(USceneComponent* SceneComp) const;

	UPROPERTY()
	int PathCost = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ADoorActor> EnterDoor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ADoorActor> ExitDoor;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* RootScene;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* DoorSocketEnter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* DoorSocketExit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FIntPoint PathStartOffset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FIntPoint PathEndOffset;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	TArray<FIntPoint> EnterExclusions;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	TArray<FIntPoint> ExitExclusions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	TArray<FIntPoint> ExitSocketChecks;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Exclusions")
	FIntPoint ExitSocketCheckOffset;
	
	TArray<FString> ValidTags;
	mutable TWeakObjectPtr<UActorComponent> LastWarnedComponent;

	//Just will be used with Branch Connection
	bool IsOverlapped;
	
	// virtual bool CanEditChange(const FEditPropertyChain& PropertyChain) const override;
	// virtual bool CanEditChange(const FProperty* InProperty) const override;
	virtual bool CanEditChangeComponent(const UActorComponent* Component, const FProperty* InProperty) const override;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UPaperTileMapComponent* TileMapComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
