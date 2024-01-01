// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/Procedural Generation/ProceduralGen.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralGen() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGen();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGen_NoRegister();
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
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FRoomConnection_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FRoomConnection>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FRoomConnection_Statics::NewProp_OverlappedRoom_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
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
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
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
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
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
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
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
	void AProceduralGen::StaticRegisterNativesAProceduralGen()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProceduralGen);
	UClass* Z_Construct_UClass_AProceduralGen_NoRegister()
	{
		return AProceduralGen::StaticClass();
	}
	struct Z_Construct_UClass_AProceduralGen_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CastedRoomDesigns_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CastedRoomDesigns_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CastedRoomDesigns;
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxSideBranchRoom_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaxSideBranchRoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StraightCorrClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_StraightCorrClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TurnCorridorClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_TurnCorridorClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastSpawnedHorizontalStraightCorr_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LastSpawnedHorizontalStraightCorr;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LargeRooms_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LargeRooms_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_LargeRooms;
		static const UECodeGen_Private::FClassPropertyParams NewProp_DebugRoomSequence_Inner;
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeOverlaps_MetaData[];
#endif
		static void NewProp_VisualizeOverlaps_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeOverlaps;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeVisited_MetaData[];
#endif
		static void NewProp_VisualizeVisited_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeVisited;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisualizeOverlappedRoomTiles_MetaData[];
#endif
		static void NewProp_VisualizeOverlappedRoomTiles_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_VisualizeOverlappedRoomTiles;
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BufferSize_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_BufferSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FindCorridorPathLimit_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_FindCorridorPathLimit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxLargeRoomCount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaxLargeRoomCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchLength_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_BranchLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxMoveOverlappedRoomIterate_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaxMoveOverlappedRoomIterate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectedLargeRoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SelectedLargeRoom;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnedRooms_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SpawnedRooms_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnedRooms;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LargeRoomsToBeAdded_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LargeRoomsToBeAdded_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_LargeRoomsToBeAdded;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RoomsToBeRemoved_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RoomsToBeRemoved_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_RoomsToBeRemoved;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CastedTurnCorridor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CastedTurnCorridor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ApplyTurnPenalty_MetaData[];
#endif
		static void NewProp_ApplyTurnPenalty_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ApplyTurnPenalty;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TurnPenaltyAmount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_TurnPenaltyAmount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnlyMakeCorridorCheck_MetaData[];
#endif
		static void NewProp_OnlyMakeCorridorCheck_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_OnlyMakeCorridorCheck;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DisplayCustomPathScenarios_MetaData[];
