// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SIMPLENETWORKING_NetworkTypes_generated_h
#error "NetworkTypes.generated.h already included, missing '#pragma once' in NetworkTypes.h"
#endif
#define SIMPLENETWORKING_NetworkTypes_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_75_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics; \
	static class UScriptStruct* StaticStruct();


template<> SIMPLENETWORKING_API UScriptStruct* StaticStruct<struct FOtherPlayerInfo>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h


#define FOREACH_ENUM_EPACKETTYPE(op) \
	op(EPacketType::CLIENT_ID) \
	op(EPacketType::POSITION_UPDATE) \
	op(EPacketType::MOVE) \
	op(EPacketType::JUMP) \
	op(EPacketType::ATTACK) 

enum class EPacketType : uint8;
template<> struct TIsUEnumClass<EPacketType> { enum { Value = true }; };
template<> SIMPLENETWORKING_API UEnum* StaticEnum<EPacketType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
