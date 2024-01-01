// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class ARoomActor;
/**
 * 
 */
class PROCEDURALMAPGENERATION_API SRoomManager : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRoomManager)
		{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
