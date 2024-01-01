// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralMapGeneration_init() {}
	PROCEDURALMAPGENERATION_API UFunction* Z_Construct_UDelegateFunction_ADoorActor_DoorEndOverlapDelegate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ProceduralMapGeneration;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ProceduralMapGeneration()
	{
		if (!Z_Registration_Info_UPackage__Script_ProceduralMapGeneration.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_ADoorActor_DoorEndOverlapDelegate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/ProceduralMapGeneration",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000040,
				0xC60D37C2,
				0x24134C8E,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ProceduralMapGeneration.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_ProceduralMapGeneration.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ProceduralMapGeneration(Z_Construct_UPackage__Script_ProceduralMapGeneration, TEXT("/Script/ProceduralMapGeneration"), Z_Registration_Info_UPackage__Script_ProceduralMapGeneration, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xC60D37C2, 0x24134C8E));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
