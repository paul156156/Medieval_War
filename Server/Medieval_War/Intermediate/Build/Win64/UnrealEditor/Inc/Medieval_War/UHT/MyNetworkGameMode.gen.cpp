// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Medieval_War/MyNetworkGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyNetworkGameMode() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AMyNetworkGameMode();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AMyNetworkGameMode_NoRegister();
MEDIEVAL_WAR_API UClass* Z_Construct_UClass_AOtherCharacter_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPlayerState();
UPackage* Z_Construct_UPackage__Script_Medieval_War();
// End Cross Module References

// Begin Class AMyNetworkGameMode Function ConnectToServer
struct Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "ConnectToServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execConnectToServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ConnectToServer();
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function ConnectToServer

// Begin Class AMyNetworkGameMode Function DisconnectFromServer
struct Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function DisconnectFromServer

// Begin Class AMyNetworkGameMode Function OnCharacterStateChanged
struct Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics
{
	struct MyNetworkGameMode_eventOnCharacterStateChanged_Parms
	{
		EPlayerState NewState;
		FVector Position;
		FRotator Rotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_NewState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnCharacterStateChanged_Parms, NewState), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnCharacterStateChanged_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnCharacterStateChanged_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_NewState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_NewState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::NewProp_Rotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnCharacterStateChanged", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::MyNetworkGameMode_eventOnCharacterStateChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::MyNetworkGameMode_eventOnCharacterStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execOnCharacterStateChanged)
{
	P_GET_ENUM(EPlayerState,Z_Param_NewState);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnCharacterStateChanged(EPlayerState(Z_Param_NewState),Z_Param_Out_Position,Z_Param_Out_Rotation);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function OnCharacterStateChanged

// Begin Class AMyNetworkGameMode Function OnClientIdReceived
struct Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics
{
	struct MyNetworkGameMode_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnClientIdReceived", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::MyNetworkGameMode_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::MyNetworkGameMode_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execOnClientIdReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClientIdReceived(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function OnClientIdReceived

// Begin Class AMyNetworkGameMode Function OnConnectionStatusChanged
struct Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics
{
	struct MyNetworkGameMode_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((MyNetworkGameMode_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyNetworkGameMode_eventOnConnectionStatusChanged_Parms), &Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnConnectionStatusChanged", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::MyNetworkGameMode_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::MyNetworkGameMode_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execOnConnectionStatusChanged)
{
	P_GET_UBOOL(Z_Param_IsConnected);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnConnectionStatusChanged(Z_Param_IsConnected);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function OnConnectionStatusChanged

// Begin Class AMyNetworkGameMode Function OnPlayerUpdateReceived
struct Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics
{
	struct MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FRotator Rotation;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xda\xb5\xe9\xb7\xaf\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xda\xb5\xe9\xb7\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnPlayerUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::MyNetworkGameMode_eventOnPlayerUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execOnPlayerUpdateReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPlayerUpdateReceived(Z_Param_ClientId,Z_Param_Out_Position,Z_Param_Out_Rotation,EPlayerState(Z_Param_State));
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function OnPlayerUpdateReceived

// Begin Class AMyNetworkGameMode Function OnServerConnected
static const FName NAME_AMyNetworkGameMode_OnServerConnected = FName(TEXT("OnServerConnected"));
void AMyNetworkGameMode::OnServerConnected()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyNetworkGameMode_OnServerConnected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnServerConnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AMyNetworkGameMode Function OnServerConnected

// Begin Class AMyNetworkGameMode Function OnServerConnectionFailed
static const FName NAME_AMyNetworkGameMode_OnServerConnectionFailed = FName(TEXT("OnServerConnectionFailed"));
void AMyNetworkGameMode::OnServerConnectionFailed()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyNetworkGameMode_OnServerConnectionFailed);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnServerConnectionFailed", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AMyNetworkGameMode Function OnServerConnectionFailed

// Begin Class AMyNetworkGameMode Function OnServerDisconnected
static const FName NAME_AMyNetworkGameMode_OnServerDisconnected = FName(TEXT("OnServerDisconnected"));
void AMyNetworkGameMode::OnServerDisconnected()
{
	UFunction* Func = FindFunctionChecked(NAME_AMyNetworkGameMode_OnServerDisconnected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "OnServerDisconnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AMyNetworkGameMode Function OnServerDisconnected

// Begin Class AMyNetworkGameMode
void AMyNetworkGameMode::StaticRegisterNativesAMyNetworkGameMode()
{
	UClass* Class = AMyNetworkGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &AMyNetworkGameMode::execConnectToServer },
		{ "DisconnectFromServer", &AMyNetworkGameMode::execDisconnectFromServer },
		{ "OnCharacterStateChanged", &AMyNetworkGameMode::execOnCharacterStateChanged },
		{ "OnClientIdReceived", &AMyNetworkGameMode::execOnClientIdReceived },
		{ "OnConnectionStatusChanged", &AMyNetworkGameMode::execOnConnectionStatusChanged },
		{ "OnPlayerUpdateReceived", &AMyNetworkGameMode::execOnPlayerUpdateReceived },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AMyNetworkGameMode);
UClass* Z_Construct_UClass_AMyNetworkGameMode_NoRegister()
{
	return AMyNetworkGameMode::StaticClass();
}
struct Z_Construct_UClass_AMyNetworkGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "MyNetworkGameMode.h" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIP_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerPort_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoConnect_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xda\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xda\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ServerPort;
	static void NewProp_bAutoConnect_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoConnect;
	static const UECodeGen_Private::FClassPropertyParams NewProp_OtherPlayerCharacterClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer, "ConnectToServer" }, // 2024256344
		{ &Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer, "DisconnectFromServer" }, // 3555494777
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnCharacterStateChanged, "OnCharacterStateChanged" }, // 2976614242
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnClientIdReceived, "OnClientIdReceived" }, // 477209855
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnConnectionStatusChanged, "OnConnectionStatusChanged" }, // 1768829256
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnPlayerUpdateReceived, "OnPlayerUpdateReceived" }, // 2701129786
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnected, "OnServerConnected" }, // 3374502201
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnServerConnectionFailed, "OnServerConnectionFailed" }, // 658562004
		{ &Z_Construct_UFunction_AMyNetworkGameMode_OnServerDisconnected, "OnServerDisconnected" }, // 529578293
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyNetworkGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, NetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, ServerIP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIP_MetaData), NewProp_ServerIP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerPort = { "ServerPort", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, ServerPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerPort_MetaData), NewProp_ServerPort_MetaData) };
void Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit(void* Obj)
{
	((AMyNetworkGameMode*)Obj)->bAutoConnect = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect = { "bAutoConnect", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMyNetworkGameMode), &Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoConnect_MetaData), NewProp_bAutoConnect_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0024080000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AOtherCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerIP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayerCharacterClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyNetworkGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Medieval_War,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyNetworkGameMode_Statics::ClassParams = {
	&AMyNetworkGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers),
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyNetworkGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AMyNetworkGameMode()
{
	if (!Z_Registration_Info_UClass_AMyNetworkGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyNetworkGameMode.OuterSingleton, Z_Construct_UClass_AMyNetworkGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyNetworkGameMode.OuterSingleton;
}
template<> MEDIEVAL_WAR_API UClass* StaticClass<AMyNetworkGameMode>()
{
	return AMyNetworkGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyNetworkGameMode);
AMyNetworkGameMode::~AMyNetworkGameMode() {}
// End Class AMyNetworkGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyNetworkGameMode, AMyNetworkGameMode::StaticClass, TEXT("AMyNetworkGameMode"), &Z_Registration_Info_UClass_AMyNetworkGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyNetworkGameMode), 1193228668U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_2905507332(TEXT("/Script/Medieval_War"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
