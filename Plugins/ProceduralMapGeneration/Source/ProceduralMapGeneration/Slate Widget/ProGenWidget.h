#pragma once

#include "CoreMinimal.h"
#include "SlateMaterialBrush.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PROCEDURALMAPGENERATION_API SProGenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SProGenWidget)
		{}
	
	SLATE_ARGUMENT(UMaterialInterface*, Material)
	SLATE_ARGUMENT(AActor*, SceneCapActor)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	FReply OnButtonClicked();
	TSharedRef<SHorizontalBox> ConstructTextInput(const FText& Text, const FText& HintText, const FSlateFontInfo& PropertyTextFont, const FOnTextChanged& OnTextChangedDelegate);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	TSharedPtr<FSlateMaterialBrush> MaterialBrush; // Member variable
	void OnMultiplyerChange(const FText& Text);
	void OnInterpSpeedChange(const FText& Text);
		
	AActor* SceneCapActor;
	int Multiplayer = 444;
	int InterpSpeed = 444;
private:
};
