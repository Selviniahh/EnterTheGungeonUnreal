// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralMapGeneration/Public/Slate Widget/PluginSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePluginSettings() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FSoftObjectPath();
	DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_UPluginSettings();
	PROCEDURALMAPGENERATION_API UClass* Z_Construct_UClass_UPluginSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration();
// End Cross Module References
	void UPluginSettings::StaticRegisterNativesUPluginSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UPluginSettings);
	UClass* Z_Construct_UClass_UPluginSettings_NoRegister()
	{
		return UPluginSettings::StaticClass();
	}
	struct Z_Construct_UClass_UPluginSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Up_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Up;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Down_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Down;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Right_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Right;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Left_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Left;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPluginSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
		(UObject* (*)())Z_Construct_UPackage__Script_ProceduralMapGeneration,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPluginSettings_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "DisplayName", "Procedural Map Generation" },
		{ "IncludePath", "Slate Widget/PluginSettings.h" },
		{ "ModuleRelativePath", "Public/Slate Widget/PluginSettings.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPluginSettings_Statics::NewProp_Up_MetaData[] = {
		{ "Category", "My Plugin" },
		{ "ModuleRelativePath", "Public/Slate Widget/PluginSettings.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPluginSettings_Statics::NewProp_Up = { "Up", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPluginSettings, Up), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Up_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Up_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPluginSettings_Statics::NewProp_Down_MetaData[] = {
		{ "Category", "My Plugin" },
		{ "ModuleRelativePath", "Public/Slate Widget/PluginSettings.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPluginSettings_Statics::NewProp_Down = { "Down", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPluginSettings, Down), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Down_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Down_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPluginSettings_Statics::NewProp_Right_MetaData[] = {
		{ "Category", "My Plugin" },
		{ "ModuleRelativePath", "Public/Slate Widget/PluginSettings.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPluginSettings_Statics::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPluginSettings, Right), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Right_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Right_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPluginSettings_Statics::NewProp_Left_MetaData[] = {
		{ "Category", "My Plugin" },
		{ "ModuleRelativePath", "Public/Slate Widget/PluginSettings.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPluginSettings_Statics::NewProp_Left = { "Left", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UPluginSettings, Left), Z_Construct_UScriptStruct_FSoftObjectPath, METADATA_PARAMS(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Left_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::NewProp_Left_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPluginSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPluginSettings_Statics::NewProp_Up,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPluginSettings_Statics::NewProp_Down,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPluginSettings_Statics::NewProp_Right,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPluginSettings_Statics::NewProp_Left,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPluginSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPluginSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UPluginSettings_Statics::ClassParams = {
		&UPluginSettings::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UPluginSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::PropPointers),
		0,
		0x001000A6u,
		METADATA_PARAMS(Z_Construct_UClass_UPluginSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPluginSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPluginSettings()
	{
		if (!Z_Registration_Info_UClass_UPluginSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPluginSettings.OuterSingleton, Z_Construct_UClass_UPluginSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UPluginSettings.OuterSingleton;
	}
	template<> PROCEDURALMAPGENERATION_API UClass* StaticClass<UPluginSettings>()
	{
		return UPluginSettings::StaticClass();
	}
	UPluginSettings::UPluginSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPluginSettings);
	UPluginSettings::~UPluginSettings() {}
	struct Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Public_Slate_Widget_PluginSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Public_Slate_Widget_PluginSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UPluginSettings, UPluginSettings::StaticClass, TEXT("UPluginSettings"), &Z_Registration_Info_UClass_UPluginSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPluginSettings), 3225818016U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Public_Slate_Widget_PluginSettings_h_4242848254(TEXT("/Script/ProceduralMapGeneration"),
		Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Public_Slate_Widget_PluginSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_xqwys_RiderProjects_RealUnreal_Plugins_ProceduralMapGeneration_Source_ProceduralMapGeneration_Public_Slate_Widget_PluginSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
