// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "dummy_clientCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef DUMMY_CLIENT_dummy_clientCharacter_generated_h
#error "dummy_clientCharacter.generated.h already included, missing '#pragma once' in dummy_clientCharacter.h"
#endif
#define DUMMY_CLIENT_dummy_clientCharacter_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FOtherPlayerInfo_Statics; \
	DUMMY_CLIENT_API static class UScriptStruct* StaticStruct();


template<> DUMMY_CLIENT_API UScriptStruct* StaticStruct<struct FOtherPlayerInfo>();

#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRemoveAllOtherPlayers); \
	DECLARE_FUNCTION(execSpawnOtherPlayerCharacter); \
	DECLARE_FUNCTION(execGetOtherPlayerCount); \
	DECLARE_FUNCTION(execGetLocalClientId); \
	DECLARE_FUNCTION(execRemoveOtherPlayerCharacter); \
	DECLARE_FUNCTION(execOnConnectionStatusChanged); \
	DECLARE_FUNCTION(execOnJumpStateUpdateReceived); \
	DECLARE_FUNCTION(execOnRotationUpdateReceived); \
	DECLARE_FUNCTION(execOnPositionUpdateReceived); \
	DECLARE_FUNCTION(execOnPlayerUpdateReceived); \
	DECLARE_FUNCTION(execOnClientIdReceived);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_CALLBACK_WRAPPERS
#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAdummy_clientCharacter(); \
	friend struct Z_Construct_UClass_Adummy_clientCharacter_Statics; \
public: \
	DECLARE_CLASS(Adummy_clientCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/dummy_client"), NO_API) \
	DECLARE_SERIALIZER(Adummy_clientCharacter)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	Adummy_clientCharacter(Adummy_clientCharacter&&); \
	Adummy_clientCharacter(const Adummy_clientCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Adummy_clientCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Adummy_clientCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Adummy_clientCharacter) \
	NO_API virtual ~Adummy_clientCharacter();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_33_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_CALLBACK_WRAPPERS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h_36_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMMY_CLIENT_API UClass* StaticClass<class Adummy_clientCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
