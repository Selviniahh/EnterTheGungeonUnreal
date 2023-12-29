// Fill out your copyright notice in the Description page of Project Settings.


#include "ProGenWidget.h"
#include "GlobalInputListener.h"
#include "SlateOptMacros.h"
#include "Materials/MaterialInterface.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SProGenWidget::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	FSlateApplication::Get().SetKeyboardFocus(SharedThis(this), EFocusCause::SetDirectly);

	if (UMaterialInterface* Material = InArgs._Material)
	{
		MaterialBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable
	}

	SceneCapActor = InArgs._SceneCapActor;

	FSlateFontInfo TitleTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 30;

	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 12;

	ChildSlot
[
	// Top-Level Vertical Box
	SNew(SVerticalBox)

	// TextBlock Slot
	+ SVerticalBox::Slot()
	.AutoHeight() // Adjust as needed for your text size
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.Padding(FMargin(0, 10, 0, 15))
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("Procedural Map Generation")))
		.Justification(ETextJustify::Center)
		.Font(TitleTextFont) // Set font size to 24 and use bold weight
		
	]

	// HorizontalBox Slot
	+ SVerticalBox::Slot()
	.FillHeight(1) // Takes remaining space
	[
		SNew(SHorizontalBox)

		// Left Section (VerticalBox with Image)
		+ SHorizontalBox::Slot()
		.FillWidth(0.5) // Adjust width ratio as needed
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1)
			[
				SNew(SImage)
				.Image(MaterialBrush.Get())
			]
		]

		// Right Section (VerticalBox with TextBlocks and TextBoxes)
		+ SHorizontalBox::Slot()
		.FillWidth(0.5) // Adjust width ratio as needed
		[
			SNew(SVerticalBox)
		
			// Multiplyer text change box
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				ConstructTextInput(FText::FromString("Multiplyer"), FText::FromString(FString::FromInt(Multiplayer)), PropertyTextFont, FOnTextChanged::CreateSP(this, &SProGenWidget::OnMultiplyerChange))
			]
		
			// InterpSpeed text change box
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				ConstructTextInput(FText::FromString("Interp Speed"), FText::FromString(FString::FromInt(InterpSpeed)), PropertyTextFont, FOnTextChanged::CreateSP(this, &SProGenWidget::OnInterpSpeedChange))
			]
		]
	]
];
	
}

TSharedRef<SHorizontalBox> SProGenWidget::ConstructTextInput(const FText& Text, const FText& HintText, const FSlateFontInfo& PropertyTextFont, const FOnTextChanged& OnTextChangedDelegate)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .HAlign(HAlign_Center)
			.Padding(FMargin(15, 0, 15, 0))
		[
			SNew(STextBlock)
					.Text(Text)
					.Font(PropertyTextFont)
		]

		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .HAlign(HAlign_Center)
		[
			SNew(SEditableTextBox)
					.Font(PropertyTextFont)
					.HintText(HintText)
					.OnTextChanged(OnTextChangedDelegate)
		];
}

void SProGenWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	FKey MyKey = FMyInputProcessor::PressedKey;
	
	FVector Direction = FVector::ZeroVector;
	if		(MyKey == EKeys::W) Direction = FVector(Multiplayer, 0, 0);
	else if (MyKey == EKeys::S) Direction = FVector(-Multiplayer, 0, 0);
	else if (MyKey == EKeys::A) Direction = FVector(0, -Multiplayer, 0);
	else if (MyKey == EKeys::D) Direction = FVector(0, Multiplayer, 0);
	else if (MyKey == EKeys::Q) Direction = FVector(0, 0, -Multiplayer);
	else if (MyKey == EKeys::E) Direction = FVector(0, 0, Multiplayer);

	if (SceneCapActor && Direction != FVector::ZeroVector)
	{
		FVector CurrentLocation = SceneCapActor->GetActorLocation();
		FVector TargetLocation = CurrentLocation + Direction;
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, InDeltaTime, 99); // InterpSpeed is a float determining how fast to move
		SceneCapActor->SetActorLocation(NewLocation, true);
	}
	
	FMyInputProcessor::PressedKey = FKey();
}

void SProGenWidget::OnMultiplyerChange(const FText& Text)
{
	Multiplayer = FCString::Atoi(*Text.ToString());
}

void SProGenWidget::OnInterpSpeedChange(const FText& Text)
{
	InterpSpeed = FCString::Atoi(*Text.ToString());
}

FReply SProGenWidget::OnButtonClicked()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
