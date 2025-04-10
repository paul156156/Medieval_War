// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodedummy_client_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_dummy_client;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_dummy_client()
	{
		if (!Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/dummy_client",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x64D8EE2F,
				0x8A8D6470,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_dummy_client.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_dummy_client(Z_Construct_UPackage__Script_dummy_client, TEXT("/Script/dummy_client"), Z_Registration_Info_UPackage__Script_dummy_client, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x64D8EE2F, 0x8A8D6470));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
