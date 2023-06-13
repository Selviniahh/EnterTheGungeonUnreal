// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletMan.h"

ABulletMan::ABulletMan()
{
		
}

void ABulletMan::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
	Move();	
}

void ABulletMan::Move()
{
	Super::Move();
	EnemyMovementDirection = Player->GetActorLocation() - GetActorLocation();
	EnemyMovementDirection.Normalize();
	if (DistanceBetweenHero > 50)
	{
		MovementComponent->AddInputVector(EnemyMovementDirection);	
	}
}

void ABulletMan::BeginPlay()
{
	Super::BeginPlay();
	
}

