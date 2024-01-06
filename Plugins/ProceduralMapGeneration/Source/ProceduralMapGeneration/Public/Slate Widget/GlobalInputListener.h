#pragma once
#include "Framework/Application/IInputProcessor.h"
class FMyInputProcessor : public IInputProcessor
{
public:
	inline static FKey PressedKey = FKey();
	inline static FKey PressedMouseKey = FKey();
	static TMap<FKey, bool> KeyPressedMap;

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;
	virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

	static bool IsKeyPressed(const FKey& Key);
	static void FillMap();
};
