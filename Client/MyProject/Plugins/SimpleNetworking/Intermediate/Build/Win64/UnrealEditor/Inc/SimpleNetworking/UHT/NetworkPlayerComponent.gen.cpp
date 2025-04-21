// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkPlayerComponent() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_UNetworkPlayerComponent();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_UNetworkPlayerComponent_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
SIMPLENETWORKING_API UScriptStruct* Z_Construct_UScriptStruct_FOtherPlayerInfo();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Class UNetworkPlayerComponent Function ConnectToServer
struct Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics
{
	struct NetworkPlayerComponent_eventConnectToServer_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((NetworkPlayerComponent_eventConnectToServer_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkPlayerComponent_eventConnectToServer_Parms), &Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "ConnectToServer", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NetworkPlayerComponent_eventConnectToServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::NetworkPlayerComponent_eventConnectToServer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execConnectToServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ConnectToServer();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function ConnectToServer

// Begin Class UNetworkPlayerComponent Function DisconnectFromServer
struct Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c \xed\x95\xa8\xec\x88\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function DisconnectFromServer

// Begin Class UNetworkPlayerComponent Function GetLocalClientId
struct Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics
{
	struct NetworkPlayerComponent_eventGetLocalClientId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x98\x84\xec\x9e\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xeb\xb0\x98\xed\x99\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x98\x84\xec\x9e\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xeb\xb0\x98\xed\x99\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventGetLocalClientId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "GetLocalClientId", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::NetworkPlayerComponent_eventGetLocalClientId_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::NetworkPlayerComponent_eventGetLocalClientId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execGetLocalClientId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLocalClientId();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function GetLocalClientId

// Begin Class UNetworkPlayerComponent Function GetOtherPlayerCount
struct Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics
{
	struct NetworkPlayerComponent_eventGetOtherPlayerCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xea\xb0\x9c\xec\x88\x98 \xeb\xb0\x98\xed\x99\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xea\xb0\x9c\xec\x88\x98 \xeb\xb0\x98\xed\x99\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventGetOtherPlayerCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "GetOtherPlayerCount", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::NetworkPlayerComponent_eventGetOtherPlayerCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::NetworkPlayerComponent_eventGetOtherPlayerCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execGetOtherPlayerCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetOtherPlayerCount();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function GetOtherPlayerCount

// Begin Class UNetworkPlayerComponent Function OnClientIdReceived
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics
{
	struct NetworkPlayerComponent_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnClientIdReceived", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::NetworkPlayerComponent_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::NetworkPlayerComponent_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnClientIdReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClientIdReceived(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnClientIdReceived

// Begin Class UNetworkPlayerComponent Function OnConnectionStatusChanged
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics
{
	struct NetworkPlayerComponent_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((NetworkPlayerComponent_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkPlayerComponent_eventOnConnectionStatusChanged_Parms), &Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnConnectionStatusChanged", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NetworkPlayerComponent_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::NetworkPlayerComponent_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnConnectionStatusChanged)
{
	P_GET_UBOOL(Z_Param_IsConnected);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnConnectionStatusChanged(Z_Param_IsConnected);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnConnectionStatusChanged

// Begin Class UNetworkPlayerComponent Function OnJumpStateUpdateReceived
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics
{
	struct NetworkPlayerComponent_eventOnJumpStateUpdateReceived_Parms
	{
		bool IsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((NetworkPlayerComponent_eventOnJumpStateUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkPlayerComponent_eventOnJumpStateUpdateReceived_Parms), &Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnJumpStateUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NetworkPlayerComponent_eventOnJumpStateUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::NetworkPlayerComponent_eventOnJumpStateUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnJumpStateUpdateReceived)
{
	P_GET_UBOOL(Z_Param_IsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnJumpStateUpdateReceived(Z_Param_IsJumping);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnJumpStateUpdateReceived

// Begin Class UNetworkPlayerComponent Function OnNetworkConnected
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnNetworkConnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnNetworkConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnNetworkConnected();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnNetworkConnected

// Begin Class UNetworkPlayerComponent Function OnNetworkDisconnected
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnNetworkDisconnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnNetworkDisconnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnNetworkDisconnected();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnNetworkDisconnected

// Begin Class UNetworkPlayerComponent Function OnOtherPlayerRemoved
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics
{
	struct NetworkPlayerComponent_eventOnOtherPlayerRemoved_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnOtherPlayerRemoved_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnOtherPlayerRemoved", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::NetworkPlayerComponent_eventOnOtherPlayerRemoved_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::NetworkPlayerComponent_eventOnOtherPlayerRemoved_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnOtherPlayerRemoved)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOtherPlayerRemoved(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnOtherPlayerRemoved

// Begin Class UNetworkPlayerComponent Function OnOtherPlayerSpawned
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics
{
	struct NetworkPlayerComponent_eventOnOtherPlayerSpawned_Parms
	{
		AActor* OtherPlayerActor;
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayerActor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor = { "OtherPlayerActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnOtherPlayerSpawned_Parms, OtherPlayerActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnOtherPlayerSpawned_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnOtherPlayerSpawned", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NetworkPlayerComponent_eventOnOtherPlayerSpawned_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::NetworkPlayerComponent_eventOnOtherPlayerSpawned_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnOtherPlayerSpawned)
{
	P_GET_OBJECT(AActor,Z_Param_OtherPlayerActor);
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOtherPlayerSpawned(Z_Param_OtherPlayerActor,Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnOtherPlayerSpawned

// Begin Class UNetworkPlayerComponent Function OnPlayerUpdateReceived
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics
{
	struct NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FRotator Rotation;
		FVector Velocity;
		bool IsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
void Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms), &Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnPlayerUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::NetworkPlayerComponent_eventOnPlayerUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnPlayerUpdateReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Velocity);
	P_GET_UBOOL(Z_Param_IsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPlayerUpdateReceived(Z_Param_ClientId,Z_Param_Out_Position,Z_Param_Out_Rotation,Z_Param_Out_Velocity,Z_Param_IsJumping);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnPlayerUpdateReceived

// Begin Class UNetworkPlayerComponent Function OnPositionUpdateReceived
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics
{
	struct NetworkPlayerComponent_eventOnPositionUpdateReceived_Parms
	{
		FVector NewPosition;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa0\x88\xea\xb1\xb0\xec\x8b\x9c \xed\x8c\xa8\xed\x82\xb7 \xed\x95\xb8\xeb\x93\xa4\xeb\x9f\xac (\xed\x98\xb8\xed\x99\x98\xec\x84\xb1 \xec\x9c\xa0\xec\xa7\x80)\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa0\x88\xea\xb1\xb0\xec\x8b\x9c \xed\x8c\xa8\xed\x82\xb7 \xed\x95\xb8\xeb\x93\xa4\xeb\x9f\xac (\xed\x98\xb8\xed\x99\x98\xec\x84\xb1 \xec\x9c\xa0\xec\xa7\x80)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewPosition_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewPosition;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnPositionUpdateReceived_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::NewProp_NewPosition,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnPositionUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::NetworkPlayerComponent_eventOnPositionUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C40401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::NetworkPlayerComponent_eventOnPositionUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnPositionUpdateReceived)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_NewPosition);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPositionUpdateReceived(Z_Param_Out_NewPosition);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnPositionUpdateReceived

// Begin Class UNetworkPlayerComponent Function OnRotationUpdateReceived
struct Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics
{
	struct NetworkPlayerComponent_eventOnRotationUpdateReceived_Parms
	{
		FRotator NewRotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewRotation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventOnRotationUpdateReceived_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRotation_MetaData), NewProp_NewRotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::NewProp_NewRotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "OnRotationUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::NetworkPlayerComponent_eventOnRotationUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C40401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::NetworkPlayerComponent_eventOnRotationUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execOnRotationUpdateReceived)
{
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_NewRotation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRotationUpdateReceived(Z_Param_Out_NewRotation);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function OnRotationUpdateReceived

// Begin Class UNetworkPlayerComponent Function RemoveAllOtherPlayers
struct Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xaa\xa8\xeb\x93\xa0 \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xaa\xa8\xeb\x93\xa0 \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "RemoveAllOtherPlayers", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execRemoveAllOtherPlayers)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOtherPlayers();
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function RemoveAllOtherPlayers

// Begin Class UNetworkPlayerComponent Function RemoveOtherPlayerCharacter
struct Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics
{
	struct NetworkPlayerComponent_eventRemoveOtherPlayerCharacter_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\xa0\x9c\xea\xb1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\xa0\x9c\xea\xb1\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventRemoveOtherPlayerCharacter_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "RemoveOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::NetworkPlayerComponent_eventRemoveOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::NetworkPlayerComponent_eventRemoveOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execRemoveOtherPlayerCharacter)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveOtherPlayerCharacter(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function RemoveOtherPlayerCharacter

// Begin Class UNetworkPlayerComponent Function SendJumpState
struct Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics
{
	struct NetworkPlayerComponent_eventSendJumpState_Parms
	{
		bool bIsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xa0\x90\xed\x94\x84 \xec\x83\x81\xed\x83\x9c \xec\xa0\x84\xec\x86\xa1 \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xa0\x90\xed\x94\x84 \xec\x83\x81\xed\x83\x9c \xec\xa0\x84\xec\x86\xa1 \xed\x95\xa8\xec\x88\x98" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bIsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NewProp_bIsJumping_SetBit(void* Obj)
{
	((NetworkPlayerComponent_eventSendJumpState_Parms*)Obj)->bIsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NewProp_bIsJumping = { "bIsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkPlayerComponent_eventSendJumpState_Parms), &Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NewProp_bIsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NewProp_bIsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "SendJumpState", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NetworkPlayerComponent_eventSendJumpState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::NetworkPlayerComponent_eventSendJumpState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execSendJumpState)
{
	P_GET_UBOOL(Z_Param_bIsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendJumpState(Z_Param_bIsJumping);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function SendJumpState

// Begin Class UNetworkPlayerComponent Function SetNetworkManager
struct Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics
{
	struct NetworkPlayerComponent_eventSetNetworkManager_Parms
	{
		USimpleNetworkManager* InNetworkManager;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\x84\xa4\xec\xa0\x95\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\x84\xa4\xec\xa0\x95" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InNetworkManager;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::NewProp_InNetworkManager = { "InNetworkManager", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventSetNetworkManager_Parms, InNetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::NewProp_InNetworkManager,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "SetNetworkManager", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::NetworkPlayerComponent_eventSetNetworkManager_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::NetworkPlayerComponent_eventSetNetworkManager_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execSetNetworkManager)
{
	P_GET_OBJECT(USimpleNetworkManager,Z_Param_InNetworkManager);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetNetworkManager(Z_Param_InNetworkManager);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function SetNetworkManager

// Begin Class UNetworkPlayerComponent Function SpawnOtherPlayerCharacter
struct Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics
{
	struct NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms
	{
		FVector Position;
		int32 InClientId;
		AActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\x8a\xa4\xed\x8f\xb0\n" },
#endif
		{ "CPP_Default_InClientId", "-1" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\x8a\xa4\xed\x8f\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FIntPropertyParams NewProp_InClientId;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId = { "InClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms, InClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkPlayerComponent, nullptr, "SpawnOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::NetworkPlayerComponent_eventSpawnOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkPlayerComponent::execSpawnOtherPlayerCharacter)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_PROPERTY(FIntProperty,Z_Param_InClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AActor**)Z_Param__Result=P_THIS->SpawnOtherPlayerCharacter(Z_Param_Out_Position,Z_Param_InClientId);
	P_NATIVE_END;
}
// End Class UNetworkPlayerComponent Function SpawnOtherPlayerCharacter

// Begin Class UNetworkPlayerComponent
void UNetworkPlayerComponent::StaticRegisterNativesUNetworkPlayerComponent()
{
	UClass* Class = UNetworkPlayerComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &UNetworkPlayerComponent::execConnectToServer },
		{ "DisconnectFromServer", &UNetworkPlayerComponent::execDisconnectFromServer },
		{ "GetLocalClientId", &UNetworkPlayerComponent::execGetLocalClientId },
		{ "GetOtherPlayerCount", &UNetworkPlayerComponent::execGetOtherPlayerCount },
		{ "OnClientIdReceived", &UNetworkPlayerComponent::execOnClientIdReceived },
		{ "OnConnectionStatusChanged", &UNetworkPlayerComponent::execOnConnectionStatusChanged },
		{ "OnJumpStateUpdateReceived", &UNetworkPlayerComponent::execOnJumpStateUpdateReceived },
		{ "OnNetworkConnected", &UNetworkPlayerComponent::execOnNetworkConnected },
		{ "OnNetworkDisconnected", &UNetworkPlayerComponent::execOnNetworkDisconnected },
		{ "OnOtherPlayerRemoved", &UNetworkPlayerComponent::execOnOtherPlayerRemoved },
		{ "OnOtherPlayerSpawned", &UNetworkPlayerComponent::execOnOtherPlayerSpawned },
		{ "OnPlayerUpdateReceived", &UNetworkPlayerComponent::execOnPlayerUpdateReceived },
		{ "OnPositionUpdateReceived", &UNetworkPlayerComponent::execOnPositionUpdateReceived },
		{ "OnRotationUpdateReceived", &UNetworkPlayerComponent::execOnRotationUpdateReceived },
		{ "RemoveAllOtherPlayers", &UNetworkPlayerComponent::execRemoveAllOtherPlayers },
		{ "RemoveOtherPlayerCharacter", &UNetworkPlayerComponent::execRemoveOtherPlayerCharacter },
		{ "SendJumpState", &UNetworkPlayerComponent::execSendJumpState },
		{ "SetNetworkManager", &UNetworkPlayerComponent::execSetNetworkManager },
		{ "SpawnOtherPlayerCharacter", &UNetworkPlayerComponent::execSpawnOtherPlayerCharacter },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNetworkPlayerComponent);
UClass* Z_Construct_UClass_UNetworkPlayerComponent_NoRegister()
{
	return UNetworkPlayerComponent::StaticClass();
}
struct Z_Construct_UClass_UNetworkPlayerComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Networking" },
		{ "IncludePath", "NetworkPlayerComponent.h" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xb0\xb8\xec\xa1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xb0\xb8\xec\xa1\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIP_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xec\x84\xa4\xec\xa0\x95\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xec\x84\xa4\xec\xa0\x95" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerPort_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoConnectOnBeginPlay_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9e\x90\xeb\x8f\x99 \xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9e\x90\xeb\x8f\x99 \xec\x97\xb0\xea\xb2\xb0 \xec\x97\xac\xeb\xb6\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableNetworkUpdates_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xed\x99\x9c\xec\x84\xb1\xed\x99\x94\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xed\x99\x9c\xec\x84\xb1\xed\x99\x94" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionUpdateInterval_MetaData[] = {
		{ "Category", "Networking" },
		{ "ClampMin", "0.01" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9c\x84\xec\xb9\x98 \xec\xa0\x84\xec\x86\xa1 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9c\x84\xec\xb9\x98 \xec\xa0\x84\xec\x86\xa1 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalClientId_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa1\x9c\xec\xbb\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa1\x9c\xec\xbb\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayers_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xeb\xa7\xb5\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkPlayerComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xeb\xa7\xb5" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ServerPort;
	static void NewProp_bAutoConnectOnBeginPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoConnectOnBeginPlay;
	static void NewProp_bEnableNetworkUpdates_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableNetworkUpdates;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PositionUpdateInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LocalClientId;
	static const UECodeGen_Private::FClassPropertyParams NewProp_OtherPlayerCharacterClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OtherPlayers_ValueProp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayers_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_OtherPlayers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_ConnectToServer, "ConnectToServer" }, // 2049583058
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_DisconnectFromServer, "DisconnectFromServer" }, // 843942467
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_GetLocalClientId, "GetLocalClientId" }, // 3535499080
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_GetOtherPlayerCount, "GetOtherPlayerCount" }, // 2572663509
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnClientIdReceived, "OnClientIdReceived" }, // 2836123123
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnConnectionStatusChanged, "OnConnectionStatusChanged" }, // 3059034240
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnJumpStateUpdateReceived, "OnJumpStateUpdateReceived" }, // 3823580789
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkConnected, "OnNetworkConnected" }, // 1347600707
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnNetworkDisconnected, "OnNetworkDisconnected" }, // 2692256238
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerRemoved, "OnOtherPlayerRemoved" }, // 743720046
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnOtherPlayerSpawned, "OnOtherPlayerSpawned" }, // 1736179218
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnPlayerUpdateReceived, "OnPlayerUpdateReceived" }, // 4175998319
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnPositionUpdateReceived, "OnPositionUpdateReceived" }, // 4255994805
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_OnRotationUpdateReceived, "OnRotationUpdateReceived" }, // 950059930
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_RemoveAllOtherPlayers, "RemoveAllOtherPlayers" }, // 3289109988
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_RemoveOtherPlayerCharacter, "RemoveOtherPlayerCharacter" }, // 1524431677
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_SendJumpState, "SendJumpState" }, // 3049979969
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_SetNetworkManager, "SetNetworkManager" }, // 4226216976
		{ &Z_Construct_UFunction_UNetworkPlayerComponent_SpawnOtherPlayerCharacter, "SpawnOtherPlayerCharacter" }, // 2806769219
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNetworkPlayerComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, NetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, ServerIP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIP_MetaData), NewProp_ServerIP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_ServerPort = { "ServerPort", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, ServerPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerPort_MetaData), NewProp_ServerPort_MetaData) };
void Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bAutoConnectOnBeginPlay_SetBit(void* Obj)
{
	((UNetworkPlayerComponent*)Obj)->bAutoConnectOnBeginPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bAutoConnectOnBeginPlay = { "bAutoConnectOnBeginPlay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UNetworkPlayerComponent), &Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bAutoConnectOnBeginPlay_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoConnectOnBeginPlay_MetaData), NewProp_bAutoConnectOnBeginPlay_MetaData) };
void Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bEnableNetworkUpdates_SetBit(void* Obj)
{
	((UNetworkPlayerComponent*)Obj)->bEnableNetworkUpdates = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bEnableNetworkUpdates = { "bEnableNetworkUpdates", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UNetworkPlayerComponent), &Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bEnableNetworkUpdates_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableNetworkUpdates_MetaData), NewProp_bEnableNetworkUpdates_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_PositionUpdateInterval = { "PositionUpdateInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, PositionUpdateInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionUpdateInterval_MetaData), NewProp_PositionUpdateInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_LocalClientId = { "LocalClientId", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, LocalClientId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalClientId_MetaData), NewProp_LocalClientId_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers_ValueProp = { "OtherPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FOtherPlayerInfo, METADATA_PARAMS(0, nullptr) }; // 4218889607
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers_Key_KeyProp = { "OtherPlayers_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers = { "OtherPlayers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkPlayerComponent, OtherPlayers), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayers_MetaData), NewProp_OtherPlayers_MetaData) }; // 4218889607
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNetworkPlayerComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_ServerIP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_ServerPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bAutoConnectOnBeginPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_bEnableNetworkUpdates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_PositionUpdateInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_LocalClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayerCharacterClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkPlayerComponent_Statics::NewProp_OtherPlayers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkPlayerComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNetworkPlayerComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkPlayerComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNetworkPlayerComponent_Statics::ClassParams = {
	&UNetworkPlayerComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNetworkPlayerComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkPlayerComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkPlayerComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNetworkPlayerComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNetworkPlayerComponent()
{
	if (!Z_Registration_Info_UClass_UNetworkPlayerComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNetworkPlayerComponent.OuterSingleton, Z_Construct_UClass_UNetworkPlayerComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNetworkPlayerComponent.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<UNetworkPlayerComponent>()
{
	return UNetworkPlayerComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNetworkPlayerComponent);
UNetworkPlayerComponent::~UNetworkPlayerComponent() {}
// End Class UNetworkPlayerComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNetworkPlayerComponent, UNetworkPlayerComponent::StaticClass, TEXT("UNetworkPlayerComponent"), &Z_Registration_Info_UClass_UNetworkPlayerComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNetworkPlayerComponent), 2683507274U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_3602084514(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
