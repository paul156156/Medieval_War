// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMedieval_War_init() {}
	MEDIEVAL_WAR_API UFunction* Z_Construct_UDelegateFunction_Medieval_War_OnCharacterStateChanged__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Medieval_War;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Medieval_War()
	{
		if (!Z_Registration_Info_UPackage__Script_Medieval_War.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Medieval_War_OnCharacterStateChanged__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Medieval_War",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xEE74E835,
				0x3DF2A430,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Medieval_War.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Medieval_War.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Medieval_War(Z_Construct_UPackage__Script_Medieval_War, TEXT("/Script/Medieval_War"), Z_Registration_Info_UPackage__Script_Medieval_War, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xEE74E835, 0x3DF2A430));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
