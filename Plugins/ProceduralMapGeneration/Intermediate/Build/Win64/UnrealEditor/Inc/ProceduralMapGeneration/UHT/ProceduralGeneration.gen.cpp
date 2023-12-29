// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/Procedural Generation/ProceduralGeneration.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralGeneration() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGeneration();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGeneration_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARoomActor_NoRegister();
	PROCEDURALMAPGENERATION_API UEnum* Z_Construct_UEnum_ProceduralMapGeneration_EDirection2();
	PROCEDURALMAPGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FPathNode();
	PROCEDURALMAPGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FRoomConnection();
	PROCEDURALMAPGENERATION_API UScriptStruct* Z_Construct_UScriptStruct_FTileStruct();
	UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_RoomConnection;
class UScriptStruct* FRoomConnection::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_RoomConnection.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_RoomConnection.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FRoomConnection, (UObject*)Z_Construct_UPackage__Script_ProceduralMapGeneration(), TEXT("RoomConnection"));
	}
	return Z_Registration_Info_UScriptStruct_RoomConnection.OuterSingleton;
}
template<> PROCEDURALMAPGENERATION_API UScriptStruct* StaticStruct<FRoomConnection>()
{
	return FRoomConnection::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FRoomConnection_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedRoom;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomConnection_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FRoomConnection_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomConnection>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom = { "OverlappedRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FRoomConnection, OverlappedRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FRoomConnection_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FRoomConnection_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
		nullptr,
		&NewStructOps,
		"RoomConnection",
		sizeof(FRoomConnection),
		alignof(FRoomConnection),
		Z_Construct_UScriptStruct_FRoomConnection_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomConnection_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FRoomConnection_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FRoomConnection_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FRoomConnection()
	{
		if (!Z_Registration_Info_UScriptStruct_RoomConnection.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_RoomConnection.InnerSingleton, Z_Construct_UScriptStruct_FRoomConnection_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_RoomConnection.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EDirection2;
	static UEnum* EDirection2_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EDirection2.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EDirection2.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProceduralMapGeneration_EDirection2, (UObject*)Z_Construct_UPackage__Script_ProceduralMapGeneration(), TEXT("EDirection2"));
		}
		return Z_Registration_Info_UEnum_EDirection2.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UEnum* StaticEnum<EDirection2>()
	{
		return EDirection2_StaticEnum();
	}
	struct Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enumerators[] = {
		{ "Dir_Left", (int64)Dir_Left },
		{ "Dir_Right", (int64)Dir_Right },
		{ "Dir_Up", (int64)Dir_Up },
		{ "Dir_Down", (int64)Dir_Down },
		{ "Dir_None", (int64)Dir_None },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enum_MetaDataParams[] = {
		{ "Dir_Down.Name", "Dir_Down" },
		{ "Dir_Left.Name", "Dir_Left" },
		{ "Dir_None.Name", "Dir_None" },
		{ "Dir_Right.Name", "Dir_Right" },
		{ "Dir_Up.Name", "Dir_Up" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
		nullptr,
		"EDirection2",
		"EDirection2",
		Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::Regular,
		METADATA_PARAMS(Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_ProceduralMapGeneration_EDirection2()
	{
		if (!Z_Registration_Info_UEnum_EDirection2.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EDirection2.InnerSingleton, Z_Construct_UEnum_ProceduralMapGeneration_EDirection2_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EDirection2.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_PathNode;
class UScriptStruct* FPathNode::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_PathNode.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_PathNode.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FPathNode, (UObject*)Z_Construct_UPackage__Script_ProceduralMapGeneration(), TEXT("PathNode"));
	}
	return Z_Registration_Info_UScriptStruct_PathNode.OuterSingleton;
}
template<> PROCEDURALMAPGENERATION_API UScriptStruct* StaticStruct<FPathNode>()
{
	return FPathNode::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FPathNode_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPathNode_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FPathNode_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPathNode>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPathNode_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
		nullptr,
		&NewStructOps,
		"PathNode",
		sizeof(FPathNode),
		alignof(FPathNode),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FPathNode_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPathNode_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FPathNode()
	{
		if (!Z_Registration_Info_UScriptStruct_PathNode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_PathNode.InnerSingleton, Z_Construct_UScriptStruct_FPathNode_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_PathNode.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TileStruct;
class UScriptStruct* FTileStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TileStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TileStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTileStruct, (UObject*)Z_Construct_UPackage__Script_ProceduralMapGeneration(), TEXT("TileStruct"));
	}
	return Z_Registration_Info_UScriptStruct_TileStruct.OuterSingleton;
}
template<> PROCEDURALMAPGENERATION_API UScriptStruct* StaticStruct<FTileStruct>()
{
	return FTileStruct::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FTileStruct_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTileStruct_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "//Merged Path Into Tile\n" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Merged Path Into Tile" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTileStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTileStruct>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTileStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
		nullptr,
		&NewStructOps,
		"TileStruct",
		sizeof(FTileStruct),
		alignof(FTileStruct),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTileStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTileStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTileStruct()
	{
		if (!Z_Registration_Info_UScriptStruct_TileStruct.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TileStruct.InnerSingleton, Z_Construct_UScriptStruct_FTileStruct_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_TileStruct.InnerSingleton;
	}
	void AProceduralGeneration::StaticRegisterNativesAProceduralGeneration()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProceduralGeneration);
	UClass* Z_Construct_UClass_AProceduralGeneration_NoRegister()
	{
		return AProceduralGeneration::StaticClass();
	}
	struct Z_Construct_UClass_AProceduralGeneration_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StraightCorr_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_StraightCorr;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TurnCorridor_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TurnCorridor;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LargeRooms_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LargeRooms_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_LargeRooms;
		static const UECodeGen_Private::FClassPropertyParams NewProp_RoomDesigns_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RoomDesigns_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_RoomDesigns;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfRooms_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_NumberOfRooms;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxLargeRoomCount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaxLargeRoomCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MapSizeX_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MapSizeX;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MapSizeY_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MapSizeY;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileSizeX_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_TileSizeX;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileSizeY_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_TileSizeY;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BufferSize_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_BufferSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NormalRoomMaxSafeCheck_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_NormalRoomMaxSafeCheck;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LargeRoomMaxSafeCheck_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_LargeRoomMaxSafeCheck;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxSideBranchRoom_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaxSideBranchRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchLength_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_BranchLength;
		static const UECodeGen_Private::FIntPropertyParams NewProp_DebugRoomSequence_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DebugRoomSequence_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_DebugRoomSequence;
		static const UECodeGen_Private::FStructPropertyParams NewProp_BlockRoomLocations_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BlockRoomLocations_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_BlockRoomLocations;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BlockRoom_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_BlockRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualiseOverlaps_MetaData[];
#endif
		static void NewProp_VisualiseOverlaps_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualiseOverlaps;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualiseVisited_MetaData[];
#endif
		static void NewProp_VisualiseVisited_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualiseVisited;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeBeginAndEndTiles_MetaData[];
#endif
		static void NewProp_VisualizeBeginAndEndTiles_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeBeginAndEndTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeCorridorPath_MetaData[];
#endif
		static void NewProp_VisualizeCorridorPath_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeCorridorPath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeAllExclusions_MetaData[];
#endif
		static void NewProp_VisualizeAllExclusions_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeAllExclusions;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeEndSocketOverlapCheck_MetaData[];
#endif
		static void NewProp_VisualizeEndSocketOverlapCheck_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeEndSocketOverlapCheck;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCorridor_MetaData[];
#endif
		static void NewProp_SpawnCorridor_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_SpawnCorridor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastSpawnedRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LastSpawnedRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastSpawnLargeRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LastSpawnLargeRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastCheckedRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LastCheckedRoom;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProceduralGeneration_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_StraightCorr_MetaData[] = {
		{ "Category", "ProceduralGeneration" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_StraightCorr = { "StraightCorr", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, StraightCorr), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_StraightCorr_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_StraightCorr_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TurnCorridor_MetaData[] = {
		{ "Category", "ProceduralGeneration" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TurnCorridor = { "TurnCorridor", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, TurnCorridor), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TurnCorridor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TurnCorridor_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms_Inner = { "LargeRooms", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms_MetaData[] = {
		{ "Comment", "// UPROPERTY(EditAnywhere,BlueprintReadWrite)\n// TSubclassOf<ADoorActor> Door;\n" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "UPROPERTY(EditAnywhere,BlueprintReadWrite)\nTSubclassOf<ADoorActor> Door;" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms = { "LargeRooms", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, LargeRooms), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns_Inner = { "RoomDesigns", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Add all the rooms to be randomly select and spawned.*/" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Add all the rooms to be randomly select and spawned." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns = { "RoomDesigns", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, RoomDesigns), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NumberOfRooms_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Total number of rooms to be spawned*/" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Total number of rooms to be spawned" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NumberOfRooms = { "NumberOfRooms", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, NumberOfRooms), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NumberOfRooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NumberOfRooms_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxLargeRoomCount_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Valid for both main and side branching*/" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Valid for both main and side branching" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxLargeRoomCount = { "MaxLargeRoomCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, MaxLargeRoomCount), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxLargeRoomCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxLargeRoomCount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeX_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeX = { "MapSizeX", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, MapSizeX), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeX_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeX_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeY_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeY = { "MapSizeY", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, MapSizeY), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeY_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeX_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/" },
		{ "DisplayPriority", "6" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeX = { "TileSizeX", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, TileSizeX), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeX_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeX_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeY_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/" },
		{ "DisplayPriority", "7" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeY = { "TileSizeY", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, TileSizeY), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeY_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BufferSize_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/* Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.\n\x09 * A larger value will create a larger distance from other rooms.*/" },
		{ "DisplayPriority", "8" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.\n       * A larger value will create a larger distance from other rooms." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BufferSize = { "BufferSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, BufferSize), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BufferSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BufferSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NormalRoomMaxSafeCheck_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Not yet implemented*/// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=\"General Map settings\", meta=(DisplayPriority = 9))\n// int MaxPathCostLimit = 1000;\n" },
		{ "DisplayPriority", "10" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Not yet implemented// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category=\"General Map settings\", meta=(DisplayPriority = 9))\n// int MaxPathCostLimit = 1000;" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NormalRoomMaxSafeCheck = { "NormalRoomMaxSafeCheck", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, NormalRoomMaxSafeCheck), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NormalRoomMaxSafeCheck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NormalRoomMaxSafeCheck_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRoomMaxSafeCheck_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*When room is moved, this is the one to check never mind update here later*/" },
		{ "DisplayPriority", "11" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "When room is moved, this is the one to check never mind update here later" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRoomMaxSafeCheck = { "LargeRoomMaxSafeCheck", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, LargeRoomMaxSafeCheck), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRoomMaxSafeCheck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRoomMaxSafeCheck_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxSideBranchRoom_MetaData[] = {
		{ "Category", "Side Branching" },
		{ "Comment", "/*How many side branch room in total should it spawn when side branching*/" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "How many side branch room in total should it spawn when side branching" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxSideBranchRoom = { "MaxSideBranchRoom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, MaxSideBranchRoom), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxSideBranchRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxSideBranchRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BranchLength_MetaData[] = {
		{ "Category", "Side Branching" },
		{ "Comment", "/*The max branch length for side branching*/" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "The max branch length for side branching" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BranchLength = { "BranchLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, BranchLength), METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BranchLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BranchLength_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence_Inner = { "DebugRoomSequence", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs. */" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence = { "DebugRoomSequence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, DebugRoomSequence), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations_Inner = { "BlockRoomLocations", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location*/" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations = { "BlockRoomLocations", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, BlockRoomLocations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoom_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps. */" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps." },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoom = { "BlockRoom", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, BlockRoom), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualiseOverlaps = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps = { "VisualiseOverlaps", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualiseVisited = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited = { "VisualiseVisited", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Begin and End socket visualization color is Cyan*/" },
		{ "DisplayPriority", "6" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Begin and End socket visualization color is Cyan" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualizeBeginAndEndTiles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles = { "VisualizeBeginAndEndTiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Path visualization color is red*/" },
		{ "DisplayPriority", "7" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Path visualization color is red" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualizeCorridorPath = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath = { "VisualizeCorridorPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*All excluded tiles are purple*/" },
		{ "DisplayPriority", "8" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "All excluded tiles are purple" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualizeAllExclusions = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions = { "VisualizeAllExclusions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "10" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->VisualizeEndSocketOverlapCheck = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck = { "VisualizeEndSocketOverlapCheck", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "11" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor_SetBit(void* Obj)
	{
		((AProceduralGeneration*)Obj)->SpawnCorridor = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor = { "SpawnCorridor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGeneration), &Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnedRoom_MetaData[] = {
		{ "Comment", "/* Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)*/" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnedRoom = { "LastSpawnedRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, LastSpawnedRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnedRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnedRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnLargeRoom_MetaData[] = {
		{ "Comment", "/* Stored to make calculations for Last Spawned LARGE Room.*/" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "Stored to make calculations for Last Spawned LARGE Room." },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnLargeRoom = { "LastSpawnLargeRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, LastSpawnLargeRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnLargeRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnLargeRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastCheckedRoom_MetaData[] = {
		{ "Comment", "/*for IsEndSocketOverlapping, don't display message box more than once for same rooms*/" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGeneration.h" },
		{ "ToolTip", "for IsEndSocketOverlapping, don't display message box more than once for same rooms" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastCheckedRoom = { "LastCheckedRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGeneration, LastCheckedRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastCheckedRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastCheckedRoom_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AProceduralGeneration_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_StraightCorr,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TurnCorridor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRooms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_RoomDesigns,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NumberOfRooms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxLargeRoomCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MapSizeY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_TileSizeY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BufferSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_NormalRoomMaxSafeCheck,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LargeRoomMaxSafeCheck,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_MaxSideBranchRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BranchLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_DebugRoomSequence,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoomLocations,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_BlockRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseOverlaps,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualiseVisited,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeBeginAndEndTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeCorridorPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeAllExclusions,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_VisualizeEndSocketOverlapCheck,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_SpawnCorridor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnedRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastSpawnLargeRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGeneration_Statics::NewProp_LastCheckedRoom,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProceduralGeneration_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProceduralGeneration>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AProceduralGeneration_Statics::ClassParams = {
		&AProceduralGeneration::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AProceduralGeneration_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AProceduralGeneration_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGeneration_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProceduralGeneration()
	{
		if (!Z_Registration_Info_UClass_AProceduralGeneration.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProceduralGeneration.OuterSingleton, Z_Construct_UClass_AProceduralGeneration_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AProceduralGeneration.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<AProceduralGeneration>()
	{
		return AProceduralGeneration::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProceduralGeneration);
	AProceduralGeneration::~AProceduralGeneration() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::EnumInfo[] = {
		{ EDirection2_StaticEnum, TEXT("EDirection2"), &Z_Registration_Info_UEnum_EDirection2, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3129253705U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ScriptStructInfo[] = {
		{ FRoomConnection::StaticStruct, Z_Construct_UScriptStruct_FRoomConnection_Statics::NewStructOps, TEXT("RoomConnection"), &Z_Registration_Info_UScriptStruct_RoomConnection, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRoomConnection), 3104528068U) },
		{ FPathNode::StaticStruct, Z_Construct_UScriptStruct_FPathNode_Statics::NewStructOps, TEXT("PathNode"), &Z_Registration_Info_UScriptStruct_PathNode, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPathNode), 2498501331U) },
		{ FTileStruct::StaticStruct, Z_Construct_UScriptStruct_FTileStruct_Statics::NewStructOps, TEXT("TileStruct"), &Z_Registration_Info_UScriptStruct_TileStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTileStruct), 3924916830U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AProceduralGeneration, AProceduralGeneration::StaticClass, TEXT("AProceduralGeneration"), &Z_Registration_Info_UClass_AProceduralGeneration, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProceduralGeneration), 2431391015U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_617076181(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGeneration_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
