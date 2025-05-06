// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworkManager() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPlayerState();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature();
SIMPLENETWORKING_API UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Delegate FOnPositionUpdate
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnPositionUpdate_Parms
	{
		FVector NewPosition;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8d\xb8\xeb\xa6\xac\xea\xb2\x8c\xec\x9d\xb4\xed\x8a\xb8 \xec\xa0\x95\xec\x9d\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8d\xb8\xeb\xa6\xac\xea\xb2\x8c\xec\x9d\xb4\xed\x8a\xb8 \xec\xa0\x95\xec\x9d\x98" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPositionUpdate_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::NewProp_NewPosition,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnPositionUpdate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPositionUpdate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPositionUpdate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnPositionUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPositionUpdate, FVector const& NewPosition)
{
	struct _Script_SimpleNetworking_eventOnPositionUpdate_Parms
	{
		FVector NewPosition;
	};
	_Script_SimpleNetworking_eventOnPositionUpdate_Parms Parms;
	Parms.NewPosition=NewPosition;
	OnPositionUpdate.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnPositionUpdate

// Begin Delegate FOnRotationUpdate
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnRotationUpdate_Parms
	{
		FRotator NewRotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewRotation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnRotationUpdate_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRotation_MetaData), NewProp_NewRotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::NewProp_NewRotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnRotationUpdate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnRotationUpdate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnRotationUpdate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnRotationUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnRotationUpdate, FRotator const& NewRotation)
{
	struct _Script_SimpleNetworking_eventOnRotationUpdate_Parms
	{
		FRotator NewRotation;
	};
	_Script_SimpleNetworking_eventOnRotationUpdate_Parms Parms;
	Parms.NewRotation=NewRotation;
	OnRotationUpdate.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnRotationUpdate

// Begin Delegate FOnConnectionStatusChanged
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((_Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms), &Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnConnectionStatusChanged__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnConnectionStatusChanged_DelegateWrapper(const FMulticastScriptDelegate& OnConnectionStatusChanged, bool IsConnected)
{
	struct _Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
	_Script_SimpleNetworking_eventOnConnectionStatusChanged_Parms Parms;
	Parms.IsConnected=IsConnected ? true : false;
	OnConnectionStatusChanged.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnConnectionStatusChanged

// Begin Delegate FOnPlayerUpdate
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnPlayerUpdate_Parms
	{
		int32 ClientId;
		FVector Position;
		FRotator Rotation;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerUpdate_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerUpdate_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerUpdate_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnPlayerUpdate_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnPlayerUpdate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerUpdate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnPlayerUpdate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnPlayerUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerUpdate, int32 ClientId, FVector const& Position, FRotator const& Rotation, EPlayerState State)
{
	struct _Script_SimpleNetworking_eventOnPlayerUpdate_Parms
	{
		int32 ClientId;
		FVector Position;
		FRotator Rotation;
		EPlayerState State;
	};
	_Script_SimpleNetworking_eventOnPlayerUpdate_Parms Parms;
	Parms.ClientId=ClientId;
	Parms.Position=Position;
	Parms.Rotation=Rotation;
	Parms.State=State;
	OnPlayerUpdate.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnPlayerUpdate

// Begin Delegate FOnClientIdReceived
struct Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics
{
	struct _Script_SimpleNetworking_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_SimpleNetworking_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking, nullptr, "OnClientIdReceived__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::_Script_SimpleNetworking_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnClientIdReceived_DelegateWrapper(const FMulticastScriptDelegate& OnClientIdReceived, int32 ClientId)
{
	struct _Script_SimpleNetworking_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
	_Script_SimpleNetworking_eventOnClientIdReceived_Parms Parms;
	Parms.ClientId=ClientId;
	OnClientIdReceived.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnClientIdReceived

// Begin Class USimpleNetworkManager Function ConnectToServer
struct Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics
{
	struct SimpleNetworkManager_eventConnectToServer_Parms
	{
		FString IPAddress;
		int32 Port;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xa8\xec\x88\x98" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IPAddress_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_IPAddress;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Port;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_IPAddress = { "IPAddress", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventConnectToServer_Parms, IPAddress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IPAddress_MetaData), NewProp_IPAddress_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventConnectToServer_Parms, Port), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((SimpleNetworkManager_eventConnectToServer_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SimpleNetworkManager_eventConnectToServer_Parms), &Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_IPAddress,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_Port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "ConnectToServer", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::SimpleNetworkManager_eventConnectToServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::SimpleNetworkManager_eventConnectToServer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execConnectToServer)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_IPAddress);
	P_GET_PROPERTY(FIntProperty,Z_Param_Port);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ConnectToServer(Z_Param_IPAddress,Z_Param_Port);
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function ConnectToServer

// Begin Class USimpleNetworkManager Function DisconnectFromServer
struct Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x84\x9c\xeb\xb2\x84 \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function DisconnectFromServer

// Begin Class USimpleNetworkManager Function GetClientId
struct Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics
{
	struct SimpleNetworkManager_eventGetClientId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xea\xb0\x80\xec\xa0\xb8\xec\x98\xa4\xea\xb8\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xea\xb0\x80\xec\xa0\xb8\xec\x98\xa4\xea\xb8\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventGetClientId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "GetClientId", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::SimpleNetworkManager_eventGetClientId_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::SimpleNetworkManager_eventGetClientId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_GetClientId()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_GetClientId_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execGetClientId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetClientId();
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function GetClientId

// Begin Class USimpleNetworkManager Function GetLastErrorCode
struct Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics
{
	struct SimpleNetworkManager_eventGetLastErrorCode_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa7\x88\xec\xa7\x80\xeb\xa7\x89 \xec\x97\x90\xeb\x9f\xac \xec\xbd\x94\xeb\x93\x9c \xeb\xb0\x98\xed\x99\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa7\x88\xec\xa7\x80\xeb\xa7\x89 \xec\x97\x90\xeb\x9f\xac \xec\xbd\x94\xeb\x93\x9c \xeb\xb0\x98\xed\x99\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventGetLastErrorCode_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "GetLastErrorCode", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::SimpleNetworkManager_eventGetLastErrorCode_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::SimpleNetworkManager_eventGetLastErrorCode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execGetLastErrorCode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLastErrorCode();
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function GetLastErrorCode

// Begin Class USimpleNetworkManager Function IsConnected
struct Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics
{
	struct SimpleNetworkManager_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x97\xb0\xea\xb2\xb0 \xec\x83\x81\xed\x83\x9c \xed\x99\x95\xec\x9d\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x97\xb0\xea\xb2\xb0 \xec\x83\x81\xed\x83\x9c \xed\x99\x95\xec\x9d\xb8" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((SimpleNetworkManager_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SimpleNetworkManager_eventIsConnected_Parms), &Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "IsConnected", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::SimpleNetworkManager_eventIsConnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::SimpleNetworkManager_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function IsConnected

// Begin Class USimpleNetworkManager Function SendAttackPacket
struct Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics
{
	struct SimpleNetworkManager_eventSendAttackPacket_Parms
	{
		FVector Position;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xea\xb3\xb5\xea\xb2\xa9 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xea\xb3\xb5\xea\xb2\xa9 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendAttackPacket_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendAttackPacket_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "SendAttackPacket", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::SimpleNetworkManager_eventSendAttackPacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::SimpleNetworkManager_eventSendAttackPacket_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execSendAttackPacket)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendAttackPacket(Z_Param_Out_Position,EPlayerState(Z_Param_State));
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function SendAttackPacket

// Begin Class USimpleNetworkManager Function SendJumpPacket
struct Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics
{
	struct SimpleNetworkManager_eventSendJumpPacket_Parms
	{
		bool IsJumping;
		FVector Position;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\xa0\x90\xed\x94\x84 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\xa0\x90\xed\x94\x84 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((SimpleNetworkManager_eventSendJumpPacket_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SimpleNetworkManager_eventSendJumpPacket_Parms), &Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendJumpPacket_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendJumpPacket_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "SendJumpPacket", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::SimpleNetworkManager_eventSendJumpPacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::SimpleNetworkManager_eventSendJumpPacket_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execSendJumpPacket)
{
	P_GET_UBOOL(Z_Param_IsJumping);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendJumpPacket(Z_Param_IsJumping,Z_Param_Out_Position,EPlayerState(Z_Param_State));
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function SendJumpPacket

// Begin Class USimpleNetworkManager Function SendMovePacket
struct Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics
{
	struct SimpleNetworkManager_eventSendMovePacket_Parms
	{
		float ForwardValue;
		float RightValue;
		FVector Position;
		FRotator Rotation;
		EPlayerState State;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9d\xb4\xeb\x8f\x99 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9d\xb4\xeb\x8f\x99 \xed\x8c\xa8\xed\x82\xb7 \xec\xa0\x84\xec\x86\xa1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ForwardValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RightValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Rotation;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_ForwardValue = { "ForwardValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendMovePacket_Parms, ForwardValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_RightValue = { "RightValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendMovePacket_Parms, RightValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendMovePacket_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendMovePacket_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkManager_eventSendMovePacket_Parms, State), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_ForwardValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_RightValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkManager, nullptr, "SendMovePacket", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::SimpleNetworkManager_eventSendMovePacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::SimpleNetworkManager_eventSendMovePacket_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USimpleNetworkManager::execSendMovePacket)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_ForwardValue);
	P_GET_PROPERTY(FFloatProperty,Z_Param_RightValue);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_GET_ENUM(EPlayerState,Z_Param_State);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendMovePacket(Z_Param_ForwardValue,Z_Param_RightValue,Z_Param_Out_Position,Z_Param_Out_Rotation,EPlayerState(Z_Param_State));
	P_NATIVE_END;
}
// End Class USimpleNetworkManager Function SendMovePacket

// Begin Class USimpleNetworkManager
void USimpleNetworkManager::StaticRegisterNativesUSimpleNetworkManager()
{
	UClass* Class = USimpleNetworkManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &USimpleNetworkManager::execConnectToServer },
		{ "DisconnectFromServer", &USimpleNetworkManager::execDisconnectFromServer },
		{ "GetClientId", &USimpleNetworkManager::execGetClientId },
		{ "GetLastErrorCode", &USimpleNetworkManager::execGetLastErrorCode },
		{ "IsConnected", &USimpleNetworkManager::execIsConnected },
		{ "SendAttackPacket", &USimpleNetworkManager::execSendAttackPacket },
		{ "SendJumpPacket", &USimpleNetworkManager::execSendJumpPacket },
		{ "SendMovePacket", &USimpleNetworkManager::execSendMovePacket },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USimpleNetworkManager);
UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister()
{
	return USimpleNetworkManager::StaticClass();
}
struct Z_Construct_UClass_USimpleNetworkManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "SimpleNetworkManager.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnPositionUpdate_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8d\xb8\xeb\xa6\xac\xea\xb2\x8c\xec\x9d\xb4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8d\xb8\xeb\xa6\xac\xea\xb2\x8c\xec\x9d\xb4\xed\x8a\xb8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnRotationUpdate_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnConnectionStatusChanged_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnPlayerUpdate_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnClientIdReceived_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/SimpleNetworkManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPositionUpdate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRotationUpdate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnConnectionStatusChanged;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPlayerUpdate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnClientIdReceived;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USimpleNetworkManager_ConnectToServer, "ConnectToServer" }, // 1092588381
		{ &Z_Construct_UFunction_USimpleNetworkManager_DisconnectFromServer, "DisconnectFromServer" }, // 3385937367
		{ &Z_Construct_UFunction_USimpleNetworkManager_GetClientId, "GetClientId" }, // 444138218
		{ &Z_Construct_UFunction_USimpleNetworkManager_GetLastErrorCode, "GetLastErrorCode" }, // 1534544213
		{ &Z_Construct_UFunction_USimpleNetworkManager_IsConnected, "IsConnected" }, // 493655781
		{ &Z_Construct_UFunction_USimpleNetworkManager_SendAttackPacket, "SendAttackPacket" }, // 3017017671
		{ &Z_Construct_UFunction_USimpleNetworkManager_SendJumpPacket, "SendJumpPacket" }, // 458825276
		{ &Z_Construct_UFunction_USimpleNetworkManager_SendMovePacket, "SendMovePacket" }, // 267245226
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USimpleNetworkManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnPositionUpdate = { "OnPositionUpdate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkManager, OnPositionUpdate), Z_Construct_UDelegateFunction_SimpleNetworking_OnPositionUpdate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnPositionUpdate_MetaData), NewProp_OnPositionUpdate_MetaData) }; // 3155615807
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnRotationUpdate = { "OnRotationUpdate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkManager, OnRotationUpdate), Z_Construct_UDelegateFunction_SimpleNetworking_OnRotationUpdate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnRotationUpdate_MetaData), NewProp_OnRotationUpdate_MetaData) }; // 3965342501
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnConnectionStatusChanged = { "OnConnectionStatusChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkManager, OnConnectionStatusChanged), Z_Construct_UDelegateFunction_SimpleNetworking_OnConnectionStatusChanged__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnConnectionStatusChanged_MetaData), NewProp_OnConnectionStatusChanged_MetaData) }; // 1612091784
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnPlayerUpdate = { "OnPlayerUpdate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkManager, OnPlayerUpdate), Z_Construct_UDelegateFunction_SimpleNetworking_OnPlayerUpdate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnPlayerUpdate_MetaData), NewProp_OnPlayerUpdate_MetaData) }; // 1289674333
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnClientIdReceived = { "OnClientIdReceived", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USimpleNetworkManager, OnClientIdReceived), Z_Construct_UDelegateFunction_SimpleNetworking_OnClientIdReceived__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnClientIdReceived_MetaData), NewProp_OnClientIdReceived_MetaData) }; // 3451386
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USimpleNetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnPositionUpdate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnRotationUpdate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnConnectionStatusChanged,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnPlayerUpdate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USimpleNetworkManager_Statics::NewProp_OnClientIdReceived,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USimpleNetworkManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USimpleNetworkManager_Statics::ClassParams = {
	&USimpleNetworkManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USimpleNetworkManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_USimpleNetworkManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USimpleNetworkManager()
{
	if (!Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton, Z_Construct_UClass_USimpleNetworkManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USimpleNetworkManager.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<USimpleNetworkManager>()
{
	return USimpleNetworkManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USimpleNetworkManager);
// End Class USimpleNetworkManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USimpleNetworkManager, USimpleNetworkManager::StaticClass, TEXT("USimpleNetworkManager"), &Z_Registration_Info_UClass_USimpleNetworkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USimpleNetworkManager), 3343174070U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_657998198(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
