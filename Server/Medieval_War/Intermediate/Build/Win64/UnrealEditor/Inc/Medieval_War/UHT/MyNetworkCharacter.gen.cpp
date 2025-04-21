// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Medieval_War/MyNetworkCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyNetworkCharacter() {}

// Begin Cross Module References
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AMyNetworkCharacter();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AMyNetworkCharacter_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_ASimpleNetworkCharacter();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_UNetworkPlayerComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_Medieval_War();
// End Cross Module References

// Begin Class AMyNetworkCharacter Function ConnectToServer
struct Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics
{
	struct MyNetworkCharacter_eventConnectToServer_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((MyNetworkCharacter_eventConnectToServer_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyNetworkCharacter_eventConnectToServer_Parms), &Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkCharacter, nullptr, "ConnectToServer", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::MyNetworkCharacter_eventConnectToServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::MyNetworkCharacter_eventConnectToServer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkCharacter::execConnectToServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ConnectToServer();
	P_NATIVE_END;
}
// End Class AMyNetworkCharacter Function ConnectToServer

// Begin Class AMyNetworkCharacter Function DisconnectFromServer
struct Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkCharacter, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkCharacter::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class AMyNetworkCharacter Function DisconnectFromServer

// Begin Class AMyNetworkCharacter
void AMyNetworkCharacter::StaticRegisterNativesAMyNetworkCharacter()
{
	UClass* Class = AMyNetworkCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &AMyNetworkCharacter::execConnectToServer },
		{ "DisconnectFromServer", &AMyNetworkCharacter::execDisconnectFromServer },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyNetworkCharacter);
UClass* Z_Construct_UClass_AMyNetworkCharacter_NoRegister()
{
	return AMyNetworkCharacter::StaticClass();
}
struct Z_Construct_UClass_AMyNetworkCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MyNetworkCharacter.h" },
		{ "ModuleRelativePath", "MyNetworkCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkComponent_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer, "ConnectToServer" }, // 1889716876
		{ &Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer, "DisconnectFromServer" }, // 3627669527
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyNetworkCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_NetworkComponent = { "NetworkComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkCharacter, NetworkComponent), Z_Construct_UClass_UNetworkPlayerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkComponent_MetaData), NewProp_NetworkComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_NetworkComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyNetworkCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ASimpleNetworkCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Medieval_War,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyNetworkCharacter_Statics::ClassParams = {
	&AMyNetworkCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyNetworkCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyNetworkCharacter()
{
	if (!Z_Registration_Info_UClass_AMyNetworkCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyNetworkCharacter.OuterSingleton, Z_Construct_UClass_AMyNetworkCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyNetworkCharacter.OuterSingleton;
}
template<> MEDIEVAL_WAR_API UClass* StaticClass<AMyNetworkCharacter>()
{
	return AMyNetworkCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyNetworkCharacter);
AMyNetworkCharacter::~AMyNetworkCharacter() {}
// End Class AMyNetworkCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyNetworkCharacter, AMyNetworkCharacter::StaticClass, TEXT("AMyNetworkCharacter"), &Z_Registration_Info_UClass_AMyNetworkCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyNetworkCharacter), 1715675025U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_3284018129(TEXT("/Script/Medieval_War"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
