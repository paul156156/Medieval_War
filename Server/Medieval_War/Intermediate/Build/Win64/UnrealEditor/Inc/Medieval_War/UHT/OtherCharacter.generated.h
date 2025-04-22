// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OtherCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef MEDIEVAL_WAR_OtherCharacter_generated_h
#error "OtherCharacter.generated.h already included, missing '#pragma once' in OtherCharacter.h"
#endif
#define MEDIEVAL_WAR_OtherCharacter_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execUpdateTransform); \
	DECLARE_FUNCTION(execUpdateAnimationState);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_CALLBACK_WRAPPERS
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAOtherCharacter(); \
	friend struct Z_Construct_UClass_AOtherCharacter_Statics; \
public: \
	DECLARE_CLASS(AOtherCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Medieval_War"), NO_API) \
	DECLARE_SERIALIZER(AOtherCharacter)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AOtherCharacter(AOtherCharacter&&); \
	AOtherCharacter(const AOtherCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOtherCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOtherCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AOtherCharacter) \
	NO_API virtual ~AOtherCharacter();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_9_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_CALLBACK_WRAPPERS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MEDIEVAL_WAR_API UClass* StaticClass<class AOtherCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Source_Medieval_War_OtherCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
