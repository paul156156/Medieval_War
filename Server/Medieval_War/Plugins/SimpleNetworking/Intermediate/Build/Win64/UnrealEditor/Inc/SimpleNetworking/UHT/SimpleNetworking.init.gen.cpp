// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworking_init() {}
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnJumpStateUpdate__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature();
	SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SimpleNetworking;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SimpleNetworking()
	{
		if (!Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnJumpStateUpdate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SimpleNetworking",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xB8D7EB0C,
				0x8CB46C7E,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SimpleNetworking.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SimpleNetworking(Z_Construct_UPackage__Script_SimpleNetworking, TEXT("/Script/SimpleNetworking"), Z_Registration_Info_UPackage__Script_SimpleNetworking, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xB8D7EB0C, 0x8CB46C7E));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
