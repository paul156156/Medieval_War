// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Dummy/OtherCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOtherCharacter() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
DUMMY_API UClass* Z_Construct_UClass_AOtherCharacter();
DUMMY_API UClass* Z_Construct_UClass_AOtherCharacter_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPlayerState();
UPackage* Z_Construct_UPackage__Script_Dummy();
// End Cross Module References

// Begin Class AOtherCharacter Function OnAnimationStateChanged
struct OtherCharacter_eventOnAnimationStateChanged_Parms
{
	EPlayerState NewState;
};
static const FName NAME_AOtherCharacter_OnAnimationStateChanged = FName(TEXT("OnAnimationStateChanged"));
void AOtherCharacter::OnAnimationStateChanged(EPlayerState NewState)
{
	OtherCharacter_eventOnAnimationStateChanged_Parms Parms;
	Parms.NewState=NewState;
	UFunction* Func = FindFunctionChecked(NAME_AOtherCharacter_OnAnimationStateChanged);
	ProcessEvent(Func,&Parms);
}
struct Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//// \xef\xbf\xbd\xd6\xb4\xcf\xb8\xef\xbf\xbd\xef\xbf\xbd\xcc\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd)\n" },
#endif
		{ "ModuleRelativePath", "OtherCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "/ \xef\xbf\xbd\xd6\xb4\xcf\xb8\xef\xbf\xbd\xef\xbf\xbd\xcc\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xba\xef\xbf\xbd\xc6\xae (\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xc3\xb3\xef\xbf\xbd\xef\xbf\xbd)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::NewProp_NewState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OtherCharacter_eventOnAnimationStateChanged_Parms, NewState), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::NewProp_NewState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOtherCharacter, nullptr, "OnAnimationStateChanged", nullptr, nullptr, Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::PropPointers), sizeof(OtherCharacter_eventOnAnimationStateChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::Function_MetaDataParams) };
static_assert(sizeof(OtherCharacter_eventOnAnimationStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
// End Class AOtherCharacter Function OnAnimationStateChanged

// Begin Class AOtherCharacter Function UpdateAnimationState
struct Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics
{
	struct OtherCharacter_eventUpdateAnimationState_Parms
	{
		EPlayerState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "OtherCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xef\xbf\xbd\xd4\xbc\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::NewProp_NewState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OtherCharacter_eventUpdateAnimationState_Parms, NewState), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(0, nullptr) }; // 3288260524
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::NewProp_NewState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOtherCharacter, nullptr, "UpdateAnimationState", nullptr, nullptr, Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::PropPointers), sizeof(Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::OtherCharacter_eventUpdateAnimationState_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::OtherCharacter_eventUpdateAnimationState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AOtherCharacter::execUpdateAnimationState)
{
	P_GET_ENUM(EPlayerState,Z_Param_NewState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateAnimationState(EPlayerState(Z_Param_NewState));
	P_NATIVE_END;
}
// End Class AOtherCharacter Function UpdateAnimationState

// Begin Class AOtherCharacter Function UpdateTransform
struct Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics
{
	struct OtherCharacter_eventUpdateTransform_Parms
	{
		FVector NewPosition;
		FRotator NewRotation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Networking" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\n" },
#endif
		{ "ModuleRelativePath", "OtherCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc4\xa1 \xef\xbf\xbd\xef\xbf\xbd \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewPosition_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewRotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewPosition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewRotation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::NewProp_NewPosition = { "NewPosition", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OtherCharacter_eventUpdateTransform_Parms, NewPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewPosition_MetaData), NewProp_NewPosition_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::NewProp_NewRotation = { "NewRotation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OtherCharacter_eventUpdateTransform_Parms, NewRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewRotation_MetaData), NewProp_NewRotation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::NewProp_NewPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::NewProp_NewRotation,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AOtherCharacter, nullptr, "UpdateTransform", nullptr, nullptr, Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::PropPointers), sizeof(Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::OtherCharacter_eventUpdateTransform_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::Function_MetaDataParams), Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::OtherCharacter_eventUpdateTransform_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AOtherCharacter_UpdateTransform()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AOtherCharacter_UpdateTransform_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AOtherCharacter::execUpdateTransform)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_NewPosition);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_NewRotation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateTransform(Z_Param_Out_NewPosition,Z_Param_Out_NewRotation);
	P_NATIVE_END;
}
// End Class AOtherCharacter Function UpdateTransform

// Begin Class AOtherCharacter
void AOtherCharacter::StaticRegisterNativesAOtherCharacter()
{
	UClass* Class = AOtherCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "UpdateAnimationState", &AOtherCharacter::execUpdateAnimationState },
		{ "UpdateTransform", &AOtherCharacter::execUpdateTransform },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AOtherCharacter);
UClass* Z_Construct_UClass_AOtherCharacter_NoRegister()
{
	return AOtherCharacter::StaticClass();
}
struct Z_Construct_UClass_AOtherCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "OtherCharacter.h" },
		{ "ModuleRelativePath", "OtherCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "Category", "Animation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "OtherCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackMontage_MetaData[] = {
		{ "Category", "Combat" },
		{ "ModuleRelativePath", "OtherCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMontage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AOtherCharacter_OnAnimationStateChanged, "OnAnimationStateChanged" }, // 1730686215
		{ &Z_Construct_UFunction_AOtherCharacter_UpdateAnimationState, "UpdateAnimationState" }, // 1090939150
		{ &Z_Construct_UFunction_AOtherCharacter_UpdateTransform, "UpdateTransform" }, // 1092108503
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AOtherCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AOtherCharacter_Statics::NewProp_CurrentState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AOtherCharacter_Statics::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOtherCharacter, CurrentState), Z_Construct_UEnum_SimpleNetworking_EPlayerState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) }; // 3288260524
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AOtherCharacter_Statics::NewProp_AttackMontage = { "AttackMontage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AOtherCharacter, AttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackMontage_MetaData), NewProp_AttackMontage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AOtherCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOtherCharacter_Statics::NewProp_CurrentState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOtherCharacter_Statics::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AOtherCharacter_Statics::NewProp_AttackMontage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AOtherCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_Dummy,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AOtherCharacter_Statics::ClassParams = {
	&AOtherCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AOtherCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AOtherCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AOtherCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AOtherCharacter()
{
	if (!Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton, Z_Construct_UClass_AOtherCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AOtherCharacter.OuterSingleton;
}
template<> DUMMY_API UClass* StaticClass<AOtherCharacter>()
{
	return AOtherCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AOtherCharacter);
AOtherCharacter::~AOtherCharacter() {}
// End Class AOtherCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Source_Dummy_OtherCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AOtherCharacter, AOtherCharacter::StaticClass, TEXT("AOtherCharacter"), &Z_Registration_Info_UClass_AOtherCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AOtherCharacter), 2556394769U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Source_Dummy_OtherCharacter_h_3107243580(TEXT("/Script/Dummy"),
	Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Source_Dummy_OtherCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Desktop_Dummy_Source_Dummy_OtherCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
