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

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h_110_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics; \
	static class UScriptStruct* StaticStruct();


template<> SIMPLENETWORKING_API UScriptStruct* StaticStruct<struct FOtherPlayerInfo>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkTypes_h


#define FOREACH_ENUM_EPACKETTYPE(op) \
	op(EPacketType::CLIENT_ID) \
	op(EPacketType::CONNECT) \
	op(EPacketType::DISCONNECT) \
	op(EPacketType::PING) \
	op(EPacketType::PONG) \
	op(EPacketType::PLAYER_INIT_INFO) \
	op(EPacketType::PLAYER_POSITION_INFO) \
	op(EPacketType::PLAYER_INPUT_INFO) 

enum class EPacketType : uint8;
template<> struct TIsUEnumClass<EPacketType> { enum { Value = true }; };
template<> SIMPLENETWORKING_API UEnum* StaticEnum<EPacketType>();

#define FOREACH_ENUM_EPLAYERSTATE(op) \
	op(EPlayerState::IDLE) \
	op(EPlayerState::WALKING) \
	op(EPlayerState::JUMPING) \
	op(EPlayerState::ATTACKING) 

enum class EPlayerState : uint8;
template<> struct TIsUEnumClass<EPlayerState> { enum { Value = true }; };
template<> SIMPLENETWORKING_API UEnum* StaticEnum<EPlayerState>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
