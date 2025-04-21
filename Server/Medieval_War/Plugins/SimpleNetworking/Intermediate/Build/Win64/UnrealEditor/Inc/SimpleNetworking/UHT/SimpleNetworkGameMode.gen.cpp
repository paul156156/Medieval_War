// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/SimpleNetworkGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworkGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_ASimpleNetworkGameMode();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_ASimpleNetworkGameMode_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Class ASimpleNetworkGameMode Function ConnectToServer
struct Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkGameMode, nullptr, "ConnectToServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkGameMode::execConnectToServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ConnectToServer();
	P_NATIVE_END;
}
// End Class ASimpleNetworkGameMode Function ConnectToServer

// Begin Class ASimpleNetworkGameMode Function DisconnectFromServer
struct Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c \xed\x95\xa8\xec\x88\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkGameMode, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkGameMode::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class ASimpleNetworkGameMode Function DisconnectFromServer

// Begin Class ASimpleNetworkGameMode Function GetNetworkManager
struct Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics
{
	struct SimpleNetworkGameMode_eventGetNetworkManager_Parms
	{
		USimpleNetworkManager* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xa0\x91\xea\xb7\xbc\xec\x9e\x90\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xa0\x91\xea\xb7\xbc\xec\x9e\x90" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkGameMode_eventGetNetworkManager_Parms, ReturnValue), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkGameMode, nullptr, "GetNetworkManager", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::SimpleNetworkGameMode_eventGetNetworkManager_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::SimpleNetworkGameMode_eventGetNetworkManager_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkGameMode::execGetNetworkManager)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USimpleNetworkManager**)Z_Param__Result=P_THIS->GetNetworkManager();
	P_NATIVE_END;
}
// End Class ASimpleNetworkGameMode Function GetNetworkManager

// Begin Class ASimpleNetworkGameMode
void ASimpleNetworkGameMode::StaticRegisterNativesASimpleNetworkGameMode()
{
	UClass* Class = ASimpleNetworkGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &ASimpleNetworkGameMode::execConnectToServer },
		{ "DisconnectFromServer", &ASimpleNetworkGameMode::execDisconnectFromServer },
		{ "GetNetworkManager", &ASimpleNetworkGameMode::execGetNetworkManager },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASimpleNetworkGameMode);
UClass* Z_Construct_UClass_ASimpleNetworkGameMode_NoRegister()
{
	return ASimpleNetworkGameMode::StaticClass();
}
struct Z_Construct_UClass_ASimpleNetworkGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "SimpleNetworkGameMode.h" },
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\x9d\xb8\xec\x8a\xa4\xed\x84\xb4\xec\x8a\xa4\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\x9d\xb8\xec\x8a\xa4\xed\x84\xb4\xec\x8a\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIP_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 IP \xec\xa3\xbc\xec\x86\x8c\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 IP \xec\xa3\xbc\xec\x86\x8c" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerPort_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xed\x8f\xac\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xed\x8f\xac\xed\x8a\xb8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoConnect_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x90\xeb\x8f\x99 \xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x90\xeb\x8f\x99 \xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoReconnect_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x97\xb0\xea\xb2\xb0 \xec\x8b\xa4\xed\x8c\xa8 \xec\x8b\x9c \xec\x9e\x90\xeb\x8f\x99 \xec\x9e\xac\xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x97\xb0\xea\xb2\xb0 \xec\x8b\xa4\xed\x8c\xa8 \xec\x8b\x9c \xec\x9e\x90\xeb\x8f\x99 \xec\x9e\xac\xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReconnectInterval_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\xac\xec\x97\xb0\xea\xb2\xb0 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)\n" },
#endif
		{ "EditCondition", "bAutoReconnect" },
		{ "ModuleRelativePath", "Public/SimpleNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\xac\xec\x97\xb0\xea\xb2\xb0 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ServerPort;
	static void NewProp_bAutoConnect_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoConnect;
	static void NewProp_bAutoReconnect_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoReconnect;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReconnectInterval;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASimpleNetworkGameMode_ConnectToServer, "ConnectToServer" }, // 1066472927
		{ &Z_Construct_UFunction_ASimpleNetworkGameMode_DisconnectFromServer, "DisconnectFromServer" }, // 1504172088
		{ &Z_Construct_UFunction_ASimpleNetworkGameMode_GetNetworkManager, "GetNetworkManager" }, // 1891921268
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASimpleNetworkGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkGameMode, NetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkGameMode, ServerIP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIP_MetaData), NewProp_ServerIP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ServerPort = { "ServerPort", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkGameMode, ServerPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerPort_MetaData), NewProp_ServerPort_MetaData) };
void Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit(void* Obj)
{
	((ASimpleNetworkGameMode*)Obj)->bAutoConnect = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoConnect = { "bAutoConnect", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASimpleNetworkGameMode), &Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoConnect_MetaData), NewProp_bAutoConnect_MetaData) };
void Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoReconnect_SetBit(void* Obj)
{
	((ASimpleNetworkGameMode*)Obj)->bAutoReconnect = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoReconnect = { "bAutoReconnect", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASimpleNetworkGameMode), &Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoReconnect_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoReconnect_MetaData), NewProp_bAutoReconnect_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ReconnectInterval = { "ReconnectInterval", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkGameMode, ReconnectInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReconnectInterval_MetaData), NewProp_ReconnectInterval_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASimpleNetworkGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ServerIP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ServerPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoConnect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_bAutoReconnect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkGameMode_Statics::NewProp_ReconnectInterval,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASimpleNetworkGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASimpleNetworkGameMode_Statics::ClassParams = {
	&ASimpleNetworkGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASimpleNetworkGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkGameMode_Statics::PropPointers),
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASimpleNetworkGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASimpleNetworkGameMode()
{
	if (!Z_Registration_Info_UClass_ASimpleNetworkGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASimpleNetworkGameMode.OuterSingleton, Z_Construct_UClass_ASimpleNetworkGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASimpleNetworkGameMode.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<ASimpleNetworkGameMode>()
{
	return ASimpleNetworkGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASimpleNetworkGameMode);
ASimpleNetworkGameMode::~ASimpleNetworkGameMode() {}
// End Class ASimpleNetworkGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASimpleNetworkGameMode, ASimpleNetworkGameMode::StaticClass, TEXT("ASimpleNetworkGameMode"), &Z_Registration_Info_UClass_ASimpleNetworkGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASimpleNetworkGameMode), 3742814551U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_2930256684(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
