// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/SimpleNetworkCharacter.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSimpleNetworkCharacter() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_ASimpleNetworkCharacter();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_ASimpleNetworkCharacter_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkManager_NoRegister();
SIMPLENETWORKING_API UScriptStruct* Z_Construct_UScriptStruct_FOtherPlayerInfo();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Class ASimpleNetworkCharacter Function GetLocalClientId
struct Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics
{
	struct SimpleNetworkCharacter_eventGetLocalClientId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x98\x84\xec\x9e\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xeb\xb0\x98\xed\x99\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x98\x84\xec\x9e\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xeb\xb0\x98\xed\x99\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventGetLocalClientId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "GetLocalClientId", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::SimpleNetworkCharacter_eventGetLocalClientId_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::SimpleNetworkCharacter_eventGetLocalClientId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execGetLocalClientId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLocalClientId();
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function GetLocalClientId

// Begin Class ASimpleNetworkCharacter Function GetOtherPlayerCount
struct Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics
{
	struct SimpleNetworkCharacter_eventGetOtherPlayerCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xea\xb0\x9c\xec\x88\x98 \xeb\xb0\x98\xed\x99\x98\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xea\xb0\x9c\xec\x88\x98 \xeb\xb0\x98\xed\x99\x98" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventGetOtherPlayerCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "GetOtherPlayerCount", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::SimpleNetworkCharacter_eventGetOtherPlayerCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::SimpleNetworkCharacter_eventGetOtherPlayerCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execGetOtherPlayerCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetOtherPlayerCount();
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function GetOtherPlayerCount

// Begin Class ASimpleNetworkCharacter Function OnConnectionStatusChanged
struct Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics
{
	struct SimpleNetworkCharacter_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8 \xed\x95\xb8\xeb\x93\xa4\xeb\x9f\xac (\xeb\x82\xb4\xeb\xb6\x80)\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8 \xed\x95\xb8\xeb\x93\xa4\xeb\x9f\xac (\xeb\x82\xb4\xeb\xb6\x80)" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((SimpleNetworkCharacter_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SimpleNetworkCharacter_eventOnConnectionStatusChanged_Parms), &Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "OnConnectionStatusChanged", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::SimpleNetworkCharacter_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::SimpleNetworkCharacter_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execOnConnectionStatusChanged)
{
	P_GET_UBOOL(Z_Param_IsConnected);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnConnectionStatusChanged(Z_Param_IsConnected);
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function OnConnectionStatusChanged

// Begin Class ASimpleNetworkCharacter Function RemoveAllOtherPlayers
struct Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xaa\xa8\xeb\x93\xa0 \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xaa\xa8\xeb\x93\xa0 \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "RemoveAllOtherPlayers", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execRemoveAllOtherPlayers)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOtherPlayers();
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function RemoveAllOtherPlayers

// Begin Class ASimpleNetworkCharacter Function RemoveOtherPlayerCharacter
struct Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics
{
	struct SimpleNetworkCharacter_eventRemoveOtherPlayerCharacter_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\xa0\x9c\xea\xb1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xec\xa0\x9c\xea\xb1\xb0" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventRemoveOtherPlayerCharacter_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "RemoveOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::SimpleNetworkCharacter_eventRemoveOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::SimpleNetworkCharacter_eventRemoveOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execRemoveOtherPlayerCharacter)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveOtherPlayerCharacter(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function RemoveOtherPlayerCharacter

// Begin Class ASimpleNetworkCharacter Function SpawnOtherPlayerCharacter
struct Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics
{
	struct SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms
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
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId = { "InClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms, InClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASimpleNetworkCharacter, nullptr, "SpawnOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::SimpleNetworkCharacter_eventSpawnOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASimpleNetworkCharacter::execSpawnOtherPlayerCharacter)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_PROPERTY(FIntProperty,Z_Param_InClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AActor**)Z_Param__Result=P_THIS->SpawnOtherPlayerCharacter(Z_Param_Out_Position,Z_Param_InClientId);
	P_NATIVE_END;
}
// End Class ASimpleNetworkCharacter Function SpawnOtherPlayerCharacter

// Begin Class ASimpleNetworkCharacter
void ASimpleNetworkCharacter::StaticRegisterNativesASimpleNetworkCharacter()
{
	UClass* Class = ASimpleNetworkCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetLocalClientId", &ASimpleNetworkCharacter::execGetLocalClientId },
		{ "GetOtherPlayerCount", &ASimpleNetworkCharacter::execGetOtherPlayerCount },
		{ "OnConnectionStatusChanged", &ASimpleNetworkCharacter::execOnConnectionStatusChanged },
		{ "RemoveAllOtherPlayers", &ASimpleNetworkCharacter::execRemoveAllOtherPlayers },
		{ "RemoveOtherPlayerCharacter", &ASimpleNetworkCharacter::execRemoveOtherPlayerCharacter },
		{ "SpawnOtherPlayerCharacter", &ASimpleNetworkCharacter::execSpawnOtherPlayerCharacter },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASimpleNetworkCharacter);
UClass* Z_Construct_UClass_ASimpleNetworkCharacter_NoRegister()
{
	return ASimpleNetworkCharacter::StaticClass();
}
struct Z_Construct_UClass_ASimpleNetworkCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SimpleNetworkCharacter.h" },
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Enhanced Input \xea\xb4\x80\xeb\xa0\xa8 \xec\x86\x8d\xec\x84\xb1 \xec\xb6\x94\xea\xb0\x80\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enhanced Input \xea\xb4\x80\xeb\xa0\xa8 \xec\x86\x8d\xec\x84\xb1 \xec\xb6\x94\xea\xb0\x80" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveForwardAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveRightAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xb0\xb8\xec\xa1\xb0\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xeb\xa7\xa4\xeb\x8b\x88\xec\xa0\x80 \xec\xb0\xb8\xec\xa1\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableNetworkUpdates_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xed\x99\x9c\xec\x84\xb1\xed\x99\x94\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xed\x99\x9c\xec\x84\xb1\xed\x99\x94" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionUpdateInterval_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xec\x9c\x84\xec\xb9\x98 \xec\xa0\x84\xec\x86\xa1 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xec\x9c\x84\xec\xb9\x98 \xec\xa0\x84\xec\x86\xa1 \xea\xb0\x84\xea\xb2\xa9 (\xec\xb4\x88)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalClientId_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\xa1\x9c\xec\xbb\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\xa1\x9c\xec\xbb\xac \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xed\x81\xb4\xeb\x9e\x98\xec\x8a\xa4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayers_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xeb\xa7\xb5\n" },
#endif
		{ "ModuleRelativePath", "Public/SimpleNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xba\x90\xeb\xa6\xad\xed\x84\xb0 \xeb\xa7\xb5" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveForwardAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveRightAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
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
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_GetLocalClientId, "GetLocalClientId" }, // 383678588
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_GetOtherPlayerCount, "GetOtherPlayerCount" }, // 3260232454
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_OnConnectionStatusChanged, "OnConnectionStatusChanged" }, // 29190986
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveAllOtherPlayers, "RemoveAllOtherPlayers" }, // 3259162195
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_RemoveOtherPlayerCharacter, "RemoveOtherPlayerCharacter" }, // 2301292148
		{ &Z_Construct_UFunction_ASimpleNetworkCharacter_SpawnOtherPlayerCharacter, "SpawnOtherPlayerCharacter" }, // 3903858053
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASimpleNetworkCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_MoveForwardAction = { "MoveForwardAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, MoveForwardAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveForwardAction_MetaData), NewProp_MoveForwardAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_MoveRightAction = { "MoveRightAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, MoveRightAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveRightAction_MetaData), NewProp_MoveRightAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, NetworkManager), Z_Construct_UClass_USimpleNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
void Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_bEnableNetworkUpdates_SetBit(void* Obj)
{
	((ASimpleNetworkCharacter*)Obj)->bEnableNetworkUpdates = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_bEnableNetworkUpdates = { "bEnableNetworkUpdates", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASimpleNetworkCharacter), &Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_bEnableNetworkUpdates_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableNetworkUpdates_MetaData), NewProp_bEnableNetworkUpdates_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_PositionUpdateInterval = { "PositionUpdateInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, PositionUpdateInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionUpdateInterval_MetaData), NewProp_PositionUpdateInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_LocalClientId = { "LocalClientId", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, LocalClientId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalClientId_MetaData), NewProp_LocalClientId_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers_ValueProp = { "OtherPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FOtherPlayerInfo, METADATA_PARAMS(0, nullptr) }; // 4218889607
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers_Key_KeyProp = { "OtherPlayers_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers = { "OtherPlayers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleNetworkCharacter, OtherPlayers), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayers_MetaData), NewProp_OtherPlayers_MetaData) }; // 4218889607
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASimpleNetworkCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_MoveForwardAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_MoveRightAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_bEnableNetworkUpdates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_PositionUpdateInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_LocalClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayerCharacterClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleNetworkCharacter_Statics::NewProp_OtherPlayers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASimpleNetworkCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASimpleNetworkCharacter_Statics::ClassParams = {
	&ASimpleNetworkCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ASimpleNetworkCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleNetworkCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASimpleNetworkCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASimpleNetworkCharacter()
{
	if (!Z_Registration_Info_UClass_ASimpleNetworkCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASimpleNetworkCharacter.OuterSingleton, Z_Construct_UClass_ASimpleNetworkCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASimpleNetworkCharacter.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<ASimpleNetworkCharacter>()
{
	return ASimpleNetworkCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASimpleNetworkCharacter);
ASimpleNetworkCharacter::~ASimpleNetworkCharacter() {}
// End Class ASimpleNetworkCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASimpleNetworkCharacter, ASimpleNetworkCharacter::StaticClass, TEXT("ASimpleNetworkCharacter"), &Z_Registration_Info_UClass_ASimpleNetworkCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASimpleNetworkCharacter), 1182960469U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_664727340(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
