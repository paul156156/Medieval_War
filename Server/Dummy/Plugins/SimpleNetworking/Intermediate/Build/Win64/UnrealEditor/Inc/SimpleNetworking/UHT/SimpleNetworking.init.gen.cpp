// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworking_init() {}
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SimpleNetworking;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SimpleNetworking()
	{
		if (!Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SimpleNetworking",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xD1ECBF5A,
				0xF8ACFC26,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SimpleNetworking(Z_Construct_UPackage__Script_SimpleNetworking, TEXT("/Script/SimpleNetworking"), Z_Registration_Info_UPackage__Script_SimpleNetworking, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD1ECBF5A, 0xF8ACFC26));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
