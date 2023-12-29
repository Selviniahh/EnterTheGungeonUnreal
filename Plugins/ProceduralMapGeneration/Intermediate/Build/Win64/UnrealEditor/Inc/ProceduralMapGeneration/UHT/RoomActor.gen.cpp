// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/Procedural Generation/RoomActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRoomActor() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	PAPER2D_API UClass* Z_Construct_UClass_UPaperTileMapComponent_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ADoorActor_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGen_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARoomActor();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARoomActor_NoRegister();
	PROCEDURALMAPGENERATION_API UEnum* Z_Construct_UEnum_ProceduralMapGeneration_Direction();
	SIDESCROLLING2D_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_Direction;
	static UEnum* Direction_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_Direction.OuterSingleton)
		{
			Z_Registration_Info_UEnum_Direction.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProceduralMapGeneration_Direction, (UObject*)Z_Construct_UPackage__Script_ProceduralMapGeneration(), TEXT("Direction"));
		}
		return Z_Registration_Info_UEnum_Direction.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UEnum* StaticEnum<Direction>()
	{
		return Direction_StaticEnum();
	}
	struct Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enumerators[] = {
		{ "HorizontalRight", (int64)HorizontalRight },
		{ "HorizontalLeft", (int64)HorizontalLeft },
		{ "VerticalUp", (int64)VerticalUp },
		{ "VerticalDown", (int64)VerticalDown },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enum_MetaDataParams[] = {
		{ "HorizontalLeft.Name", "HorizontalLeft" },
		{ "HorizontalRight.Name", "HorizontalRight" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
		{ "VerticalDown.Name", "VerticalDown" },
		{ "VerticalUp.Name", "VerticalUp" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
		nullptr,
		"Direction",
		"Direction",
		Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Regular,
		METADATA_PARAMS(Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_ProceduralMapGeneration_Direction()
	{
		if (!Z_Registration_Info_UEnum_Direction.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_Direction.InnerSingleton, Z_Construct_UEnum_ProceduralMapGeneration_Direction_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_Direction.InnerSingleton;
	}
	DEFINE_FUNCTION(ARoomActor::execCategorizeAndSortSceneCompsByTag)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CategorizeAndSortSceneCompsByTag();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ARoomActor::execVisualizeBeginEndTiles)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->VisualizeBeginEndTiles();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ARoomActor::execVisualizeAllBlocked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->VisualizeAllBlocked();
		P_NATIVE_END;
	}
	void ARoomActor::StaticRegisterNativesARoomActor()
	{
		UClass* Class = ARoomActor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CategorizeAndSortSceneCompsByTag", &ARoomActor::execCategorizeAndSortSceneCompsByTag },
			{ "VisualizeAllBlocked", &ARoomActor::execVisualizeAllBlocked },
			{ "VisualizeBeginEndTiles", &ARoomActor::execVisualizeBeginEndTiles },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics::Function_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARoomActor, nullptr, "CategorizeAndSortSceneCompsByTag", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARoomActor, nullptr, "VisualizeAllBlocked", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ARoomActor, nullptr, "VisualizeBeginEndTiles", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARoomActor);
	UClass* Z_Construct_UClass_ARoomActor_NoRegister()
	{
		return ARoomActor::StaticClass();
	}
	struct Z_Construct_UClass_ARoomActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PathCost_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_PathCost;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LargeRoom_MetaData[];
#endif
		static void NewProp_LargeRoom_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_LargeRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NoExit_MetaData[];
#endif
		static void NewProp_NoExit_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_NoExit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnterDoor_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_EnterDoor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitDoor_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_ExitDoor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NoExitVerticalUp_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_NoExitVerticalUp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NoExitVerticalDown_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_NoExitVerticalDown;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NoExitHorizontalRight_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_NoExitHorizontalRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NoExitHorizontalLeft_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_NoExitHorizontalLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RootScene_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RootScene;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DoorSocketEnter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DoorSocketEnter;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DoorSocketExit_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DoorSocketExit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BoxComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_BoxComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PathStartOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PathStartOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PathEndOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PathEndOffset;
		static const UECodeGen_Private::FStructPropertyParams NewProp_EnterExclusions_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnterExclusions_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_EnterExclusions;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ExitExclusions_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitExclusions_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ExitExclusions;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnterExclusionOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_EnterExclusionOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitExclusionOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ExitExclusionOffset;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ExitSocketChecks_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitSocketChecks_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ExitSocketChecks;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitSocketCheckOffset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ExitSocketCheckOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeBlocked_MetaData[];
#endif
		static void NewProp_VisualizeBlocked_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeBlocked;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnterSocketDirection_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_EnterSocketDirection;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExitSocketDirection_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_ExitSocketDirection;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeBeginAndEndTiles_MetaData[];
#endif
		static void NewProp_VisualizeBeginAndEndTiles_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeBeginAndEndTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaveAmount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_WaveAmount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnterDoorActor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_EnterDoorActor;
		static const UECodeGen_Private::FClassPropertyParams NewProp_EnemyClass_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EnemyClass_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_EnemyClass;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwnerCorridors_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerCorridors_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_OwnerCorridors;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IfCorridorOwnerRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IfCorridorOwnerRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProceduralGen_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ProceduralGen;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileMapComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_TileMapComponent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARoomActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ARoomActor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ARoomActor_CategorizeAndSortSceneCompsByTag, "CategorizeAndSortSceneCompsByTag" }, // 453854864
		{ &Z_Construct_UFunction_ARoomActor_VisualizeAllBlocked, "VisualizeAllBlocked" }, // 3550075319
		{ &Z_Construct_UFunction_ARoomActor_VisualizeBeginEndTiles, "VisualizeBeginEndTiles" }, // 3731550811
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Procedural Generation/RoomActor.h" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_PathCost_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_PathCost = { "PathCost", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, PathCost), METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathCost_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathCost_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	void Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom_SetBit(void* Obj)
	{
		((ARoomActor*)Obj)->LargeRoom = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom = { "LargeRoom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(ARoomActor), &Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom_SetBit, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	void Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit_SetBit(void* Obj)
	{
		((ARoomActor*)Obj)->NoExit = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit = { "NoExit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(ARoomActor), &Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit_SetBit, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoor_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoor = { "EnterDoor", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnterDoor), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitDoor_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitDoor = { "ExitDoor", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitDoor), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitDoor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitDoor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalUp_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalUp = { "NoExitVerticalUp", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, NoExitVerticalUp), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalUp_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalDown_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalDown = { "NoExitVerticalDown", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, NoExitVerticalDown), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalDown_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalDown_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalRight_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalRight = { "NoExitHorizontalRight", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, NoExitHorizontalRight), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalLeft_MetaData[] = {
		{ "Category", "Door" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalLeft = { "NoExitHorizontalLeft", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, NoExitHorizontalLeft), Z_Construct_UClass_UClass, Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_RootScene_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_RootScene = { "RootScene", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, RootScene), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_RootScene_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_RootScene_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketEnter_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketEnter = { "DoorSocketEnter", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, DoorSocketEnter), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketEnter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketEnter_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketExit_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketExit = { "DoorSocketExit", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, DoorSocketExit), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketExit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketExit_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_BoxComponent_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_BoxComponent = { "BoxComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, BoxComponent), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_BoxComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_BoxComponent_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_PathStartOffset_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_PathStartOffset = { "PathStartOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, PathStartOffset), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathStartOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathStartOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_PathEndOffset_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_PathEndOffset = { "PathEndOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, PathEndOffset), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathEndOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_PathEndOffset_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions_Inner = { "EnterExclusions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions = { "EnterExclusions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnterExclusions), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions_Inner = { "ExitExclusions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions = { "ExitExclusions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitExclusions), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusionOffset_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusionOffset = { "EnterExclusionOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnterExclusionOffset), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusionOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusionOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusionOffset_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusionOffset = { "ExitExclusionOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitExclusionOffset), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusionOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusionOffset_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks_Inner = { "ExitSocketChecks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks = { "ExitSocketChecks", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitSocketChecks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketCheckOffset_MetaData[] = {
		{ "Category", "Exclusions" },
		{ "DisplayPriority", "6" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketCheckOffset = { "ExitSocketCheckOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitSocketCheckOffset), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketCheckOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketCheckOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	void Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked_SetBit(void* Obj)
	{
		((ARoomActor*)Obj)->VisualizeBlocked = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked = { "VisualizeBlocked", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(ARoomActor), &Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked_SetBit, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterSocketDirection_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterSocketDirection = { "EnterSocketDirection", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnterSocketDirection), Z_Construct_UEnum_ProceduralMapGeneration_Direction, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterSocketDirection_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterSocketDirection_MetaData)) }; // 69348607
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketDirection_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketDirection = { "ExitSocketDirection", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ExitSocketDirection), Z_Construct_UEnum_ProceduralMapGeneration_Direction, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketDirection_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketDirection_MetaData)) }; // 69348607
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	void Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit(void* Obj)
	{
		((ARoomActor*)Obj)->VisualizeBeginAndEndTiles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles = { "VisualizeBeginAndEndTiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(ARoomActor), &Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_WaveAmount_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_WaveAmount = { "WaveAmount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, WaveAmount), METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_WaveAmount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_WaveAmount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoorActor_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoorActor = { "EnterDoorActor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnterDoorActor), Z_Construct_UClass_ADoorActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoorActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoorActor_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass_Inner = { "EnemyClass", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_AEnemyBase_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass = { "EnemyClass", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, EnemyClass), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors_Inner = { "OwnerCorridors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "Comment", "// TMap<ARoomActor*, FVector >\n" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
		{ "ToolTip", "TMap<ARoomActor*, FVector >" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors = { "OwnerCorridors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, OwnerCorridors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_IfCorridorOwnerRoom_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_IfCorridorOwnerRoom = { "IfCorridorOwnerRoom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, IfCorridorOwnerRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_IfCorridorOwnerRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_IfCorridorOwnerRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_ProceduralGen_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "Comment", "//Simulation\n" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
		{ "ToolTip", "Simulation" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_ProceduralGen = { "ProceduralGen", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, ProceduralGen), Z_Construct_UClass_AProceduralGen_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_ProceduralGen_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_ProceduralGen_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_Rotation_MetaData[] = {
		{ "Category", "RoomActor" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_Rotation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARoomActor_Statics::NewProp_TileMapComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Procedural Generation/RoomActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARoomActor_Statics::NewProp_TileMapComponent = { "TileMapComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARoomActor, TileMapComponent), Z_Construct_UClass_UPaperTileMapComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::NewProp_TileMapComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::NewProp_TileMapComponent_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARoomActor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_PathCost,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_LargeRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitDoor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalUp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitVerticalDown,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_NoExitHorizontalLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_RootScene,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketEnter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_DoorSocketExit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_BoxComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_PathStartOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_PathEndOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusions,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusions,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterExclusionOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitExclusionOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketChecks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketCheckOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBlocked,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterSocketDirection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ExitSocketDirection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_VisualizeBeginAndEndTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_WaveAmount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnterDoorActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_EnemyClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_OwnerCorridors,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_IfCorridorOwnerRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_ProceduralGen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_Rotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARoomActor_Statics::NewProp_TileMapComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARoomActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARoomActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARoomActor_Statics::ClassParams = {
		&ARoomActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ARoomActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ARoomActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ARoomActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARoomActor()
	{
		if (!Z_Registration_Info_UClass_ARoomActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARoomActor.OuterSingleton, Z_Construct_UClass_ARoomActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARoomActor.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<ARoomActor>()
	{
		return ARoomActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARoomActor);
	ARoomActor::~ARoomActor() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::EnumInfo[] = {
		{ Direction_StaticEnum, TEXT("Direction"), &Z_Registration_Info_UEnum_Direction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 69348607U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARoomActor, ARoomActor::StaticClass, TEXT("ARoomActor"), &Z_Registration_Info_UClass_ARoomActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARoomActor), 2986588843U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_4032047607(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_RoomActor_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
