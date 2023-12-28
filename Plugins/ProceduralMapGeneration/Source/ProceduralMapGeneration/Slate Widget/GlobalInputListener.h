#pragma once
#include "Framework/Application/IInputProcessor.h"
class FMyInputProcessor : public IInputProcessor
{
public:
	inline static FKey PressedKey = FKey();
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
	
};
