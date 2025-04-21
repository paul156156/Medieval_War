// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkTypes() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
SIMPLENETWORKING_API UEnum* Z_Construct_UEnum_SimpleNetworking_EPacketType();
SIMPLENETWORKING_API UScriptStruct* Z_Construct_UScriptStruct_FOtherPlayerInfo();
UPackage* Z_Construct_UPackage__Script_SimpleNetworking();
// End Cross Module References

// Begin Enum EPacketType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPacketType;
static UEnum* EPacketType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EPacketType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EPacketType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SimpleNetworking_EPacketType, (UObject*)Z_Construct_UPackage__Script_SimpleNetworking(), TEXT("EPacketType"));
	}
	return Z_Registration_Info_UEnum_EPacketType.OuterSingleton;
}
template<> SIMPLENETWORKING_API UEnum* StaticEnum<EPacketType>()
{
	return EPacketType_StaticEnum();
}
struct Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CLIENT_ID.Name", "EPacketType::CLIENT_ID" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xed\x8c\xa8\xed\x82\xb7 \xed\x83\x80\xec\x9e\x85 \xec\xa0\x95\xec\x9d\x98 (\xec\x84\x9c\xeb\xb2\x84\xec\x99\x80 \xeb\x8f\x99\xec\x9d\xbc\xed\x95\x98\xea\xb2\x8c \xeb\xa7\x9e\xec\xb6\xb0\xec\x95\xbc \xed\x95\xa8)\n" },
#endif
		{ "JUMP.Name", "EPacketType::JUMP" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
		{ "MOVE.Name", "EPacketType::MOVE" },
		{ "POSITION_UPDATE.Name", "EPacketType::POSITION_UPDATE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xed\x8c\xa8\xed\x82\xb7 \xed\x83\x80\xec\x9e\x85 \xec\xa0\x95\xec\x9d\x98 (\xec\x84\x9c\xeb\xb2\x84\xec\x99\x80 \xeb\x8f\x99\xec\x9d\xbc\xed\x95\x98\xea\xb2\x8c \xeb\xa7\x9e\xec\xb6\xb0\xec\x95\xbc \xed\x95\xa8)" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EPacketType::CLIENT_ID", (int64)EPacketType::CLIENT_ID },
		{ "EPacketType::MOVE", (int64)EPacketType::MOVE },
		{ "EPacketType::JUMP", (int64)EPacketType::JUMP },
		{ "EPacketType::POSITION_UPDATE", (int64)EPacketType::POSITION_UPDATE },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_SimpleNetworking,
	nullptr,
	"EPacketType",
	"EPacketType",
	Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_SimpleNetworking_EPacketType()
{
	if (!Z_Registration_Info_UEnum_EPacketType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPacketType.InnerSingleton, Z_Construct_UEnum_SimpleNetworking_EPacketType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EPacketType.InnerSingleton;
}
// End Enum EPacketType

// Begin ScriptStruct FOtherPlayerInfo
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_OtherPlayerInfo;
class UScriptStruct* FOtherPlayerInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FOtherPlayerInfo, (UObject*)Z_Construct_UPackage__Script_SimpleNetworking(), TEXT("OtherPlayerInfo"));
	}
	return Z_Registration_Info_UScriptStruct_OtherPlayerInfo.OuterSingleton;
}
template<> SIMPLENETWORKING_API UScriptStruct* StaticStruct<FOtherPlayerInfo>()
{
	return FOtherPlayerInfo::StaticStruct();
}
struct Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x95\xeb\xb3\xb4 \xec\xa0\x80\xec\x9e\xa5 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4\n" },
#endif
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xeb\x8b\xa4\xeb\xa5\xb8 \xed\x94\x8c\xeb\xa0\x88\xec\x9d\xb4\xec\x96\xb4 \xec\xa0\x95\xeb\xb3\xb4 \xec\xa0\x80\xec\x9e\xa5 \xea\xb5\xac\xec\xa1\xb0\xec\xb2\xb4" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClientId_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPosition_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetRotation_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PositionInterpolationTime_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationInterpolationTime_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IsJumping_MetaData[] = {
		{ "Category", "Networking" },
		{ "ModuleRelativePath", "Public/NetworkTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClientId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPosition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PositionInterpolationTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationInterpolationTime;
	static void NewProp_IsJumping_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_IsJumping;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FOtherPlayerInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_ClientId = { "ClientId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOtherPlayerInfo, ClientId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClientId_MetaData), NewProp_ClientId_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_TargetPosition = { "TargetPosition", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOtherPlayerInfo, TargetPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPosition_MetaData), NewProp_TargetPosition_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_TargetRotation = { "TargetRotation", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOtherPlayerInfo, TargetRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetRotation_MetaData), NewProp_TargetRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_PositionInterpolationTime = { "PositionInterpolationTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOtherPlayerInfo, PositionInterpolationTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PositionInterpolationTime_MetaData), NewProp_PositionInterpolationTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_RotationInterpolationTime = { "RotationInterpolationTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FOtherPlayerInfo, RotationInterpolationTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationInterpolationTime_MetaData), NewProp_RotationInterpolationTime_MetaData) };
void Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_IsJumping_SetBit(void* Obj)
{
	((FOtherPlayerInfo*)Obj)->IsJumping = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_IsJumping = { "IsJumping", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FOtherPlayerInfo), &Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_IsJumping_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IsJumping_MetaData), NewProp_IsJumping_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_ClientId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_TargetPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_TargetRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_PositionInterpolationTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_RotationInterpolationTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewProp_IsJumping,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_SimpleNetworking,
	nullptr,
	&NewStructOps,
	"OtherPlayerInfo",
	Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::PropPointers),
	sizeof(FOtherPlayerInfo),
	alignof(FOtherPlayerInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
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

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EPacketType_StaticEnum, TEXT("EPacketType"), &Z_Registration_Info_UEnum_EPacketType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2359833436U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FOtherPlayerInfo::StaticStruct, Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics::NewStructOps, TEXT("OtherPlayerInfo"), &Z_Registration_Info_UScriptStruct_OtherPlayerInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FOtherPlayerInfo), 4218889607U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_1373325060(TEXT("/Script/SimpleNetworking"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