#endif
		static void NewProp_DisplayCustomPathScenarios_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_DisplayCustomPathScenarios;
		static const UECodeGen_Private::FClassPropertyParams NewProp_FixedTwoRoomActor_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FixedTwoRoomActor_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_FixedTwoRoomActor;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VerticalUpToVerticalUp_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerticalUpToVerticalUp_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VerticalUpToVerticalUp;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VerticalUpTurnRightToVerticalUp_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerticalUpTurnRightToVerticalUp_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VerticalUpTurnRightToVerticalUp;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VerticalUpTurnLeftToVerticalUp_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerticalUpTurnLeftToVerticalUp_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VerticalUpTurnLeftToVerticalUp;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProceduralGen_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Procedural Generation/ProceduralGen.h" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns_Inner = { "CastedRoomDesigns", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns = { "CastedRoomDesigns", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, CastedRoomDesigns), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns_Inner = { "RoomDesigns", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Add all the rooms to be randomly select and spawned.*/" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Add all the rooms to be randomly select and spawned." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns = { "RoomDesigns", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, RoomDesigns), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_NumberOfRooms_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Total number of rooms to be spawned*/" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Total number of rooms to be spawned" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_NumberOfRooms = { "NumberOfRooms", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, NumberOfRooms), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_NumberOfRooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_NumberOfRooms_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeX_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeX = { "MapSizeX", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, MapSizeX), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeX_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeX_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeY_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms*/" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Given amount of tiles will be included to make all the algorithm checks. Make sure it's long enough if you planning to spawn large amount of rooms" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeY = { "MapSizeY", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, MapSizeY), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeY_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeX_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/" },
		{ "DisplayPriority", "6" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeX = { "TileSizeX", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, TileSizeX), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeX_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeX_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeY_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/*The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors.*/" },
		{ "DisplayPriority", "7" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "The tile size for entire map. It's important to give precise small amount otherwise there will be tile offset issues when a path trying to be found for connecting two rooms with corridors." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeY = { "TileSizeY", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, TileSizeY), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeY_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxSideBranchRoom_MetaData[] = {
		{ "Category", "ProceduralGen" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxSideBranchRoom = { "MaxSideBranchRoom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, MaxSideBranchRoom), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxSideBranchRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxSideBranchRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_StraightCorrClass_MetaData[] = {
		{ "Category", "ProceduralGen" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_StraightCorrClass = { "StraightCorrClass", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, StraightCorrClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_StraightCorrClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_StraightCorrClass_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnCorridorClass_MetaData[] = {
		{ "Category", "ProceduralGen" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnCorridorClass = { "TurnCorridorClass", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, TurnCorridorClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnCorridorClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnCorridorClass_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedHorizontalStraightCorr_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedHorizontalStraightCorr = { "LastSpawnedHorizontalStraightCorr", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, LastSpawnedHorizontalStraightCorr), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedHorizontalStraightCorr_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedHorizontalStraightCorr_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms_Inner = { "LargeRooms", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms = { "LargeRooms", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, LargeRooms), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence_Inner = { "DebugRoomSequence", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs. */" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Make sure Room sequence length is equal to -1 Number of rooms. Secondly, give index numbers of Room designs." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence = { "DebugRoomSequence", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, DebugRoomSequence), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations_Inner = { "BlockRoomLocations", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location*/" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "For debug purposes the location for each given BlockRoom's location. Block room will be spawned at given location" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations = { "BlockRoomLocations", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, BlockRoomLocations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoom_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps. */" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Solely for debug purposes. The added room will be used to check overlaps with original rooms. Intended to force rooms to have overlaps." },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoom = { "BlockRoom", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, BlockRoom), Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeOverlaps = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps = { "VisualizeOverlaps", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "5" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeVisited = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited = { "VisualizeVisited", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*When a room overlapped, this option will visualize all the areas it searched to spawn overlapped room. To find out how much you need to increase MaxOverlappedRoomIterate, enable this option*/" },
		{ "DisplayPriority", "6" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "When a room overlapped, this option will visualize all the areas it searched to spawn overlapped room. To find out how much you need to increase MaxOverlappedRoomIterate, enable this option" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeOverlappedRoomTiles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles = { "VisualizeOverlappedRoomTiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Begin and End socket visualization color is Cyan*/" },
		{ "DisplayPriority", "7" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Begin and End socket visualization color is Cyan" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeBeginAndEndTiles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles = { "VisualizeBeginAndEndTiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*Path visualization color is red*/" },
		{ "DisplayPriority", "8" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Path visualization color is red" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeCorridorPath = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath = { "VisualizeCorridorPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions_MetaData[] = {
		{ "Category", "Debugging" },
		{ "Comment", "/*All excluded tiles are purple*/" },
		{ "DisplayPriority", "9" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "All excluded tiles are purple" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeAllExclusions = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions = { "VisualizeAllExclusions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "10" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->VisualizeEndSocketOverlapCheck = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck = { "VisualizeEndSocketOverlapCheck", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor_MetaData[] = {
		{ "Category", "Debugging" },
		{ "DisplayPriority", "11" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->SpawnCorridor = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor = { "SpawnCorridor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedRoom_MetaData[] = {
		{ "Comment", "/* Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)*/" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Stored to make calculations for Last Spawned Room. (Connect LastSpawnedRoom's exit socket with new room)" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedRoom = { "LastSpawnedRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, LastSpawnedRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedRoom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_BufferSize_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "Comment", "/* Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.\n\x09\x09 * A larger value will create a larger distance from other rooms.*/" },
		{ "DisplayPriority", "8" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Determines the buffer size when a room is overlapped and moved to a non-overlapping position.A smaller value might cause the overlapped room to be squeezed closer to other rooms.\n               * A larger value will create a larger distance from other rooms." },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_BufferSize = { "BufferSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, BufferSize), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BufferSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BufferSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_FindCorridorPathLimit_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "DisplayPriority", "10" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_FindCorridorPathLimit = { "FindCorridorPathLimit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, FindCorridorPathLimit), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_FindCorridorPathLimit_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_FindCorridorPathLimit_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxLargeRoomCount_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "DisplayPriority", "3" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxLargeRoomCount = { "MaxLargeRoomCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, MaxLargeRoomCount), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxLargeRoomCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxLargeRoomCount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_BranchLength_MetaData[] = {
		{ "Category", "General Map settings" },
		{ "DisplayPriority", "4" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_BranchLength = { "BranchLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, BranchLength), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BranchLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_BranchLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxMoveOverlappedRoomIterate_MetaData[] = {
		{ "Category", "ProceduralGen" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxMoveOverlappedRoomIterate = { "MaxMoveOverlappedRoomIterate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, MaxMoveOverlappedRoomIterate), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxMoveOverlappedRoomIterate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxMoveOverlappedRoomIterate_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_SelectedLargeRoom_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_SelectedLargeRoom = { "SelectedLargeRoom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, SelectedLargeRoom), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SelectedLargeRoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SelectedLargeRoom_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms_Inner = { "SpawnedRooms", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms = { "SpawnedRooms", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, SpawnedRooms), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded_Inner = { "LargeRoomsToBeAdded", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded = { "LargeRoomsToBeAdded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, LargeRoomsToBeAdded), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved_Inner = { "RoomsToBeRemoved", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved = { "RoomsToBeRemoved", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, RoomsToBeRemoved), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedTurnCorridor_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedTurnCorridor = { "CastedTurnCorridor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, CastedTurnCorridor), Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedTurnCorridor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedTurnCorridor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty_MetaData[] = {
		{ "Category", "Corridor path finding" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->ApplyTurnPenalty = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty = { "ApplyTurnPenalty", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnPenaltyAmount_MetaData[] = {
		{ "Category", "Corridor path finding" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnPenaltyAmount = { "TurnPenaltyAmount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, TurnPenaltyAmount), METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnPenaltyAmount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnPenaltyAmount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck_MetaData[] = {
		{ "Category", "ProceduralGen" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->OnlyMakeCorridorCheck = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck = { "OnlyMakeCorridorCheck", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios_MetaData[] = {
		{ "Category", "Make custom path scenarios" },
		{ "Comment", "//Now I need to give custom pattern but I really not sure how to implement this\n" },
		{ "DisplayPriority", "1" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
		{ "ToolTip", "Now I need to give custom pattern but I really not sure how to implement this" },
	};
#endif
	void Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios_SetBit(void* Obj)
	{
		((AProceduralGen*)Obj)->DisplayCustomPathScenarios = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios = { "DisplayCustomPathScenarios", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(AProceduralGen), &Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios_SetBit, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor_Inner = { "FixedTwoRoomActor", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor_MetaData[] = {
		{ "Category", "Make custom path scenarios" },
		{ "DisplayPriority", "2" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor = { "FixedTwoRoomActor", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, FixedTwoRoomActor), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp_Inner = { "VerticalUpToVerticalUp", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp_MetaData[] = {
		{ "Category", "Make custom path scenarios" },
		{ "DisplayPriority", "3" },
		{ "EditCondition", "DisplayCustomPathScenarios" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp = { "VerticalUpToVerticalUp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, VerticalUpToVerticalUp), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp_Inner = { "VerticalUpTurnRightToVerticalUp", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp_MetaData[] = {
		{ "Category", "Make custom path scenarios" },
		{ "DisplayPriority", "4" },
		{ "EditCondition", "DisplayCustomPathScenarios" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp = { "VerticalUpTurnRightToVerticalUp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, VerticalUpTurnRightToVerticalUp), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp_Inner = { "VerticalUpTurnLeftToVerticalUp", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp_MetaData[] = {
		{ "Category", "Make custom path scenarios" },
		{ "DisplayPriority", "5" },
		{ "EditCondition", "DisplayCustomPathScenarios" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Procedural Generation/ProceduralGen.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp = { "VerticalUpTurnLeftToVerticalUp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AProceduralGen, VerticalUpTurnLeftToVerticalUp), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AProceduralGen_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedRoomDesigns,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomDesigns,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_NumberOfRooms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_MapSizeY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_TileSizeY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxSideBranchRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_StraightCorrClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnCorridorClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedHorizontalStraightCorr,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRooms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_DebugRoomSequence,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoomLocations,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_BlockRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlaps,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeVisited,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeOverlappedRoomTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeBeginAndEndTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeCorridorPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeAllExclusions,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VisualizeEndSocketOverlapCheck,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnCorridor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LastSpawnedRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_BufferSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_FindCorridorPathLimit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxLargeRoomCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_BranchLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_MaxMoveOverlappedRoomIterate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_SelectedLargeRoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_SpawnedRooms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_LargeRoomsToBeAdded,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_RoomsToBeRemoved,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_CastedTurnCorridor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_ApplyTurnPenalty,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_TurnPenaltyAmount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_OnlyMakeCorridorCheck,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_DisplayCustomPathScenarios,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_FixedTwoRoomActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpToVerticalUp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnRightToVerticalUp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProceduralGen_Statics::NewProp_VerticalUpTurnLeftToVerticalUp,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProceduralGen_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProceduralGen>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AProceduralGen_Statics::ClassParams = {
		&AProceduralGen::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AProceduralGen_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AProceduralGen_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralGen_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProceduralGen()
	{
		if (!Z_Registration_Info_UClass_AProceduralGen.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProceduralGen.OuterSingleton, Z_Construct_UClass_AProceduralGen_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AProceduralGen.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<AProceduralGen>()
	{
		return AProceduralGen::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProceduralGen);
	AProceduralGen::~AProceduralGen() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::EnumInfo[] = {
		{ EDirection2_StaticEnum, TEXT("EDirection2"), &Z_Registration_Info_UEnum_EDirection2, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3097676441U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ScriptStructInfo[] = {
		{ FRoomConnection::StaticStruct, Z_Construct_UScriptStruct_FRoomConnection_Statics::NewStructOps, TEXT("RoomConnection"), &Z_Registration_Info_UScriptStruct_RoomConnection, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FRoomConnection), 1100347170U) },
		{ FPathNode::StaticStruct, Z_Construct_UScriptStruct_FPathNode_Statics::NewStructOps, TEXT("PathNode"), &Z_Registration_Info_UScriptStruct_PathNode, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FPathNode), 195156686U) },
		{ FTileStruct::StaticStruct, Z_Construct_UScriptStruct_FTileStruct_Statics::NewStructOps, TEXT("TileStruct"), &Z_Registration_Info_UScriptStruct_TileStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTileStruct), 3240958174U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AProceduralGen, AProceduralGen::StaticClass, TEXT("AProceduralGen"), &Z_Registration_Info_UClass_AProceduralGen, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProceduralGen), 3305577712U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_1727281529(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_ProceduralGen_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
