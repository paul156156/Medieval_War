// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Medieval_War/OtherCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOtherCharacter() {}

// Begin Cross Module References
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AMyCharacter();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AOtherCharacter();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AOtherCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_Medieval_War();
// End Cross Module References

// Begin Class AOtherCharacter
void AOtherCharacter::StaticRegisterNativesAOtherCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AOtherCharacter);
UClass* Z_Construct_UClass_AOtherCharacter_NoRegister()
{
	return AOtherCharacter::StaticClass();
}
struct Z_Construct_UClass_AOtherCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "OtherCharacter.h" },
		{ "ModuleRelativePath", "OtherCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AOtherCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AOtherCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AMyCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Medieval_War,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AOtherCharacter_Statics::ClassParams = {
	&AOtherCharacter::StaticClass,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AOtherCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AOtherCharacter()
{
	if (!Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton, Z_Construct_UClass_AOtherCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton;
}
template<> MEDIEVAL_WAR_API UClass* StaticClass<AOtherCharacter>()
{
	return AOtherCharacter::StaticClass();
}
AOtherCharacter::AOtherCharacter() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AOtherCharacter);
AOtherCharacter::~AOtherCharacter() {}
// End Class AOtherCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AOtherCharacter, AOtherCharacter::StaticClass, TEXT("AOtherCharacter"), &Z_Registration_Info_UClass_AOtherCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AOtherCharacter), 276763800U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_1753996666(TEXT("/Script/Medieval_War"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
