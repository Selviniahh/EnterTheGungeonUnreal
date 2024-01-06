#include "ProceduralMapGeneration/Public/Slate Widget/GlobalInputListener.h"

TMap<FKey, bool> FMyInputProcessor::KeyPressedMap;


bool FMyInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();
	PressedKey = Key;

	if (KeyPressedMap.Contains(Key))
	{
		KeyPressedMap[InKeyEvent.GetKey()] = true;
	}
	

	// Return false to allow the event to continue through the Slate event pipeline
	return IInputProcessor::HandleKeyDownEvent(SlateApp, InKeyEvent);
}

bool FMyInputProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	PressedMouseKey = MouseEvent.GetEffectingButton();
	return IInputProcessor::HandleMouseMoveEvent(SlateApp, MouseEvent);
}

auto FMyInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) -> void
{
}

bool FMyInputProcessor::IsKeyPressed(const FKey& Key)
{
	return KeyPressedMap.Contains(Key) && KeyPressedMap[Key];
}

void FMyInputProcessor::FillMap()
{
	KeyPressedMap.Add(EKeys::W, false);
	KeyPressedMap.Add(EKeys::A, false);
	KeyPressedMap.Add(EKeys::S, false);
	KeyPressedMap.Add(EKeys::D, false);
	KeyPressedMap.Add(EKeys::Q, false);
	KeyPressedMap.Add(EKeys::E, false);
}

bool FMyInputProcessor::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (KeyPressedMap.Contains(InKeyEvent.GetKey()))
	{
		KeyPressedMap[InKeyEvent.GetKey()] = false;
	}
	
	return IInputProcessor::HandleKeyUpEvent(SlateApp, InKeyEvent);
}
