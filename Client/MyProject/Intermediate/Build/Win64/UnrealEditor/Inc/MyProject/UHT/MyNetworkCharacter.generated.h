// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GamePlay/MyNetworkCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYPROJECT_MyNetworkCharacter_generated_h
#error "MyNetworkCharacter.generated.h already included, missing '#pragma once' in MyNetworkCharacter.h"
#endif
#define MYPROJECT_MyNetworkCharacter_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnClientIdReceived); \
	DECLARE_FUNCTION(execOnPlayerUpdateReceived); \
	DECLARE_FUNCTION(execOnConnectionStatusChanged); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyNetworkCharacter(); \
	friend struct Z_Construct_UClass_AMyNetworkCharacter_Statics; \
public: \
	DECLARE_CLASS(AMyNetworkCharacter, AMyCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AMyNetworkCharacter)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyNetworkCharacter(AMyNetworkCharacter&&); \
	AMyNetworkCharacter(const AMyNetworkCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyNetworkCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyNetworkCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyNetworkCharacter) \
	NO_API virtual ~AMyNetworkCharacter();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_13_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class AMyNetworkCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyNetworkCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
