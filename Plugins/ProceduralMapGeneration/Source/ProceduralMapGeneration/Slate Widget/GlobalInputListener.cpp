#include "GlobalInputListener.h"


bool FMyInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	// Get the pressed key
	// Add this line to FMyInputProcessor.cpp
	// Get the pressed key
	FKey Key = InKeyEvent.GetKey();
	PressedKey = Key;
	// Log the pressed key
	// UE_LOG(LogTemp, Display, TEXT("Key Pressed: %s"), *Key.ToString());

	// Here you can add a condition to check for specific keys
	// and return true to consume those events.

	// Return false to allow the event to continue through the Slate event pipeline
	return IInputProcessor::HandleKeyDownEvent(SlateApp, InKeyEvent);
}

auto FMyInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) -> void
{
}
