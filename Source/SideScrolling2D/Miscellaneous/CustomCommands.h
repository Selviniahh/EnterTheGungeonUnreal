// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CustomCommands.generated.h"

/**
 * 
 */

UENUM()
enum EActionType
{
	IncrementX,
	DecrementX,
	IncrementY,
	DecrementY,
	None
};

UCLASS()
class SIDESCROLLING2D_API UCustomCommands : public UObject
{
	GENERATED_BODY()

public:
	UCustomCommands();
	~UCustomCommands();

private:
	void CopyGridCommand(int width, int height);

	void GoRight(const TArray<FString>& Args);
	void GoLeft(const TArray<FString>& Args);
	void GoUp(const TArray<FString>& Args);
	void GoDown(const TArray<FString>& Args);
	
	void CopyToClipboard(const FString& StringToCopy);
	void CopyGridWithArgs(const TArray< FString >& Args);
	void GoDirectionWithArgs(const FString& Direction, const TArray<FString>& Args);


	/*Check if InputString is valid IntPoint. If valid, define OutX and OutY with what clipboard has */
	bool TryParseFIntPoint(const FString& InputString, int32& OutX, int32& OutY);

	/*Adjust values based on action*/
	void ModifyFIntPointValues(int32& XValueInt, int32& YValueInt, EActionType Action, int Multiplyer);

	/*Main function for copying clipboard for 4 direction */
	void ModifyAndCopyFIntPointToClipboard(const FString& InputString, EActionType Action, int Multiplyer);

	IConsoleCommand* MyCommand;
};
