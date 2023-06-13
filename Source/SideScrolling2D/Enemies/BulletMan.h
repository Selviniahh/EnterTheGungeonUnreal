// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BulletMan.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLING2D_API ABulletMan : public AEnemyBase
{
	GENERATED_BODY()

public:
	ABulletMan();
	virtual void Tick(float DelatTime) override;
	void Move() override;

protected:
	virtual void BeginPlay() override;
};
