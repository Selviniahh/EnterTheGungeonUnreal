// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLING2D_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Damaged;
	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 0.f;
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	float MaxHealth = 100.0f;
	

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
