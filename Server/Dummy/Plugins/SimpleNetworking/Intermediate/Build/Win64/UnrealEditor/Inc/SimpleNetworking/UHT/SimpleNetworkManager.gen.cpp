// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworkManager() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Class USimpleNetworkManager
void USimpleNetworkManager::StaticRegisterNativesUSimpleNetworkManager()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USimpleNetworkManager);
UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister()
{
	return USimpleNetworkManager::StaticClass();
}
struct Z_Construct_UClass_USimpleNetworkManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SimpleNetworkManager.h" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USimpleNetworkManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USimpleNetworkManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USimpleNetworkManager_Statics::ClassParams = {
	&USimpleNetworkManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_USimpleNetworkManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USimpleNetworkManager()
{
	if (!Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton, Z_Construct_UClass_USimpleNetworkManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<USimpleNetworkManager>()
{
	return USimpleNetworkManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USimpleNetworkManager);
USimpleNetworkManager::~USimpleNetworkManager() {}
// End Class USimpleNetworkManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USimpleNetworkManager, USimpleNetworkManager::StaticClass, TEXT("USimpleNetworkManager"), &Z_Registration_Info_UClass_USimpleNetworkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USimpleNetworkManager), 3516463395U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_1491815218(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
