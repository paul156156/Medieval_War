// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/ISimpleNetworkInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeISimpleNetworkInterface() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkInterface();
SIMPLENETWORKING_API UClass* Z_Construct_UClass_USimpleNetworkInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Interface USimpleNetworkInterface Function OnClientIdReceived
struct SimpleNetworkInterface_eventOnClientIdReceived_Parms
{
	int32 ClientId;
};
void ISimpleNetworkInterface::OnClientIdReceived(int32 ClientId)
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnClientIdReceived instead.");
}
static FName NAME_USimpleNetworkInterface_OnClientIdReceived = FName(TEXT("OnClientIdReceived"));
void ISimpleNetworkInterface::Execute_OnClientIdReceived(UObject* O, int32 ClientId)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	SimpleNetworkInterface_eventOnClientIdReceived_Parms Parms;
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnClientIdReceived);
	if (Func)
	{
		Parms.ClientId=ClientId;
		O->ProcessEvent(Func, &Parms);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnClientIdReceived_Implementation(ClientId);
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xec\x88\x98\xec\x8b\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x81\xb4\xeb\x9d\xbc\xec\x9d\xb4\xec\x96\xb8\xed\x8a\xb8 ID \xec\x88\x98\xec\x8b\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnClientIdReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnClientIdReceived", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::PropPointers), sizeof(SimpleNetworkInterface_eventOnClientIdReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(SimpleNetworkInterface_eventOnClientIdReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnClientIdReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnClientIdReceived_Implementation(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnClientIdReceived

// Begin Interface USimpleNetworkInterface Function OnNetworkConnected
void ISimpleNetworkInterface::OnNetworkConnected()
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnNetworkConnected instead.");
}
static FName NAME_USimpleNetworkInterface_OnNetworkConnected = FName(TEXT("OnNetworkConnected"));
void ISimpleNetworkInterface::Execute_OnNetworkConnected(UObject* O)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnNetworkConnected);
	if (Func)
	{
		O->ProcessEvent(Func, NULL);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnNetworkConnected_Implementation();
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\xb0\xea\xb2\xb0\xeb\x90\xa8 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\xb0\xea\xb2\xb0\xeb\x90\xa8 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnNetworkConnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnNetworkConnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnNetworkConnected_Implementation();
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnNetworkConnected

// Begin Interface USimpleNetworkInterface Function OnNetworkDisconnected
void ISimpleNetworkInterface::OnNetworkDisconnected()
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnNetworkDisconnected instead.");
}
static FName NAME_USimpleNetworkInterface_OnNetworkDisconnected = FName(TEXT("OnNetworkDisconnected"));
void ISimpleNetworkInterface::Execute_OnNetworkDisconnected(UObject* O)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnNetworkDisconnected);
	if (Func)
	{
		O->ProcessEvent(Func, NULL);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnNetworkDisconnected_Implementation();
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c\xeb\x90\xa8 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x84\xa4\xed\x8a\xb8\xec\x9b\x8c\xed\x81\xac \xec\x97\xb0\xea\xb2\xb0 \xed\x95\xb4\xec\xa0\x9c\xeb\x90\xa8 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnNetworkDisconnected", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnNetworkDisconnected)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnNetworkDisconnected_Implementation();
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnNetworkDisconnected

// Begin Interface USimpleNetworkInterface Function OnOtherPlayerRemoved
struct SimpleNetworkInterface_eventOnOtherPlayerRemoved_Parms
{
	int32 ClientId;
};
void ISimpleNetworkInterface::OnOtherPlayerRemoved(int32 ClientId)
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnOtherPlayerRemoved instead.");
}
static FName NAME_USimpleNetworkInterface_OnOtherPlayerRemoved = FName(TEXT("OnOtherPlayerRemoved"));
void ISimpleNetworkInterface::Execute_OnOtherPlayerRemoved(UObject* O, int32 ClientId)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	SimpleNetworkInterface_eventOnOtherPlayerRemoved_Parms Parms;
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnOtherPlayerRemoved);
	if (Func)
	{
		Parms.ClientId=ClientId;
		O->ProcessEvent(Func, &Parms);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnOtherPlayerRemoved_Implementation(ClientId);
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x9c\xea\xb1\xb0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnOtherPlayerRemoved_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnOtherPlayerRemoved", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::PropPointers), sizeof(SimpleNetworkInterface_eventOnOtherPlayerRemoved_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::Function_MetaDataParams) };
static_assert(sizeof(SimpleNetworkInterface_eventOnOtherPlayerRemoved_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnOtherPlayerRemoved)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOtherPlayerRemoved_Implementation(Z_Param_ClientId);
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnOtherPlayerRemoved

// Begin Interface USimpleNetworkInterface Function OnOtherPlayerSpawned
struct SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms
{
	AActor* OtherPlayerActor;
	int32 ClientId;
};
void ISimpleNetworkInterface::OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId)
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnOtherPlayerSpawned instead.");
}
static FName NAME_USimpleNetworkInterface_OnOtherPlayerSpawned = FName(TEXT("OnOtherPlayerSpawned"));
void ISimpleNetworkInterface::Execute_OnOtherPlayerSpawned(UObject* O, AActor* OtherPlayerActor, int32 ClientId)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms Parms;
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnOtherPlayerSpawned);
	if (Func)
	{
		Parms.OtherPlayerActor=OtherPlayerActor;
		Parms.ClientId=ClientId;
		O->ProcessEvent(Func, &Parms);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnOtherPlayerSpawned_Implementation(OtherPlayerActor,ClientId);
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\x83\x9d\xec\x84\xb1 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\x83\x9d\xec\x84\xb1 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPlayerActor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor = { "OtherPlayerActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms, OtherPlayerActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::NewProp_OtherPlayerActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::NewProp_ClientId,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnOtherPlayerSpawned", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::PropPointers), sizeof(SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::Function_MetaDataParams) };
static_assert(sizeof(SimpleNetworkInterface_eventOnOtherPlayerSpawned_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnOtherPlayerSpawned)
{
	P_GET_OBJECT(AActor,Z_Param_OtherPlayerActor);
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnOtherPlayerSpawned_Implementation(Z_Param_OtherPlayerActor,Z_Param_ClientId);
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnOtherPlayerSpawned

// Begin Interface USimpleNetworkInterface Function OnPlayerUpdateReceived
struct SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms
{
	int32 ClientId;
	FVector Position;
	FRotator Rotation;
	FVector Velocity;
	bool IsJumping;
};
void ISimpleNetworkInterface::OnPlayerUpdateReceived(int32 ClientId, FVector const& Position, FRotator const& Rotation, FVector const& Velocity, bool IsJumping)
{
	check(0 && "Do not directly call Event functions in Interfaces. Call Execute_OnPlayerUpdateReceived instead.");
}
static FName NAME_USimpleNetworkInterface_OnPlayerUpdateReceived = FName(TEXT("OnPlayerUpdateReceived"));
void ISimpleNetworkInterface::Execute_OnPlayerUpdateReceived(UObject* O, int32 ClientId, FVector const& Position, FRotator const& Rotation, FVector const& Velocity, bool IsJumping)
{
	check(O != NULL);
	check(O->GetClass()->ImplementsInterface(USimpleNetworkInterface::StaticClass()));
	SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms Parms;
	UFunction* const Func = O->FindFunction(NAME_USimpleNetworkInterface_OnPlayerUpdateReceived);
	if (Func)
	{
		Parms.ClientId=ClientId;
		Parms.Position=Position;
		Parms.Rotation=Rotation;
		Parms.Velocity=Velocity;
		Parms.IsJumping=IsJumping;
		O->ProcessEvent(Func, &Parms);
	}
	else if (auto I = (ISimpleNetworkInterface*)(O->GetNativeInterfaceAddress(USimpleNetworkInterface::StaticClass())))
	{
		I->OnPlayerUpdateReceived_Implementation(ClientId,Position,Rotation,Velocity,IsJumping);
	}
}
struct Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xec\x88\x98\xec\x8b\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8\n" },
#endif
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\x97\x85\xeb\x8d\xb0\xec\x9d\xb4\xed\x8a\xb8 \xec\x88\x98\xec\x8b\xa0 \xec\x9d\xb4\xeb\xb2\xa4\xed\x8a\xb8" },
#endif
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
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms, ClientId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms, Rotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rotation_MetaData), NewProp_Rotation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
void Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms), &Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Rotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USimpleNetworkInterface, nullptr, "OnPlayerUpdateReceived", nullptr, nullptr, Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::PropPointers), sizeof(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C20C00, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::Function_MetaDataParams), Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::Function_MetaDataParams) };
static_assert(sizeof(SimpleNetworkInterface_eventOnPlayerUpdateReceived_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ISimpleNetworkInterface::execOnPlayerUpdateReceived)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_ClientId);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Position);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_Rotation);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Velocity);
	P_GET_UBOOL(Z_Param_IsJumping);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPlayerUpdateReceived_Implementation(Z_Param_ClientId,Z_Param_Out_Position,Z_Param_Out_Rotation,Z_Param_Out_Velocity,Z_Param_IsJumping);
	P_NATIVE_END;
}
// End Interface USimpleNetworkInterface Function OnPlayerUpdateReceived

