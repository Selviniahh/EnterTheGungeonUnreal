#pragma once
#include "Framework/Application/IInputProcessor.h"
class FMyInputProcessor : public IInputProcessor
{
public:
	inline static FKey PressedKey = FKey();
	inline static FKey PressedMouseKey = FKey();
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;
	
};
