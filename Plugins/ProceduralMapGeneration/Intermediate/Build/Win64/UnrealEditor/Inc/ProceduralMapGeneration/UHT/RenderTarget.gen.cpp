// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/TEst/RenderTarget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRenderTarget() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARenderTarget();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_ARenderTarget_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration();
// End Cross Module References
	void ARenderTarget::StaticRegisterNativesARenderTarget()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ARenderTarget);
	UClass* Z_Construct_UClass_ARenderTarget_NoRegister()
	{
		return ARenderTarget::StaticClass();
	}
	struct Z_Construct_UClass_ARenderTarget_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SceneCaptureComponent2D_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SceneCaptureComponent2D;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StaticMeshComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_StaticMeshComponent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ARenderTarget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARenderTarget_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "TEst/RenderTarget.h" },
		{ "ModuleRelativePath", "TEst/RenderTarget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARenderTarget_Statics::NewProp_SceneCaptureComponent2D_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TEst/RenderTarget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARenderTarget_Statics::NewProp_SceneCaptureComponent2D = { "SceneCaptureComponent2D", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARenderTarget, SceneCaptureComponent2D), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARenderTarget_Statics::NewProp_SceneCaptureComponent2D_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARenderTarget_Statics::NewProp_SceneCaptureComponent2D_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ARenderTarget_Statics::NewProp_StaticMeshComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "TEst/RenderTarget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ARenderTarget_Statics::NewProp_StaticMeshComponent = { "StaticMeshComponent", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ARenderTarget, StaticMeshComponent), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ARenderTarget_Statics::NewProp_StaticMeshComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ARenderTarget_Statics::NewProp_StaticMeshComponent_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ARenderTarget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARenderTarget_Statics::NewProp_SceneCaptureComponent2D,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ARenderTarget_Statics::NewProp_StaticMeshComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ARenderTarget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ARenderTarget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ARenderTarget_Statics::ClassParams = {
		&ARenderTarget::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ARenderTarget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ARenderTarget_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ARenderTarget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ARenderTarget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ARenderTarget()
	{
		if (!Z_Registration_Info_UClass_ARenderTarget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ARenderTarget.OuterSingleton, Z_Construct_UClass_ARenderTarget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ARenderTarget.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<ARenderTarget>()
	{
		return ARenderTarget::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ARenderTarget);
	ARenderTarget::~ARenderTarget() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_Documents_Unreal_Projects_SideScrolling2D_master_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_TEst_RenderTarget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_Documents_Unreal_Projects_SideScrolling2D_master_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_TEst_RenderTarget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ARenderTarget, ARenderTarget::StaticClass, TEXT("ARenderTarget"), &Z_Registration_Info_UClass_ARenderTarget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ARenderTarget), 1409692329U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_Documents_Unreal_Projects_SideScrolling2D_master_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_TEst_RenderTarget_h_1647269008(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_Documents_Unreal_Projects_SideScrolling2D_master_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_TEst_RenderTarget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_Documents_Unreal_Projects_SideScrolling2D_master_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_TEst_RenderTarget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
