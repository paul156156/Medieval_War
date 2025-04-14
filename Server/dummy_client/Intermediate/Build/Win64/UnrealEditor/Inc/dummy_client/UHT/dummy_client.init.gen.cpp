// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodedummy_client_init() {}
	DUMMY_CLIENT_API UFunction* Z_Construct_UDelegateFunction_dummy_client_OnConnectionStatusChanged__DelegateSignature();
	DUMMY_CLIENT_API UFunction* Z_Construct_UDelegateFunction_dummy_client_OnJumpStateUpdate__DelegateSignature();
	DUMMY_CLIENT_API UFunction* Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature();
	DUMMY_CLIENT_API UFunction* Z_Construct_UDelegateFunction_dummy_client_OnRotationUpdate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_dummy_client;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_dummy_client()
	{
		if (!Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_dummy_client_OnConnectionStatusChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_dummy_client_OnJumpStateUpdate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_dummy_client_OnRotationUpdate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/dummy_client",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xE2EF5B33,
				0x10900A30,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_dummy_client(Z_Construct_UPackage__Script_dummy_client, TEXT("/Script/dummy_client"), Z_Registration_Info_UPackage__Script_dummy_client, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xE2EF5B33, 0x10900A30));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
