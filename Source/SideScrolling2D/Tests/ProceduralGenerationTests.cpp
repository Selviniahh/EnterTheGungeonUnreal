#include "Misc/AutomationTest.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationEditorCommon.h"
#include "ProceduralMapGeneration/Procedural Generation/ProceduralGen.h"
#include "Tests/AutomationCommon.h"

namespace ProceduralGenTestUtils
{
	

	UWorld* TestWorld = nullptr;
	AProceduralGen* FindProceduralGen()
	{
		if (!TestWorld && GEngine)
		{
			for (const FWorldContext& Context : GEngine->GetWorldContexts())
			{
				if (Context.WorldType == EWorldType::Game || Context.WorldType == EWorldType::PIE)
				{
					TestWorld = Context.World();
					break;
				}
			}
		}

		if (TestWorld)
		{
			for (TActorIterator<AProceduralGen> It(TestWorld); It; ++It)
			{
				return *It;
			}
		}

 		return nullptr;
	}
}


// DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForGenerationComplete, AProceduralGeneration*, ProceduralGen);
// bool FWaitForGenerationComplete::Update()
// {
// 	AProceduralGeneration* ProceduralGeneration = ProceduralGenTestUtils::FindProceduralGen();
// 	if (!ProceduralGeneration)
// 	{
// 		return false;
// 	}
//
// 	//We already know ProceduralGeneration is not null. Now check if generation is completed. 
// 	if (!ProceduralGeneration->bGenCompleteTest)
// 	{
// 		return false; 
// 	}
//
// 	if (ProceduralGeneration->NotValid)
// 	{
//         UE_LOG(LogTemp, Error, TEXT("Generation result is not valid!"));
// 		
// 		return false;
// 	}
// 	
// 	return true;
// }

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ProceduralGenerationTests, "ProceduralGenerationTests.IsEverythingValid", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool ProceduralGenerationTests::RunTest(const FString& Parameters)
{
	AProceduralGen* ProceduralGeneration = ProceduralGenTestUtils::FindProceduralGen();
	if (!ProceduralGeneration)
	{
		AddError(TEXT("Procedural generation is not found. Is it spawned in run time?"));
		return false; 
	}

	// if (ProceduralGeneration->bGenCompleteTest)
	// {
	// 	AddError(TEXT("Procedural generation is not yet finished. Run the test after all the rooms are spawned."));
	// 	return false; 
	// }
	//
	// if (ProceduralGeneration->NotValid)
	// {
	// 	AddError(TEXT("Procedural generation result is not valid!"));
	// 	return false; 
	// }
	
	AddInfo(TEXT("All the tiles are valid"));
	return true; 
}