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
DUMMY_CLIENT_API UClass* Z_Construct_UClass_UNetworkManager_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_dummy_client();
// End Cross Module References

// Begin Class Adummy_clientGameMode Function GetNetworkManager
struct Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics
{
	struct dummy_clientGameMode_eventGetNetworkManager_Parms
	{
		UNetworkManager* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientGameMode_eventGetNetworkManager_Parms, ReturnValue), Z_Construct_UClass_UNetworkManager_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientGameMode, nullptr, "GetNetworkManager", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::dummy_clientGameMode_eventGetNetworkManager_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::dummy_clientGameMode_eventGetNetworkManager_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientGameMode::execGetNetworkManager)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UNetworkManager**)Z_Param__Result=P_THIS->GetNetworkManager();
	P_NATIVE_END;
}
// End Class Adummy_clientGameMode Function GetNetworkManager

// Begin Class Adummy_clientGameMode
void Adummy_clientGameMode::StaticRegisterNativesAdummy_clientGameMode()
{
	UClass* Class = Adummy_clientGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetNetworkManager", &Adummy_clientGameMode::execGetNetworkManager },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xce\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xce\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIP_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd IP \xef\xbf\xbd\xd6\xbc\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd IP \xef\xbf\xbd\xd6\xbc\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerPort_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoConnect_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xda\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xda\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ServerPort;
	static void NewProp_bAutoConnect_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoConnect;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_Adummy_clientGameMode_GetNetworkManager, "GetNetworkManager" }, // 3523174705
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Adummy_clientGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientGameMode, NetworkManager), Z_Construct_UClass_UNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientGameMode, ServerIP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIP_MetaData), NewProp_ServerIP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_ServerPort = { "ServerPort", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientGameMode, ServerPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerPort_MetaData), NewProp_ServerPort_MetaData) };
void Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_bAutoConnect_SetBit(void* Obj)
{
	((Adummy_clientGameMode*)Obj)->bAutoConnect = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_bAutoConnect = { "bAutoConnect", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(Adummy_clientGameMode), &Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_bAutoConnect_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoConnect_MetaData), NewProp_bAutoConnect_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_Adummy_clientGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_ServerIP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_ServerPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientGameMode_Statics::NewProp_bAutoConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientGameMode_Statics::PropPointers) < 2048);
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
	FuncInfo,
	Z_Construct_UClass_Adummy_clientGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientGameMode_Statics::PropPointers),
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
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_Adummy_clientGameMode, Adummy_clientGameMode::StaticClass, TEXT("Adummy_clientGameMode"), &Z_Registration_Info_UClass_Adummy_clientGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(Adummy_clientGameMode), 1399861483U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_1939491892(TEXT("/Script/dummy_client"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
