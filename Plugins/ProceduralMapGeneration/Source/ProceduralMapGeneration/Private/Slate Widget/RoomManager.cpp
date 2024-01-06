// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate Widget/RoomManager.h"

#include "SlateMaterialBrush.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "ProceduralMapGeneration/Procedural Generation/Test/MakeAllCorridorScenarioTest.h"
#include "ProceduralMapGeneration/Procedural Generation/Test/ProGenWidgetTests.h"
#include "Slate Widget/GlobalInputListener.h"
#include "Slate Widget/PluginSettings.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRoomManager::Construct(const FArguments& InArgs)
{
	FirstRoom = InArgs._RoomFirst;
	SecondRoom = InArgs._RoomSecond;
	PluginSetting = GetDefault<UPluginSettings>();
	SceneCapInst = PluginSetting->SceneCapActorInst.Get();
	
	CorridorTest = NewObject<UMakeAllCorridorScenarioTest>(GetTransientPackage(), UMakeAllCorridorScenarioTest::StaticClass());
	AllTests = NewObject<UProGenWidgetTests>(GetTransientPackage(), UProGenWidgetTests::StaticClass());
	AllTests->Initialize(FirstRoom,SecondRoom);

	const UPluginSettings* Plugin = GetDefault<UPluginSettings>();

	if (UMaterialInterface* Material = Plugin->SceneCapMaterial.Get())
		SceneCapImgBrush = MakeShared<FSlateMaterialBrush>(*Material, FVector2D(100, 100)); // Initialize member variable

	FSlateFontInfo PropertyTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	PropertyTextFont.Size = 12;
	
	ButtonStyle = MakeShared<FButtonStyle>();
	ButtonStyle.Get()->SetNormal(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on
	ButtonStyle.Get()->SetHovered(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on
	ButtonStyle.Get()->SetPressed(FSlateColorBrush(FColor(0, 0, 0, 0))); //Make everything 0 later on

	ChildSlot
	[
		//Parent
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		[
			SNew(SHorizontalBox)

			//1. Slot
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			  .FillWidth(1.0)
			[
				SNew(SImage)
				.Image(SceneCapImgBrush.Get()) // Initialize member variable)
			]

			+ SHorizontalBox::Slot()
			[
				SNew(SVerticalBox)

				//2. slot
				+ SVerticalBox::Slot()
				  .HAlign(HAlign_Fill)
				  .VAlign(VAlign_Fill)
				  .AutoHeight()
				  .Padding(FMargin(10,0,0,0))
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					  .AutoWidth()
					  .VAlign(VAlign_Center)
					  .HAlign(HAlign_Center)
					[
						ConstructTextBlock(PropertyTextFont, FText::FromString("Make Overlap Check"))
					]

					+ SHorizontalBox::Slot()
						  .AutoWidth()
						  .VAlign(VAlign_Center)
						  .HAlign(HAlign_Center)
						  .Padding(FMargin(10,0,0,0))
					[
					SNew(SButton)
						.OnClicked(this, &SRoomManager::OnButtonClicked)
						.OnHovered(this, &SRoomManager::OnHovered)
						.OnUnhovered(this, &SRoomManager::OnUnHovered)
						.Text(FText::FromString(TEXT("Make Test")))
					]
				]
			]
		]
	];
}

TSharedRef<STextBlock> SRoomManager::ConstructTextBlock(FSlateFontInfo FontInfo, FText Text)
{
	TextBlock = SNew(STextBlock)
	   .Justification(ETextJustify::Center)
	   .Text(Text)
	   .Font(FontInfo)
	   .RenderOpacity(0.5);

	return TextBlock.ToSharedRef();
}

FReply SRoomManager::OnButtonClicked()
{
	AllTests->MakeOverlapTest();
	return FReply::Handled();
}

void SRoomManager::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	TMap<FKey, bool> KeyMap = FMyInputProcessor::KeyPressedMap;
	FKey MyKey = FMyInputProcessor::PressedKey;
	FVector Direction = FVector::ZeroVector;

	if (KeyMap[EKeys::A] && KeyMap[EKeys::D])
	{
		UE_LOG(LogTemp, Display, TEXT("A pressed"));

	}
	
	//Simulate actual add input movement as much as possible
	if (FMyInputProcessor::KeyPressedMap.Contains(MyKey))
	{
		if		(KeyMap[EKeys::A]) Direction = FVector(-1, 0, 0);
		else if (KeyMap[EKeys::D]) Direction = FVector(1, 0, 0);
		else if (KeyMap[EKeys::W]) Direction = FVector(0, -1, 0);
		else if (KeyMap[EKeys::S]) Direction = FVector(0, 1, 0);
		else if (KeyMap[EKeys::Q]) Direction = FVector(0, 0, -1);
		else if (KeyMap[EKeys::E]) Direction = FVector(0, 0, 1);
		
		// Check for specific diagonal combinations
		if (KeyMap[EKeys::A] && KeyMap[EKeys::W]) Direction = FVector(-1, -1, 0).GetSafeNormal();
		if (KeyMap[EKeys::W] && KeyMap[EKeys::D]) Direction = FVector(1, -1, 0).GetSafeNormal();
		if (KeyMap[EKeys::A] && KeyMap[EKeys::S]) Direction = FVector(-1, 1, 0).GetSafeNormal();
		if (KeyMap[EKeys::D] && KeyMap[EKeys::S]) Direction = FVector(1, 1, 0).GetSafeNormal();

		
	}

	if (SceneCapInst)
	{
		float AccelerationSpeed = 2000.0f;
		FVector TargetVelocity = Direction * AccelerationSpeed;
		// Smoothly interpolate to the target velocity
		CurrentVelocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, InDeltaTime, 10.0f);

		// Apply the current velocity to update position
		FVector NewLocation = SceneCapInst->GetActorLocation() + CurrentVelocity * InDeltaTime;
		SceneCapInst->SetActorLocation(NewLocation);
	}

	
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

#pragma region OverlapVisual

void SRoomManager::OnHovered()
{
	TextBlock.Get()->SetRenderOpacity(1);
}

void SRoomManager::OnUnHovered()
{
	TextBlock.Get()->SetRenderOpacity(0.5);
}

void SRoomManager::OnPressed()
{
	TextBlock.Get()->SetRenderOpacity(1);
}
#pragma endregion


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
