// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Dummy/MyNetworkGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyNetworkGameMode() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DUMMY_API UClass* Z_Construct_UClass_AMyCharacter_NoRegister();
DUMMY_API UClass* Z_Construct_UClass_AMyNetworkGameMode();
DUMMY_API UClass* Z_Construct_UClass_AMyNetworkGameMode_NoRegister();
DUMMY_API UClass* Z_Construct_UClass_AOtherCharacter_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkReplicator_NoRegister();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPlayerState();
UPackage* Z_Construct_UPackage__Script_Dummy();
// End Cross Module References

// Begin Class AMyNetworkGameMode Function ConnectToServer
struct Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "ConnectToServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer_Statics::Function_MetaDataParams) };
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
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer_Statics::Function_MetaDataParams) };
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

// Begin Class AMyNetworkGameMode Function HandleClientIdAssigned
struct Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics
{
	struct MyNetworkGameMode_eventHandleClientIdAssigned_Parms
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandleClientIdAssigned_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "HandleClientIdAssigned", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::MyNetworkGameMode_eventHandleClientIdAssigned_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::MyNetworkGameMode_eventHandleClientIdAssigned_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execHandleClientIdAssigned)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleClientIdAssigned(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function HandleClientIdAssigned

// Begin Class AMyNetworkGameMode Function HandleInitialPositionReceived
struct Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics
{
	struct MyNetworkGameMode_eventHandleInitialPositionReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FVector Velocity;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandleInitialPositionReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandleInitialPositionReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandleInitialPositionReceived_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandleInitialPositionReceived_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "HandleInitialPositionReceived", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::MyNetworkGameMode_eventHandleInitialPositionReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00880401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::MyNetworkGameMode_eventHandleInitialPositionReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execHandleInitialPositionReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT(FVector,Z_Param_Position);
	P_GET_STRUCT(FVector,Z_Param_Velocity);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleInitialPositionReceived(Z_Param_ClientId,Z_Param_Position,Z_Param_Velocity,EPlayerState(Z_Param_State));
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function HandleInitialPositionReceived

// Begin Class AMyNetworkGameMode Function HandlePlayerDisconnected
struct Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics
{
	struct MyNetworkGameMode_eventHandlePlayerDisconnected_Parms
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerDisconnected_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "HandlePlayerDisconnected", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::MyNetworkGameMode_eventHandlePlayerDisconnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::MyNetworkGameMode_eventHandlePlayerDisconnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execHandlePlayerDisconnected)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandlePlayerDisconnected(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function HandlePlayerDisconnected

// Begin Class AMyNetworkGameMode Function HandlePlayerPositionUpdated
struct Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics
{
	struct MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms
	{
		int32 ClientId;
		FVector Position;
		float Yaw;
		float Roll;
		FVector Velocity;
		EPlayerState State;
		float Timestamp;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Yaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Roll;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Roll = { "Roll", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, Roll), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms, Timestamp), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Roll,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::NewProp_Timestamp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkGameMode, nullptr, "HandlePlayerPositionUpdated", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00880401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::MyNetworkGameMode_eventHandlePlayerPositionUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkGameMode::execHandlePlayerPositionUpdated)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT(FVector,Z_Param_Position);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Roll);
	P_GET_STRUCT(FVector,Z_Param_Velocity);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Timestamp);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandlePlayerPositionUpdated(Z_Param_ClientId,Z_Param_Position,Z_Param_Yaw,Z_Param_Roll,Z_Param_Velocity,EPlayerState(Z_Param_State),Z_Param_Timestamp);
	P_NATIVE_END;
}
// End Class AMyNetworkGameMode Function HandlePlayerPositionUpdated

// Begin Class AMyNetworkGameMode
void AMyNetworkGameMode::StaticRegisterNativesAMyNetworkGameMode()
{
	UClass* Class = AMyNetworkGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &AMyNetworkGameMode::execConnectToServer },
		{ "DisconnectFromServer", &AMyNetworkGameMode::execDisconnectFromServer },
		{ "HandleClientIdAssigned", &AMyNetworkGameMode::execHandleClientIdAssigned },
		{ "HandleInitialPositionReceived", &AMyNetworkGameMode::execHandleInitialPositionReceived },
		{ "HandlePlayerDisconnected", &AMyNetworkGameMode::execHandlePlayerDisconnected },
		{ "HandlePlayerPositionUpdated", &AMyNetworkGameMode::execHandlePlayerPositionUpdated },
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
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkReplicator_MetaData[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeferredCharacter_MetaData[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayers_MetaData[] = {
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerIP_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ServerPort_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoConnect_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "MyNetworkGameMode.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkReplicator;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DeferredCharacter;
	static const UECodeGen_Private::FClassPropertyParams NewProp_OtherPlayerCharacterClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayers_ValueProp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherPlayers_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_OtherPlayers;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ServerIP;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ServerPort;
	static void NewProp_bAutoConnect_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoConnect;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyNetworkGameMode_ConnectToServer, "ConnectToServer" }, // 3206952605
		{ &Z_Construct_UFunction_AMyNetworkGameMode_DisconnectFromServer, "DisconnectFromServer" }, // 3165441063
		{ &Z_Construct_UFunction_AMyNetworkGameMode_HandleClientIdAssigned, "HandleClientIdAssigned" }, // 1500598270
		{ &Z_Construct_UFunction_AMyNetworkGameMode_HandleInitialPositionReceived, "HandleInitialPositionReceived" }, // 859641385
		{ &Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerDisconnected, "HandlePlayerDisconnected" }, // 937120115
		{ &Z_Construct_UFunction_AMyNetworkGameMode_HandlePlayerPositionUpdated, "HandlePlayerPositionUpdated" }, // 696218226
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyNetworkGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, NetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkReplicator = { "NetworkReplicator", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, NetworkReplicator), Z_Construct_UClass_USimpleNetworkReplicator_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkReplicator_MetaData), NewProp_NetworkReplicator_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_DeferredCharacter = { "DeferredCharacter", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, DeferredCharacter), Z_Construct_UClass_AMyCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeferredCharacter_MetaData), NewProp_DeferredCharacter_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AOtherCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers_ValueProp = { "OtherPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_AOtherCharacter_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers_Key_KeyProp = { "OtherPlayers_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers = { "OtherPlayers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, OtherPlayers), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayers_MetaData), NewProp_OtherPlayers_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerIP = { "ServerIP", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, ServerIP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerIP_MetaData), NewProp_ServerIP_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerPort = { "ServerPort", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkGameMode, ServerPort), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ServerPort_MetaData), NewProp_ServerPort_MetaData) };
void Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit(void* Obj)
{
	((AMyNetworkGameMode*)Obj)->bAutoConnect = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect = { "bAutoConnect", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMyNetworkGameMode), &Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoConnect_MetaData), NewProp_bAutoConnect_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_NetworkReplicator,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_DeferredCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayerCharacterClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_OtherPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerIP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_ServerPort,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkGameMode_Statics::NewProp_bAutoConnect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyNetworkGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Dummy,
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
template<> DUMMY_API UClass* StaticClass<AMyNetworkGameMode>()
{
	return AMyNetworkGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyNetworkGameMode);
AMyNetworkGameMode::~AMyNetworkGameMode() {}
// End Class AMyNetworkGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyNetworkGameMode, AMyNetworkGameMode::StaticClass, TEXT("AMyNetworkGameMode"), &Z_Registration_Info_UClass_AMyNetworkGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyNetworkGameMode), 404916122U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_3508946907(TEXT("/Script/Dummy"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
