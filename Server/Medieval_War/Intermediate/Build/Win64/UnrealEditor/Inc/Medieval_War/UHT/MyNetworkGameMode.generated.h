// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyNetworkGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef MEDIEVAL_WAR_MyNetworkGameMode_generated_h
#error "MyNetworkGameMode.generated.h already included, missing '#pragma once' in MyNetworkGameMode.h"
#endif
#define MEDIEVAL_WAR_MyNetworkGameMode_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnConnectionStatusChanged); \
	DECLARE_FUNCTION(execOnClientIdReceived); \
	DECLARE_FUNCTION(execOnPlayerUpdateReceived); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer); \
	DECLARE_FUNCTION(execOnCharacterStateChanged);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_CALLBACK_WRAPPERS
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyNetworkGameMode(); \
	friend struct Z_Construct_UClass_AMyNetworkGameMode_Statics; \
public: \
	DECLARE_CLASS(AMyNetworkGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Medieval_War"), NO_API) \
	DECLARE_SERIALIZER(AMyNetworkGameMode)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyNetworkGameMode(AMyNetworkGameMode&&); \
	AMyNetworkGameMode(const AMyNetworkGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyNetworkGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyNetworkGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyNetworkGameMode) \
	NO_API virtual ~AMyNetworkGameMode();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_13_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_CALLBACK_WRAPPERS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MEDIEVAL_WAR_API UClass* StaticClass<class AMyNetworkGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
