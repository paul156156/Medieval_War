// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyNetworkCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MEDIEVAL_WAR_MyNetworkCharacter_generated_h
#error "MyNetworkCharacter.generated.h already included, missing '#pragma once' in MyNetworkCharacter.h"
#endif
#define MEDIEVAL_WAR_MyNetworkCharacter_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyNetworkCharacter(); \
	friend struct Z_Construct_UClass_AMyNetworkCharacter_Statics; \
public: \
	DECLARE_CLASS(AMyNetworkCharacter, ASimpleNetworkCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Medieval_War"), NO_API) \
	DECLARE_SERIALIZER(AMyNetworkCharacter)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyNetworkCharacter(AMyNetworkCharacter&&); \
	AMyNetworkCharacter(const AMyNetworkCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyNetworkCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyNetworkCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyNetworkCharacter) \
	NO_API virtual ~AMyNetworkCharacter();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_12_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MEDIEVAL_WAR_API UClass* StaticClass<class AMyNetworkCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_MyNetworkCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
