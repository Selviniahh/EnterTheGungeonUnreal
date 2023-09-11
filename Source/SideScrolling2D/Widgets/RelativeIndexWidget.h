// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RelativeIndexWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLING2D_API URelativeIndexWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void GenerateRandom();
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* RandomNumberLabel;

	UPROPERTY(meta=(BindWidget))
	class UButton* GenerateButton;

	UFUNCTION()
	void OnGenerateButtonClicked();
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	bool IsPressed(FKey Key) const;
};
