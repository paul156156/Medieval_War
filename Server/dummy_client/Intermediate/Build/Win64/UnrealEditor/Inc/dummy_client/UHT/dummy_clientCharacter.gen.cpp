// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "dummy_client/dummy_clientCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodedummy_clientCharacter() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientCharacter();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientCharacter_NoRegister();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_UNetworkManager_NoRegister();
DUMMY_CLIENT_API UScriptStruct* Z_Construct_UScriptStruct_FOtherPlayerInfo();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_dummy_client();
// End Cross Module References

// Begin ScriptStruct FOtherPlayerInfo
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_OtherPlayerInfo;
class UScriptStruct* FOtherPlayerInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FOtherPlayerInfo, (UObject*)Z_Construct_UPackage__Script_dummy_client(), TEXT("OtherPlayerInfo"));
	}
	return Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton;
}
template<> DUMMY_CLIENT_API UScriptStruct* StaticStruct<FOtherPlayerInfo>()
{
	return FOtherPlayerInfo::StaticStruct();
}
struct Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc3\xbc\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc3\xbc" },
#endif
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FOtherPlayerInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_dummy_client,
	nullptr,
	&NewStructOps,
	"OtherPlayerInfo",
	nullptr,
	0,
	sizeof(FOtherPlayerInfo),
	alignof(FOtherPlayerInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FOtherPlayerInfo()
{
	if (!Z_Registration_Info_UScriptStruct_OtherPlayerInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_OtherPlayerInfo.InnerSingleton, Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_OtherPlayerInfo.InnerSingleton;
}
// End ScriptStruct FOtherPlayerInfo

// Begin Class Adummy_clientCharacter Function GetLocalClientId
struct Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics
{
	struct dummy_clientCharacter_eventGetLocalClientId_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventGetLocalClientId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "GetLocalClientId", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::dummy_clientCharacter_eventGetLocalClientId_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::dummy_clientCharacter_eventGetLocalClientId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execGetLocalClientId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLocalClientId();
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function GetLocalClientId

// Begin Class Adummy_clientCharacter Function GetOtherPlayerCount
struct Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics
{
	struct dummy_clientCharacter_eventGetOtherPlayerCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventGetOtherPlayerCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "GetOtherPlayerCount", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::dummy_clientCharacter_eventGetOtherPlayerCount_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::dummy_clientCharacter_eventGetOtherPlayerCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execGetOtherPlayerCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetOtherPlayerCount();
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function GetOtherPlayerCount

// Begin Class Adummy_clientCharacter Function OnClientIdReceived
struct Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics
{
	struct dummy_clientCharacter_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnClientIdReceived", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::dummy_clientCharacter_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::dummy_clientCharacter_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnClientIdReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClientIdReceived(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnClientIdReceived

// Begin Class Adummy_clientCharacter Function OnConnectionStatusChanged
struct Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics
{
	struct dummy_clientCharacter_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((dummy_clientCharacter_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(dummy_clientCharacter_eventOnConnectionStatusChanged_Parms), &Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnConnectionStatusChanged", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::dummy_clientCharacter_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::dummy_clientCharacter_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnConnectionStatusChanged)
{
	P_GET_UBOOL(Z_Param_IsConnected);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnConnectionStatusChanged(Z_Param_IsConnected);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnConnectionStatusChanged

// Begin Class Adummy_clientCharacter Function OnJumpStateUpdateReceived
struct Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics
{
	struct dummy_clientCharacter_eventOnJumpStateUpdateReceived_Parms
	{
		bool IsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd) */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((dummy_clientCharacter_eventOnJumpStateUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(dummy_clientCharacter_eventOnJumpStateUpdateReceived_Parms), &Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnJumpStateUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::dummy_clientCharacter_eventOnJumpStateUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::dummy_clientCharacter_eventOnJumpStateUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnJumpStateUpdateReceived)
{
	P_GET_UBOOL(Z_Param_IsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnJumpStateUpdateReceived(Z_Param_IsJumping);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnJumpStateUpdateReceived

// Begin Class Adummy_clientCharacter Function OnNetworkConnected
static const FName NAME_Adummy_clientCharacter_OnNetworkConnected = FName(TEXT("OnNetworkConnected"));
void Adummy_clientCharacter::OnNetworkConnected()
{
	UFunction* Func = FindFunctionChecked(NAME_Adummy_clientCharacter_OnNetworkConnected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnNetworkConnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class Adummy_clientCharacter Function OnNetworkConnected

// Begin Class Adummy_clientCharacter Function OnNetworkDisconnected
static const FName NAME_Adummy_clientCharacter_OnNetworkDisconnected = FName(TEXT("OnNetworkDisconnected"));
void Adummy_clientCharacter::OnNetworkDisconnected()
{
	UFunction* Func = FindFunctionChecked(NAME_Adummy_clientCharacter_OnNetworkDisconnected);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnNetworkDisconnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class Adummy_clientCharacter Function OnNetworkDisconnected

// Begin Class Adummy_clientCharacter Function OnOtherPlayerRemoved
struct dummy_clientCharacter_eventOnOtherPlayerRemoved_Parms
{
	int32 ClientId;
};
static const FName NAME_Adummy_clientCharacter_OnOtherPlayerRemoved = FName(TEXT("OnOtherPlayerRemoved"));
void Adummy_clientCharacter::OnOtherPlayerRemoved(int32 ClientId)
{
	dummy_clientCharacter_eventOnOtherPlayerRemoved_Parms Parms;
	Parms.ClientId=ClientId;
	UFunction* Func = FindFunctionChecked(NAME_Adummy_clientCharacter_OnOtherPlayerRemoved);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb5\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb5\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnOtherPlayerRemoved_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnOtherPlayerRemoved", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::PropPointers), sizeof(dummy_clientCharacter_eventOnOtherPlayerRemoved_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::Function_MetaDataParams) };
static_assert(sizeof(dummy_clientCharacter_eventOnOtherPlayerRemoved_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class Adummy_clientCharacter Function OnOtherPlayerRemoved

// Begin Class Adummy_clientCharacter Function OnOtherPlayerSpawned
struct dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms
{
	AActor* OtherPlayerActor;
	int32 ClientId;
};
static const FName NAME_Adummy_clientCharacter_OnOtherPlayerSpawned = FName(TEXT("OnOtherPlayerSpawned"));
void Adummy_clientCharacter::OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId)
{
	dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms Parms;
	Parms.OtherPlayerActor=OtherPlayerActor;
	Parms.ClientId=ClientId;
	UFunction* Func = FindFunctionChecked(NAME_Adummy_clientCharacter_OnOtherPlayerSpawned);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayerActor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor = { "OtherPlayerActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms, OtherPlayerActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnOtherPlayerSpawned", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::PropPointers), sizeof(dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::Function_MetaDataParams) };
static_assert(sizeof(dummy_clientCharacter_eventOnOtherPlayerSpawned_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class Adummy_clientCharacter Function OnOtherPlayerSpawned

// Begin Class Adummy_clientCharacter Function OnPlayerUpdateReceived
struct Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics
{
	struct dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms
	{
		int32 ClientId;
		FVector NewPosition;
		FRotator NewRotation;
		bool IsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd) */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewPosition_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewPosition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewRotation;
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRotation_MetaData), NewProp_NewRotation_MetaData) };
void Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms), &Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_NewPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_NewRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnPlayerUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::dummy_clientCharacter_eventOnPlayerUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnPlayerUpdateReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_NewPosition);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_NewRotation);
	P_GET_UBOOL(Z_Param_IsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPlayerUpdateReceived(Z_Param_ClientId,Z_Param_Out_NewPosition,Z_Param_Out_NewRotation,Z_Param_IsJumping);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnPlayerUpdateReceived

// Begin Class Adummy_clientCharacter Function OnPositionUpdateReceived
struct Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics
{
	struct dummy_clientCharacter_eventOnPositionUpdateReceived_Parms
	{
		FVector NewPosition;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd) */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd)" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnPositionUpdateReceived_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::NewProp_NewPosition,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnPositionUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::dummy_clientCharacter_eventOnPositionUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::dummy_clientCharacter_eventOnPositionUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnPositionUpdateReceived)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_NewPosition);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPositionUpdateReceived(Z_Param_Out_NewPosition);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnPositionUpdateReceived

// Begin Class Adummy_clientCharacter Function OnRotationUpdateReceived
struct Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics
{
	struct dummy_clientCharacter_eventOnRotationUpdateReceived_Parms
	{
		FRotator NewRotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd) */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xbd\xef\xbf\xbd)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewRotation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventOnRotationUpdateReceived_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRotation_MetaData), NewProp_NewRotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::NewProp_NewRotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "OnRotationUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::dummy_clientCharacter_eventOnRotationUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::dummy_clientCharacter_eventOnRotationUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execOnRotationUpdateReceived)
{
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_NewRotation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRotationUpdateReceived(Z_Param_Out_NewRotation);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function OnRotationUpdateReceived

// Begin Class Adummy_clientCharacter Function RemoveAllOtherPlayers
struct Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "RemoveAllOtherPlayers", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execRemoveAllOtherPlayers)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOtherPlayers();
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function RemoveAllOtherPlayers

// Begin Class Adummy_clientCharacter Function RemoveOtherPlayerCharacter
struct Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics
{
	struct dummy_clientCharacter_eventRemoveOtherPlayerCharacter_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventRemoveOtherPlayerCharacter_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "RemoveOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::dummy_clientCharacter_eventRemoveOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::dummy_clientCharacter_eventRemoveOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execRemoveOtherPlayerCharacter)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveOtherPlayerCharacter(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function RemoveOtherPlayerCharacter

// Begin Class Adummy_clientCharacter Function SpawnOtherPlayerCharacter
struct Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics
{
	struct dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms
	{
		FVector Position;
		int32 InClientId;
		AActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "CPP_Default_InClientId", "-1" },
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId = { "InClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms, InClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_InClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "SpawnOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers), sizeof(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(Adummy_clientCharacter::execSpawnOtherPlayerCharacter)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_PROPERTY(FIntProperty,Z_Param_InClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AActor**)Z_Param__Result=P_THIS->SpawnOtherPlayerCharacter(Z_Param_Out_Position,Z_Param_InClientId);
	P_NATIVE_END;
}
// End Class Adummy_clientCharacter Function SpawnOtherPlayerCharacter

// Begin Class Adummy_clientCharacter
void Adummy_clientCharacter::StaticRegisterNativesAdummy_clientCharacter()
{
	UClass* Class = Adummy_clientCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetLocalClientId", &Adummy_clientCharacter::execGetLocalClientId },
		{ "GetOtherPlayerCount", &Adummy_clientCharacter::execGetOtherPlayerCount },
		{ "OnClientIdReceived", &Adummy_clientCharacter::execOnClientIdReceived },
		{ "OnConnectionStatusChanged", &Adummy_clientCharacter::execOnConnectionStatusChanged },
		{ "OnJumpStateUpdateReceived", &Adummy_clientCharacter::execOnJumpStateUpdateReceived },
		{ "OnPlayerUpdateReceived", &Adummy_clientCharacter::execOnPlayerUpdateReceived },
		{ "OnPositionUpdateReceived", &Adummy_clientCharacter::execOnPositionUpdateReceived },
		{ "OnRotationUpdateReceived", &Adummy_clientCharacter::execOnRotationUpdateReceived },
		{ "RemoveAllOtherPlayers", &Adummy_clientCharacter::execRemoveAllOtherPlayers },
		{ "RemoveOtherPlayerCharacter", &Adummy_clientCharacter::execRemoveOtherPlayerCharacter },
		{ "SpawnOtherPlayerCharacter", &Adummy_clientCharacter::execSpawnOtherPlayerCharacter },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(Adummy_clientCharacter);
UClass* Z_Construct_UClass_Adummy_clientCharacter_NoRegister()
{
	return Adummy_clientCharacter::StaticClass();
}
struct Z_Construct_UClass_Adummy_clientCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "dummy_clientCharacter.h" },
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xc8\xb7\xce\xbf\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xc8\xb7\xce\xbf\xef\xbf\xbd \xc4\xab\xef\xbf\xbd\xde\xb6\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkManager_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdb\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xc5\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xdb\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableNetworkUpdates_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc8\xb0\xef\xbf\xbd\xef\xbf\xbd\xc8\xad */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc8\xb0\xef\xbf\xbd\xef\xbf\xbd\xc8\xad" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionUpdateInterval_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd) */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalClientId_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd\xc6\xae ID" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayers_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseTurnRate_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseLookUpRate_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd/\xef\xbf\xbd\xd9\xbf\xee\xb7\xb9\xef\xbf\xbd\xef\xbf\xbd\xc6\xae */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd/\xef\xbf\xbd\xd9\xbf\xee\xb7\xb9\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkManager;
	static void NewProp_bEnableNetworkUpdates_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableNetworkUpdates;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PositionUpdateInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LocalClientId;
	static const UECodeGen_Private::FClassPropertyParams NewProp_OtherPlayerCharacterClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OtherPlayers_ValueProp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayers_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_OtherPlayers;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseTurnRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseLookUpRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_Adummy_clientCharacter_GetLocalClientId, "GetLocalClientId" }, // 387248744
		{ &Z_Construct_UFunction_Adummy_clientCharacter_GetOtherPlayerCount, "GetOtherPlayerCount" }, // 4179836714
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnClientIdReceived, "OnClientIdReceived" }, // 206550279
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnConnectionStatusChanged, "OnConnectionStatusChanged" }, // 3026786390
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnJumpStateUpdateReceived, "OnJumpStateUpdateReceived" }, // 2211656082
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkConnected, "OnNetworkConnected" }, // 105777910
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnNetworkDisconnected, "OnNetworkDisconnected" }, // 4029573599
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerRemoved, "OnOtherPlayerRemoved" }, // 630105136
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnOtherPlayerSpawned, "OnOtherPlayerSpawned" }, // 3718412012
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnPlayerUpdateReceived, "OnPlayerUpdateReceived" }, // 3708269459
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived, "OnPositionUpdateReceived" }, // 586555525
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnRotationUpdateReceived, "OnRotationUpdateReceived" }, // 3813054373
		{ &Z_Construct_UFunction_Adummy_clientCharacter_RemoveAllOtherPlayers, "RemoveAllOtherPlayers" }, // 987574348
		{ &Z_Construct_UFunction_Adummy_clientCharacter_RemoveOtherPlayerCharacter, "RemoveOtherPlayerCharacter" }, // 2134668704
		{ &Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter, "SpawnOtherPlayerCharacter" }, // 685617608
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Adummy_clientCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_NetworkManager = { "NetworkManager", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, NetworkManager), Z_Construct_UClass_UNetworkManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkManager_MetaData), NewProp_NetworkManager_MetaData) };
void Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_bEnableNetworkUpdates_SetBit(void* Obj)
{
	((Adummy_clientCharacter*)Obj)->bEnableNetworkUpdates = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_bEnableNetworkUpdates = { "bEnableNetworkUpdates", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(Adummy_clientCharacter), &Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_bEnableNetworkUpdates_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableNetworkUpdates_MetaData), NewProp_bEnableNetworkUpdates_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_PositionUpdateInterval = { "PositionUpdateInterval", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, PositionUpdateInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionUpdateInterval_MetaData), NewProp_PositionUpdateInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_LocalClientId = { "LocalClientId", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, LocalClientId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalClientId_MetaData), NewProp_LocalClientId_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0024080000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers_ValueProp = { "OtherPlayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FOtherPlayerInfo, METADATA_PARAMS(0, nullptr) }; // 3505176033
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers_Key_KeyProp = { "OtherPlayers_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers = { "OtherPlayers", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, OtherPlayers), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayers_MetaData), NewProp_OtherPlayers_MetaData) }; // 3505176033
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseTurnRate = { "BaseTurnRate", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, BaseTurnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseTurnRate_MetaData), NewProp_BaseTurnRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseLookUpRate = { "BaseLookUpRate", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, BaseLookUpRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseLookUpRate_MetaData), NewProp_BaseLookUpRate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_Adummy_clientCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_bEnableNetworkUpdates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_PositionUpdateInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_LocalClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayerCharacterClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_OtherPlayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseTurnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseLookUpRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_Adummy_clientCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_dummy_client,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_Adummy_clientCharacter_Statics::ClassParams = {
	&Adummy_clientCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_Adummy_clientCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientCharacter_Statics::PropPointers),
	0,
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_Adummy_clientCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_Adummy_clientCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_Adummy_clientCharacter()
{
	if (!Z_Registration_Info_UClass_Adummy_clientCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_Adummy_clientCharacter.OuterSingleton, Z_Construct_UClass_Adummy_clientCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_Adummy_clientCharacter.OuterSingleton;
}
template<> DUMMY_CLIENT_API UClass* StaticClass<Adummy_clientCharacter>()
{
	return Adummy_clientCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(Adummy_clientCharacter);
Adummy_clientCharacter::~Adummy_clientCharacter() {}
// End Class Adummy_clientCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FOtherPlayerInfo::StaticStruct, Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewStructOps, TEXT("OtherPlayerInfo"), &Z_Registration_Info_UScriptStruct_OtherPlayerInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FOtherPlayerInfo), 3505176033U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_Adummy_clientCharacter, Adummy_clientCharacter::StaticClass, TEXT("Adummy_clientCharacter"), &Z_Registration_Info_UClass_Adummy_clientCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(Adummy_clientCharacter), 1107035437U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_2532973154(TEXT("/Script/dummy_client"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
