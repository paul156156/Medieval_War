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
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientCharacter();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_Adummy_clientCharacter_NoRegister();
DUMMY_CLIENT_API UClass* Z_Construct_UClass_UNetworkManager_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_dummy_client();
// End Cross Module References

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
		{ "Comment", "/** \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd */" },
#endif
		{ "ModuleRelativePath", "dummy_clientCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd" },
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

// Begin Class Adummy_clientCharacter Function SpawnOtherPlayerCharacter
struct dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms
{
	FVector Position;
};
static const FName NAME_Adummy_clientCharacter_SpawnOtherPlayerCharacter = FName(TEXT("SpawnOtherPlayerCharacter"));
void Adummy_clientCharacter::SpawnOtherPlayerCharacter(FVector const& Position)
{
	dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms Parms;
	Parms.Position=Position;
	UFunction* Func = FindFunctionChecked(NAME_Adummy_clientCharacter_SpawnOtherPlayerCharacter);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xd9\xb8\xef\xbf\xbd \xef\xbf\xbd\xc3\xb7\xef\xbf\xbd\xef\xbf\xbd\xcc\xbe\xef\xbf\xbd \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xce\xba\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
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
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::NewProp_Position,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_Adummy_clientCharacter, nullptr, "SpawnOtherPlayerCharacter", nullptr, nullptr, Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::PropPointers), sizeof(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C20800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams), Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::Function_MetaDataParams) };
static_assert(sizeof(dummy_clientCharacter_eventSpawnOtherPlayerCharacter_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class Adummy_clientCharacter Function SpawnOtherPlayerCharacter

// Begin Class Adummy_clientCharacter
void Adummy_clientCharacter::StaticRegisterNativesAdummy_clientCharacter()
{
	UClass* Class = Adummy_clientCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnPositionUpdateReceived", &Adummy_clientCharacter::execOnPositionUpdateReceived },
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
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseTurnRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseLookUpRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_Adummy_clientCharacter_OnPositionUpdateReceived, "OnPositionUpdateReceived" }, // 1820151712
		{ &Z_Construct_UFunction_Adummy_clientCharacter_SpawnOtherPlayerCharacter, "SpawnOtherPlayerCharacter" }, // 2132919159
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
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseTurnRate = { "BaseTurnRate", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, BaseTurnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseTurnRate_MetaData), NewProp_BaseTurnRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_BaseLookUpRate = { "BaseLookUpRate", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Adummy_clientCharacter, BaseLookUpRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseLookUpRate_MetaData), NewProp_BaseLookUpRate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_Adummy_clientCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_NetworkManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_bEnableNetworkUpdates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_Adummy_clientCharacter_Statics::NewProp_PositionUpdateInterval,
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
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_Adummy_clientCharacter, Adummy_clientCharacter::StaticClass, TEXT("Adummy_clientCharacter"), &Z_Registration_Info_UClass_Adummy_clientCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(Adummy_clientCharacter), 2181745723U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_1874983011(TEXT("/Script/dummy_client"),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
