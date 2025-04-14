// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "dummy_client/NetworkManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkManager() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_UNetworkManager();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_UNetworkManager_NoRegister();
DUMMY_CLIENT_API UEnum* Z_Construct_UEnum_dummy_client_EPacketType();
DUMMY_CLIENT_API UFunction* Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_dummy_client();
// End Cross Module References

// Begin Enum EPacketType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPacketType;
static UEnum* EPacketType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPacketType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPacketType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_dummy_client_EPacketType, (UObject*)Z_Construct_UPackage__Script_dummy_client(), TEXT("EPacketType"));
	}
	return Z_Registration_Info_UEnum_EPacketType.OuterSingleton;
}
template<> DUMMY_CLIENT_API UEnum* StaticEnum<EPacketType>()
{
	return EPacketType_StaticEnum();
}
struct Z_Construct_UEnum_dummy_client_EPacketType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb0\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "JUMP.Name", "EPacketType::JUMP" },
		{ "ModuleRelativePath", "NetworkManager.h" },
		{ "MOVE.Name", "EPacketType::MOVE" },
		{ "POSITION_UPDATE.Name", "EPacketType::POSITION_UPDATE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcf\xb0\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPacketType::MOVE", (int64)EPacketType::MOVE },
		{ "EPacketType::JUMP", (int64)EPacketType::JUMP },
		{ "EPacketType::POSITION_UPDATE", (int64)EPacketType::POSITION_UPDATE },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_dummy_client_EPacketType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_dummy_client,
	nullptr,
	"EPacketType",
	"EPacketType",
	Z_Construct_UEnum_dummy_client_EPacketType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_dummy_client_EPacketType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_dummy_client_EPacketType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_dummy_client_EPacketType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_dummy_client_EPacketType()
{
	if (!Z_Registration_Info_UEnum_EPacketType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPacketType.InnerSingleton, Z_Construct_UEnum_dummy_client_EPacketType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPacketType.InnerSingleton;
}
// End Enum EPacketType

// Begin Delegate FOnPositionUpdate
struct Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics
{
	struct _Script_dummy_client_eventOnPositionUpdate_Parms
	{
		FVector NewPosition;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_dummy_client_eventOnPositionUpdate_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::NewProp_NewPosition,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_dummy_client, nullptr, "OnPositionUpdate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::_Script_dummy_client_eventOnPositionUpdate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::_Script_dummy_client_eventOnPositionUpdate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnPositionUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPositionUpdate, FVector const& NewPosition)
{
	struct _Script_dummy_client_eventOnPositionUpdate_Parms
	{
		FVector NewPosition;
	};
	_Script_dummy_client_eventOnPositionUpdate_Parms Parms;
	Parms.NewPosition=NewPosition;
	OnPositionUpdate.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnPositionUpdate

// Begin Class UNetworkManager Function ConnectToServer
struct Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics
{
	struct NetworkManager_eventConnectToServer_Parms
	{
		FString IPAddress;
		int32 Port;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd" },
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
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_IPAddress = { "IPAddress", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventConnectToServer_Parms, IPAddress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IPAddress_MetaData), NewProp_IPAddress_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventConnectToServer_Parms, Port), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((NetworkManager_eventConnectToServer_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkManager_eventConnectToServer_Parms), &Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_IPAddress,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_Port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkManager, nullptr, "ConnectToServer", nullptr, nullptr, Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NetworkManager_eventConnectToServer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::NetworkManager_eventConnectToServer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkManager_ConnectToServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkManager_ConnectToServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkManager::execConnectToServer)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_IPAddress);
	P_GET_PROPERTY(FIntProperty,Z_Param_Port);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->ConnectToServer(Z_Param_IPAddress,Z_Param_Port);
	P_NATIVE_END;
}
// End Class UNetworkManager Function ConnectToServer

// Begin Class UNetworkManager Function DisconnectFromServer
struct Z_Construct_UFunction_UNetworkManager_DisconnectFromServer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkManager_DisconnectFromServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkManager, nullptr, "DisconnectFromServer", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_DisconnectFromServer_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkManager_DisconnectFromServer_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UNetworkManager_DisconnectFromServer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkManager_DisconnectFromServer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkManager::execDisconnectFromServer)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DisconnectFromServer();
	P_NATIVE_END;
}
// End Class UNetworkManager Function DisconnectFromServer

// Begin Class UNetworkManager Function IsConnected
struct Z_Construct_UFunction_UNetworkManager_IsConnected_Statics
{
	struct NetworkManager_eventIsConnected_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((NetworkManager_eventIsConnected_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkManager_eventIsConnected_Parms), &Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkManager, nullptr, "IsConnected", nullptr, nullptr, Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NetworkManager_eventIsConnected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::NetworkManager_eventIsConnected_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkManager_IsConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkManager_IsConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkManager::execIsConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsConnected();
	P_NATIVE_END;
}
// End Class UNetworkManager Function IsConnected

// Begin Class UNetworkManager Function SendJumpPacket
struct Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics
{
	struct NetworkManager_eventSendJumpPacket_Parms
	{
		bool IsJumping;
		FVector Position;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((NetworkManager_eventSendJumpPacket_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(NetworkManager_eventSendJumpPacket_Parms), &Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventSendJumpPacket_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_IsJumping,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NewProp_Position,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkManager, nullptr, "SendJumpPacket", nullptr, nullptr, Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NetworkManager_eventSendJumpPacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::NetworkManager_eventSendJumpPacket_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkManager_SendJumpPacket()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkManager_SendJumpPacket_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkManager::execSendJumpPacket)
{
	P_GET_UBOOL(Z_Param_IsJumping);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendJumpPacket(Z_Param_IsJumping,Z_Param_Out_Position);
	P_NATIVE_END;
}
// End Class UNetworkManager Function SendJumpPacket

// Begin Class UNetworkManager Function SendMovePacket
struct Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics
{
	struct NetworkManager_eventSendMovePacket_Parms
	{
		float ForwardValue;
		float RightValue;
		FVector Position;
		FRotator Rotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb6 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
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
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_ForwardValue = { "ForwardValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventSendMovePacket_Parms, ForwardValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_RightValue = { "RightValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventSendMovePacket_Parms, RightValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventSendMovePacket_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(NetworkManager_eventSendMovePacket_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_ForwardValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_RightValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NewProp_Rotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNetworkManager, nullptr, "SendMovePacket", nullptr, nullptr, Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NetworkManager_eventSendMovePacket_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::NetworkManager_eventSendMovePacket_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNetworkManager_SendMovePacket()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNetworkManager_SendMovePacket_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UNetworkManager::execSendMovePacket)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_ForwardValue);
	P_GET_PROPERTY(FFloatProperty,Z_Param_RightValue);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SendMovePacket(Z_Param_ForwardValue,Z_Param_RightValue,Z_Param_Out_Position,Z_Param_Out_Rotation);
	P_NATIVE_END;
}
// End Class UNetworkManager Function SendMovePacket

// Begin Class UNetworkManager
void UNetworkManager::StaticRegisterNativesUNetworkManager()
{
	UClass* Class = UNetworkManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ConnectToServer", &UNetworkManager::execConnectToServer },
		{ "DisconnectFromServer", &UNetworkManager::execDisconnectFromServer },
		{ "IsConnected", &UNetworkManager::execIsConnected },
		{ "SendJumpPacket", &UNetworkManager::execSendJumpPacket },
		{ "SendMovePacket", &UNetworkManager::execSendMovePacket },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNetworkManager);
UClass* Z_Construct_UClass_UNetworkManager_NoRegister()
{
	return UNetworkManager::StaticClass();
}
struct Z_Construct_UClass_UNetworkManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "NetworkManager.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "NetworkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnPositionUpdate_MetaData[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "ModuleRelativePath", "NetworkManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPositionUpdate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNetworkManager_ConnectToServer, "ConnectToServer" }, // 3172435568
		{ &Z_Construct_UFunction_UNetworkManager_DisconnectFromServer, "DisconnectFromServer" }, // 3118484715
		{ &Z_Construct_UFunction_UNetworkManager_IsConnected, "IsConnected" }, // 2882788218
		{ &Z_Construct_UFunction_UNetworkManager_SendJumpPacket, "SendJumpPacket" }, // 465594146
		{ &Z_Construct_UFunction_UNetworkManager_SendMovePacket, "SendMovePacket" }, // 566363540
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNetworkManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UNetworkManager_Statics::NewProp_OnPositionUpdate = { "OnPositionUpdate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNetworkManager, OnPositionUpdate), Z_Construct_UDelegateFunction_dummy_client_OnPositionUpdate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnPositionUpdate_MetaData), NewProp_OnPositionUpdate_MetaData) }; // 723253435
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNetworkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNetworkManager_Statics::NewProp_OnPositionUpdate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNetworkManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_dummy_client,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNetworkManager_Statics::ClassParams = {
	&UNetworkManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UNetworkManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkManager_Statics::PropPointers),
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNetworkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UNetworkManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNetworkManager()
{
	if (!Z_Registration_Info_UClass_UNetworkManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNetworkManager.OuterSingleton, Z_Construct_UClass_UNetworkManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNetworkManager.OuterSingleton;
}
template<> DUMMY_CLIENT_API UClass* StaticClass<UNetworkManager>()
{
	return UNetworkManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNetworkManager);
// End Class UNetworkManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EPacketType_StaticEnum, TEXT("EPacketType"), &Z_Registration_Info_UEnum_EPacketType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 308638729U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNetworkManager, UNetworkManager::StaticClass, TEXT("UNetworkManager"), &Z_Registration_Info_UClass_UNetworkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNetworkManager), 902442288U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_1354411989(TEXT("/Script/dummy_client"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
