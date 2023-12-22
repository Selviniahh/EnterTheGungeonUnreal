// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomCommands.h"
#include "Engine/Console.h"
#include "Internationalization/Regex.h"

UCustomCommands::UCustomCommands()
{
	MyCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("CopyGrid"),TEXT("Help Text"),FConsoleCommandWithArgsDelegate::CreateUObject(this,&UCustomCommands::CopyGridWithArgs));
	MyCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("GoRight"),TEXT("GoRight"),FConsoleCommandWithArgsDelegate::CreateUObject(this,&UCustomCommands::GoRight));
	MyCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("GoLeft"),TEXT("GoLeft"),FConsoleCommandWithArgsDelegate::CreateUObject(this,&UCustomCommands::GoLeft));
	MyCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("GoUp"),TEXT("GoUp"),FConsoleCommandWithArgsDelegate::CreateUObject(this,&UCustomCommands::GoUp));
	MyCommand = IConsoleManager::Get().RegisterConsoleCommand(TEXT("GoDown"),TEXT("GoDown"),FConsoleCommandWithArgsDelegate::CreateUObject(this,&UCustomCommands::GoDown));
}

UCustomCommands::~UCustomCommands()
{
	if (MyCommand)
	{
		IConsoleManager::Get().UnregisterConsoleObject(MyCommand,false);
	}
}

//Wrapper functions to parse Direction based on called Command to GoDirectionWithArgs function. This wrapper functions exist due to called command name is inaccessible from bound delegate function. 
void UCustomCommands::GoRight(const TArray<FString>& Args) {GoDirectionWithArgs("GoRight", Args);}
void UCustomCommands::GoLeft(const TArray<FString>& Args) {GoDirectionWithArgs("GoLeft", Args);}
void UCustomCommands::GoUp(const TArray<FString>& Args) {GoDirectionWithArgs("GoUp", Args);}
void UCustomCommands::GoDown(const TArray<FString>& Args) {GoDirectionWithArgs("GoDown", Args);}


void UCustomCommands::GoDirectionWithArgs(const FString& Direction, const TArray<FString>& Args)
{
	FString CommandName = Direction;
	
	TMap<FString, EActionType> CommandToActionMap;
	CommandToActionMap.Add("GoRight", IncrementX);
	CommandToActionMap.Add("GoLeft", DecrementX);
	CommandToActionMap.Add("GoUp", DecrementY);
	CommandToActionMap.Add("GoDown", IncrementY);

	//If the given argument is empty, just make a single increment or decrement direction 
	if (Args.IsEmpty())
	{
		EActionType* Action = CommandToActionMap.Find(CommandName);
		FString Copy;
		FPlatformMisc::ClipboardPaste(Copy);
		ModifyAndCopyFIntPointToClipboard(Copy,*Action, 1);
	}
	//Make multiple operation direction based on given argument
	else
	{
		FString Multiplyer = Args[0];  // Expecting a single argument like "3x10"
		TArray<FString> Dimensions;
		if (Multiplyer.StartsWith(TEXT("x"),ESearchCase::IgnoreCase)) //In case given argument is "x5" chop the x. 
			Multiplyer.RemoveAt(0,1,true);
		
		EActionType* Action = CommandToActionMap.Find(CommandName);
		FString Copy;
		FPlatformMisc::ClipboardPaste(Copy);
		ModifyAndCopyFIntPointToClipboard(Copy,*Action, FCString::Atoi(*Multiplyer));
	}
}


/*Bound function to command delegate*/
void UCustomCommands::CopyGridWithArgs(const TArray<FString>& Args)
{
	if (Args.Num() > 0)
	{
		FString Arg = Args[0];  // Expecting a single argument like "3x10"
		TArray<FString> Dimensions;
		Arg.ParseIntoArray(Dimensions, TEXT("x"), true); // For (3x10) Dimensions[0] = "3", Dimensions[1] = "10"

		if (Dimensions.Num() == 2)
		{
			int32 Width = FCString::Atoi(*Dimensions[0]);
			int32 Height = FCString::Atoi(*Dimensions[1]);

			CopyGridCommand(Width, Height);
		}
	}
}

/*Copy IntPoint array to clipboard */
void UCustomCommands::CopyGridCommand(int width, int height)
{
	FString ResultString;
    
	for(int x = 0; x < width; ++x)
	{
		for(int y = 0; y < height; ++y)
		{
			//Append to make it work like array
			ResultString += FString::Printf(TEXT("(X=%d,Y=%d),"), x, y); 
		}
	}
    
	// Remove the trailing comma
	if (ResultString.Len() > 0)
	{
		ResultString.RemoveAt(ResultString.Len() - 1);
	}
    
	// Add enclosing parentheses
	ResultString = TEXT("(") + ResultString + TEXT(")");
    
	const TCHAR* TextToCopy = *ResultString;
	FPlatformMisc::ClipboardCopy(TextToCopy);
}

void UCustomCommands::ModifyAndCopyFIntPointToClipboard(const FString& InputString, EActionType Action, int Multiplyer)
{
	int32 XValueInt = 0;
	int32 YValueInt = 0;
    
	if (TryParseFIntPoint(InputString, XValueInt, YValueInt))
	{
		ModifyFIntPointValues(XValueInt, YValueInt, Action, Multiplyer);
	}
	else
	{
		//If no regex found, start with copying initial values and make modification what action is given. (X=-1,Y=0) or (X=0,Y=1)
		ModifyFIntPointValues(XValueInt, YValueInt, Action, Multiplyer);
	}

	//Convert ints to FString
	FString ResultString = FString::Printf(TEXT("(X=%d,Y=%d)"), XValueInt, YValueInt);
	CopyToClipboard(ResultString);
}


bool UCustomCommands::TryParseFIntPoint(const FString& InputString, int32& OutX, int32& OutY)
{
	FRegexPattern Pattern(TEXT("\\(X=(-?\\d+),Y=(-?\\d+)\\)"));
	FRegexMatcher Matcher(Pattern, InputString);
    
	if (Matcher.FindNext())
	{
		OutX = FCString::Atoi(*Matcher.GetCaptureGroup(1));
		OutY = FCString::Atoi(*Matcher.GetCaptureGroup(2));
		return true;
	}
	return false;
}

void UCustomCommands::ModifyFIntPointValues(int32& XValueInt, int32& YValueInt, EActionType Action, int Multiplyer)
{
	switch (Action)
	{
	case IncrementX:
		XValueInt += Multiplyer;
		break;
	case DecrementX:
		XValueInt -= Multiplyer;
		break;
	case IncrementY:
		YValueInt += Multiplyer;
		break;
	case DecrementY:
		YValueInt -= Multiplyer;
		break;
	default: break;
	}
}

void UCustomCommands::CopyToClipboard(const FString& StringToCopy)
{
	const TCHAR* TextToCopy = *StringToCopy;
	FPlatformMisc::ClipboardCopy(TextToCopy);
}
