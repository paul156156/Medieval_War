// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDummy_init() {}
	DUMMY_API UFunction* Z_Construct_UDelegateFunction_Dummy_OnCharacterStateChanged__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Dummy;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Dummy()
	{
		if (!Z_Registration_Info_UPackage__Script_Dummy.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Dummy_OnCharacterStateChanged__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Dummy",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xB802D0CD,
				0x8A2D2C51,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Dummy.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Dummy.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Dummy(Z_Construct_UPackage__Script_Dummy, TEXT("/Script/Dummy"), Z_Registration_Info_UPackage__Script_Dummy, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xB802D0CD, 0x8A2D2C51));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
