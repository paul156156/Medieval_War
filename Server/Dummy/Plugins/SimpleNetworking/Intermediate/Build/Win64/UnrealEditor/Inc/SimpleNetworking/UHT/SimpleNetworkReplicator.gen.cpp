// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/SimpleNetworkReplicator.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworkReplicator() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkReplicator();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkReplicator_NoRegister();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPlayerState();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Delegate FOnClientIdAssigned
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnClientIdAssigned_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnClientIdAssigned_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnClientIdAssigned__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnClientIdAssigned_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnClientIdAssigned_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnClientIdAssigned_DelegateWrapper(const FMulticastScriptDelegate& OnClientIdAssigned, int32 ClientId)
{
	struct _Script_SimpleNetworking_eventOnClientIdAssigned_Parms
	{
		int32 ClientId;
	};
	_Script_SimpleNetworking_eventOnClientIdAssigned_Parms Parms;
	Parms.ClientId=ClientId;
	OnClientIdAssigned.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnClientIdAssigned

// Begin Delegate FOnPlayerDisconnected
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnPlayerDisconnected_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerDisconnected_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnPlayerDisconnected__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerDisconnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerDisconnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnPlayerDisconnected_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerDisconnected, int32 ClientId)
{
	struct _Script_SimpleNetworking_eventOnPlayerDisconnected_Parms
	{
		int32 ClientId;
	};
	_Script_SimpleNetworking_eventOnPlayerDisconnected_Parms Parms;
	Parms.ClientId=ClientId;
	OnPlayerDisconnected.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnPlayerDisconnected

// Begin Delegate FOnMyInitialPositionReceived
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FVector Velocity;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnMyInitialPositionReceived__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnMyInitialPositionReceived_DelegateWrapper(const FMulticastScriptDelegate& OnMyInitialPositionReceived, int32 ClientId, FVector Position, FVector Velocity, EPlayerState State)
{
	struct _Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FVector Velocity;
		EPlayerState State;
	};
	_Script_SimpleNetworking_eventOnMyInitialPositionReceived_Parms Parms;
	Parms.ClientId=ClientId;
	Parms.Position=Position;
	Parms.Velocity=Velocity;
	Parms.State=State;
	OnMyInitialPositionReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnMyInitialPositionReceived

// Begin Delegate FOnPlayerPositionUpdated
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms
	{
		int32 ClientId;
		FVector NewPosition;
		float NewYaw;
		float NewRoll;
		FVector NewVelocity;
		EPlayerState State;
		float Timestamp;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewPosition;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewYaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRoll;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewVelocity;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Timestamp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewYaw = { "NewYaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, NewYaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewRoll = { "NewRoll", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, NewRoll), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewVelocity = { "NewVelocity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, NewVelocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_Timestamp = { "Timestamp", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms, Timestamp), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewYaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewRoll,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_NewVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_State,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::NewProp_Timestamp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnPlayerPositionUpdated__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnPlayerPositionUpdated_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerPositionUpdated, int32 ClientId, FVector NewPosition, float NewYaw, float NewRoll, FVector NewVelocity, EPlayerState State, float Timestamp)
{
	struct _Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms
	{
		int32 ClientId;
		FVector NewPosition;
		float NewYaw;
		float NewRoll;
		FVector NewVelocity;
		EPlayerState State;
		float Timestamp;
	};
	_Script_SimpleNetworking_eventOnPlayerPositionUpdated_Parms Parms;
	Parms.ClientId=ClientId;
	Parms.NewPosition=NewPosition;
	Parms.NewYaw=NewYaw;
	Parms.NewRoll=NewRoll;
	Parms.NewVelocity=NewVelocity;
	Parms.State=State;
	Parms.Timestamp=Timestamp;
	OnPlayerPositionUpdated.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnPlayerPositionUpdated

// Begin Class USimpleNetworkReplicator
void USimpleNetworkReplicator::StaticRegisterNativesUSimpleNetworkReplicator()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USimpleNetworkReplicator);
UClass* Z_Construct_UClass_USimpleNetworkReplicator_NoRegister()
{
	return USimpleNetworkReplicator::StaticClass();
}
struct Z_Construct_UClass_USimpleNetworkReplicator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SimpleNetworkReplicator.h" },
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnClientIdAssigned_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnPlayerDisconnected_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnPlayerPositionUpdated_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnMyInitialPositionReceived_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkReplicator.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnClientIdAssigned;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPlayerDisconnected;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPlayerPositionUpdated;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnMyInitialPositionReceived;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USimpleNetworkReplicator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnClientIdAssigned = { "OnClientIdAssigned", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkReplicator, OnClientIdAssigned), Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdAssigned__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnClientIdAssigned_MetaData), NewProp_OnClientIdAssigned_MetaData) }; // 357492274
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnPlayerDisconnected = { "OnPlayerDisconnected", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkReplicator, OnPlayerDisconnected), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerDisconnected__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnPlayerDisconnected_MetaData), NewProp_OnPlayerDisconnected_MetaData) }; // 685630318
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnPlayerPositionUpdated = { "OnPlayerPositionUpdated", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkReplicator, OnPlayerPositionUpdated), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerPositionUpdated__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnPlayerPositionUpdated_MetaData), NewProp_OnPlayerPositionUpdated_MetaData) }; // 2735752158
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnMyInitialPositionReceived = { "OnMyInitialPositionReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkReplicator, OnMyInitialPositionReceived), Z_Construct_UDelegateFunction_SimpleNetworking_OnMyInitialPositionReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnMyInitialPositionReceived_MetaData), NewProp_OnMyInitialPositionReceived_MetaData) }; // 985633122
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USimpleNetworkReplicator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnClientIdAssigned,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnPlayerDisconnected,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnPlayerPositionUpdated,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkReplicator_Statics::NewProp_OnMyInitialPositionReceived,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkReplicator_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USimpleNetworkReplicator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkReplicator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USimpleNetworkReplicator_Statics::ClassParams = {
	&USimpleNetworkReplicator::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_USimpleNetworkReplicator_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkReplicator_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkReplicator_Statics::Class_MetaDataParams), Z_Construct_UClass_USimpleNetworkReplicator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USimpleNetworkReplicator()
{
	if (!Z_Registration_Info_UClass_USimpleNetworkReplicator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USimpleNetworkReplicator.OuterSingleton, Z_Construct_UClass_USimpleNetworkReplicator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USimpleNetworkReplicator.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<USimpleNetworkReplicator>()
{
	return USimpleNetworkReplicator::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USimpleNetworkReplicator);
USimpleNetworkReplicator::~USimpleNetworkReplicator() {}
// End Class USimpleNetworkReplicator

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USimpleNetworkReplicator, USimpleNetworkReplicator::StaticClass, TEXT("USimpleNetworkReplicator"), &Z_Registration_Info_UClass_USimpleNetworkReplicator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USimpleNetworkReplicator), 922718258U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_3154297265(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