// Begin Interface USimpleNetworkInterface
void USimpleNetworkInterface::StaticRegisterNativesUSimpleNetworkInterface()
{
	UClass* Class = USimpleNetworkInterface::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnClientIdReceived", &ISimpleNetworkInterface::execOnClientIdReceived },
		{ "OnNetworkConnected", &ISimpleNetworkInterface::execOnNetworkConnected },
		{ "OnNetworkDisconnected", &ISimpleNetworkInterface::execOnNetworkDisconnected },
		{ "OnOtherPlayerRemoved", &ISimpleNetworkInterface::execOnOtherPlayerRemoved },
		{ "OnOtherPlayerSpawned", &ISimpleNetworkInterface::execOnOtherPlayerSpawned },
		{ "OnPlayerUpdateReceived", &ISimpleNetworkInterface::execOnPlayerUpdateReceived },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USimpleNetworkInterface);
UClass* Z_Construct_UClass_USimpleNetworkInterface_NoRegister()
{
	return USimpleNetworkInterface::StaticClass();
}
struct Z_Construct_UClass_USimpleNetworkInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/ISimpleNetworkInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnClientIdReceived, "OnClientIdReceived" }, // 3373801657
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkConnected, "OnNetworkConnected" }, // 331529065
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnNetworkDisconnected, "OnNetworkDisconnected" }, // 898400039
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerRemoved, "OnOtherPlayerRemoved" }, // 1961704393
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnOtherPlayerSpawned, "OnOtherPlayerSpawned" }, // 1220585662
		{ &Z_Construct_UFunction_USimpleNetworkInterface_OnPlayerUpdateReceived, "OnPlayerUpdateReceived" }, // 2755168464
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ISimpleNetworkInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USimpleNetworkInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USimpleNetworkInterface_Statics::ClassParams = {
	&USimpleNetworkInterface::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USimpleNetworkInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_USimpleNetworkInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USimpleNetworkInterface()
{
	if (!Z_Registration_Info_UClass_USimpleNetworkInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USimpleNetworkInterface.OuterSingleton, Z_Construct_UClass_USimpleNetworkInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USimpleNetworkInterface.OuterSingleton;
}
template<> SIMPLENETWORKING_API UClass* StaticClass<USimpleNetworkInterface>()
{
	return USimpleNetworkInterface::StaticClass();
}
USimpleNetworkInterface::USimpleNetworkInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USimpleNetworkInterface);
USimpleNetworkInterface::~USimpleNetworkInterface() {}
// End Interface USimpleNetworkInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USimpleNetworkInterface, USimpleNetworkInterface::StaticClass, TEXT("USimpleNetworkInterface"), &Z_Registration_Info_UClass_USimpleNetworkInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USimpleNetworkInterface), 1888866136U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_4130106646(TEXT("/Script/SimpleNetworking"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
