// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyProject/Private/GamePlay/MyNetworkCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyNetworkCharacter() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
MYPROJECT_API UClass* Z_Construct_UClass_AMyCharacter();
MYPROJECT_API UClass* Z_Construct_UClass_AMyNetworkCharacter();
MYPROJECT_API UClass* Z_Construct_UClass_AMyNetworkCharacter_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_UNetworkPlayerComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
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
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
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
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
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

// Begin Class AMyNetworkCharacter Function OnClientIdReceived
struct Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics
{
	struct MyNetworkCharacter_eventOnClientIdReceived_Parms
	{
		int32 ClientId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkCharacter_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkCharacter, nullptr, "OnClientIdReceived", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::MyNetworkCharacter_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::MyNetworkCharacter_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkCharacter::execOnClientIdReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClientIdReceived(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Class AMyNetworkCharacter Function OnClientIdReceived

// Begin Class AMyNetworkCharacter Function OnConnectionStatusChanged
struct Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics
{
	struct MyNetworkCharacter_eventOnConnectionStatusChanged_Parms
	{
		bool IsConnected;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xda\xb5\xe9\xb7\xaf - UFUNCTION \xef\xbf\xbd\xef\xbf\xbd\xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xca\xbf\xef\xbf\xbd!\n" },
#endif
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xda\xb5\xe9\xb7\xaf - UFUNCTION \xef\xbf\xbd\xef\xbf\xbd\xc5\xa9\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xca\xbf\xef\xbf\xbd!" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_IsConnected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsConnected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit(void* Obj)
{
	((MyNetworkCharacter_eventOnConnectionStatusChanged_Parms*)Obj)->IsConnected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected = { "IsConnected", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyNetworkCharacter_eventOnConnectionStatusChanged_Parms), &Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::NewProp_IsConnected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkCharacter, nullptr, "OnConnectionStatusChanged", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::MyNetworkCharacter_eventOnConnectionStatusChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::MyNetworkCharacter_eventOnConnectionStatusChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkCharacter::execOnConnectionStatusChanged)
{
	P_GET_UBOOL(Z_Param_IsConnected);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnConnectionStatusChanged(Z_Param_IsConnected);
	P_NATIVE_END;
}
// End Class AMyNetworkCharacter Function OnConnectionStatusChanged

// Begin Class AMyNetworkCharacter Function OnPlayerUpdateReceived
struct Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics
{
	struct MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms
	{
		int32 ClientId;
		FVector Position;
		FRotator Rotation;
		FVector Velocity;
		bool IsJumping;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
void Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms), &Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AMyNetworkCharacter, nullptr, "OnPlayerUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::PropPointers), sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::MyNetworkCharacter_eventOnPlayerUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMyNetworkCharacter::execOnPlayerUpdateReceived)
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
// End Class AMyNetworkCharacter Function OnPlayerUpdateReceived

// Begin Class AMyNetworkCharacter
void AMyNetworkCharacter::StaticRegisterNativesAMyNetworkCharacter()
{
	UClass* Class = AMyNetworkCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &AMyNetworkCharacter::execConnectToServer },
		{ "DisconnectFromServer", &AMyNetworkCharacter::execDisconnectFromServer },
		{ "OnClientIdReceived", &AMyNetworkCharacter::execOnClientIdReceived },
		{ "OnConnectionStatusChanged", &AMyNetworkCharacter::execOnConnectionStatusChanged },
		{ "OnPlayerUpdateReceived", &AMyNetworkCharacter::execOnPlayerUpdateReceived },
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xb7 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xdf\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "GamePlay/MyNetworkCharacter.h" },
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xb7 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xdf\xb0\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NetworkComponent_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xc5\xa9 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerCharacterClass_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Private/GamePlay/MyNetworkCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NetworkComponent;
	static const UECodeGen_Private::FClassPropertyParams NewProp_OtherPlayerCharacterClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMyNetworkCharacter_ConnectToServer, "ConnectToServer" }, // 548178795
		{ &Z_Construct_UFunction_AMyNetworkCharacter_DisconnectFromServer, "DisconnectFromServer" }, // 3374125429
		{ &Z_Construct_UFunction_AMyNetworkCharacter_OnClientIdReceived, "OnClientIdReceived" }, // 2031542506
		{ &Z_Construct_UFunction_AMyNetworkCharacter_OnConnectionStatusChanged, "OnConnectionStatusChanged" }, // 1187020391
		{ &Z_Construct_UFunction_AMyNetworkCharacter_OnPlayerUpdateReceived, "OnPlayerUpdateReceived" }, // 3397860754
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyNetworkCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_NetworkComponent = { "NetworkComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkCharacter, NetworkComponent), Z_Construct_UClass_UNetworkPlayerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NetworkComponent_MetaData), NewProp_NetworkComponent_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_OtherPlayerCharacterClass = { "OtherPlayerCharacterClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMyNetworkCharacter, OtherPlayerCharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPlayerCharacterClass_MetaData), NewProp_OtherPlayerCharacterClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_NetworkComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMyNetworkCharacter_Statics::NewProp_OtherPlayerCharacterClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyNetworkCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AMyNetworkCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AMyCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
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
template<> MYPROJECT_API UClass* StaticClass<AMyNetworkCharacter>()
{
	return AMyNetworkCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AMyNetworkCharacter);
AMyNetworkCharacter::~AMyNetworkCharacter() {}
// End Class AMyNetworkCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyNetworkCharacter, AMyNetworkCharacter::StaticClass, TEXT("AMyNetworkCharacter"), &Z_Registration_Info_UClass_AMyNetworkCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyNetworkCharacter), 343456225U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_1131932377(TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
