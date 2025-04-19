// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/Public/GamePlay/MyPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyPlayerController() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
MYPROJECT_API UClass* Z_Construct_UClass_AMyPlayerController();
MYPROJECT_API UClass* Z_Construct_UClass_AMyPlayerController_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
// End Cross Module References

// Begin Class AMyPlayerController
void AMyPlayerController::StaticRegisterNativesAMyPlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyPlayerController);
UClass* Z_Construct_UClass_AMyPlayerController_NoRegister()
{
	return AMyPlayerController::StaticClass();
}
struct Z_Construct_UClass_AMyPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "GamePlay/MyPlayerController.h" },
		{ "ModuleRelativePath", "Public/GamePlay/MyPlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AMyPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyPlayerController_Statics::ClassParams = {
	&AMyPlayerController::StaticClass,
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
	0x008002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyPlayerController()
{
	if (!Z_Registration_Info_UClass_AMyPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyPlayerController.OuterSingleton, Z_Construct_UClass_AMyPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyPlayerController.OuterSingleton;
}
template<> MYPROJECT_API UClass* StaticClass<AMyPlayerController>()
{
	return AMyPlayerController::StaticClass();
}
AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyPlayerController);
AMyPlayerController::~AMyPlayerController() {}
// End Class AMyPlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Public_GamePlay_MyPlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyPlayerController, AMyPlayerController::StaticClass, TEXT("AMyPlayerController"), &Z_Registration_Info_UClass_AMyPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyPlayerController), 720882926U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Public_GamePlay_MyPlayerController_h_3668384743(TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Public_GamePlay_MyPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Public_GamePlay_MyPlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
