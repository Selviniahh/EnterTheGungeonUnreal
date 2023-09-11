// Fill out your copyright notice in the Description page of Project Settings.


#include "RelativeIndexWidget.h"

#include "LevelEditorViewport.h"
#include "ScopedTransaction.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void URelativeIndexWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GenerateRandom();
	GenerateButton->OnClicked.AddUniqueDynamic(this, &URelativeIndexWidget::OnGenerateButtonClicked);
}

void URelativeIndexWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}




void URelativeIndexWidget::GenerateRandom()
{
	int32 RandomNumber = FMath::RandRange(0, 100);
	RandomNumberLabel->SetText(FText::AsNumber(RandomNumber));
}

void URelativeIndexWidget::OnGenerateButtonClicked()
{
	GenerateRandom();
}