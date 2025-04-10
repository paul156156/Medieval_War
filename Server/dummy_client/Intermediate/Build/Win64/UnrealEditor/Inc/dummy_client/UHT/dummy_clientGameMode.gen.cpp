// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "dummy_client/dummy_clientGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodedummy_clientGameMode() {}

// Begin Cross Module References
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientGameMode();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_dummy_client();
// End Cross Module References

// Begin Class Adummy_clientGameMode
void Adummy_clientGameMode::StaticRegisterNativesAdummy_clientGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(Adummy_clientGameMode);
UClass* Z_Construct_UClass_Adummy_clientGameMode_NoRegister()
{
	return Adummy_clientGameMode::StaticClass();
}
struct Z_Construct_UClass_Adummy_clientGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "dummy_clientGameMode.h" },
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Adummy_clientGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_Adummy_clientGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_dummy_client,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_Adummy_clientGameMode_Statics::ClassParams = {
	&Adummy_clientGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_Adummy_clientGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_Adummy_clientGameMode()
{
	if (!Z_Registration_Info_UClass_Adummy_clientGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_Adummy_clientGameMode.OuterSingleton, Z_Construct_UClass_Adummy_clientGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_Adummy_clientGameMode.OuterSingleton;
}
template<> DUMMY_CLIENT_API UClass* StaticClass<Adummy_clientGameMode>()
{
	return Adummy_clientGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(Adummy_clientGameMode);
Adummy_clientGameMode::~Adummy_clientGameMode() {}
// End Class Adummy_clientGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_Adummy_clientGameMode, Adummy_clientGameMode::StaticClass, TEXT("Adummy_clientGameMode"), &Z_Registration_Info_UClass_Adummy_clientGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(Adummy_clientGameMode), 579279744U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_937183622(TEXT("/Script/dummy_client"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
