// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/Procedural Generation/MakeAllCorridorScenarioTest.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMakeAllCorridorScenarioTest() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_AProceduralGen_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARoomActor_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_UMakeAllCorridorScenarioTest();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_UMakeAllCorridorScenarioTest_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration();
// End Cross Module References
	void UMakeAllCorridorScenarioTest::StaticRegisterNativesUMakeAllCorridorScenarioTest()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMakeAllCorridorScenarioTest);
	UClass* Z_Construct_UClass_UMakeAllCorridorScenarioTest_NoRegister()
	{
		return UMakeAllCorridorScenarioTest::StaticClass();
	}
	struct Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProGen_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ProGen;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FixedRoomActor_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FixedRoomActor_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_FixedRoomActor;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Procedural Generation/MakeAllCorridorScenarioTest.h" },
		{ "ModuleRelativePath", "Procedural Generation/MakeAllCorridorScenarioTest.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_ProGen_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/MakeAllCorridorScenarioTest.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_ProGen = { "ProGen", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UMakeAllCorridorScenarioTest, ProGen), Z_Construct_UClass_AProceduralGen_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_ProGen_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_ProGen_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor_Inner = { "FixedRoomActor", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_ARoomActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor_MetaData[] = {
		{ "ModuleRelativePath", "Procedural Generation/MakeAllCorridorScenarioTest.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor = { "FixedRoomActor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UMakeAllCorridorScenarioTest, FixedRoomActor), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_ProGen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::NewProp_FixedRoomActor,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMakeAllCorridorScenarioTest>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::ClassParams = {
		&UMakeAllCorridorScenarioTest::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMakeAllCorridorScenarioTest()
	{
		if (!Z_Registration_Info_UClass_UMakeAllCorridorScenarioTest.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMakeAllCorridorScenarioTest.OuterSingleton, Z_Construct_UClass_UMakeAllCorridorScenarioTest_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMakeAllCorridorScenarioTest.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<UMakeAllCorridorScenarioTest>()
	{
		return UMakeAllCorridorScenarioTest::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMakeAllCorridorScenarioTest);
	UMakeAllCorridorScenarioTest::~UMakeAllCorridorScenarioTest() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_MakeAllCorridorScenarioTest_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_MakeAllCorridorScenarioTest_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMakeAllCorridorScenarioTest, UMakeAllCorridorScenarioTest::StaticClass, TEXT("UMakeAllCorridorScenarioTest"), &Z_Registration_Info_UClass_UMakeAllCorridorScenarioTest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMakeAllCorridorScenarioTest), 1464187843U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_MakeAllCorridorScenarioTest_h_861726449(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_MakeAllCorridorScenarioTest_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Procedural_Generation_MakeAllCorridorScenarioTest_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
