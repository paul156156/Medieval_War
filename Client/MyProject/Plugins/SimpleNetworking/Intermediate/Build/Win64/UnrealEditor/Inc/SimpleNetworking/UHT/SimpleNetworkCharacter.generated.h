// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SimpleNetworkCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef SIMPLENETWORKING_SimpleNetworkCharacter_generated_h
#error "SimpleNetworkCharacter.generated.h already included, missing '#pragma once' in SimpleNetworkCharacter.h"
#endif
#define SIMPLENETWORKING_SimpleNetworkCharacter_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnConnectionStatusChanged); \
	DECLARE_FUNCTION(execGetOtherPlayerCount); \
	DECLARE_FUNCTION(execGetLocalClientId); \
	DECLARE_FUNCTION(execRemoveAllOtherPlayers); \
	DECLARE_FUNCTION(execRemoveOtherPlayerCharacter); \
	DECLARE_FUNCTION(execSpawnOtherPlayerCharacter);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASimpleNetworkCharacter(); \
	friend struct Z_Construct_UClass_ASimpleNetworkCharacter_Statics; \
public: \
	DECLARE_CLASS(ASimpleNetworkCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), NO_API) \
	DECLARE_SERIALIZER(ASimpleNetworkCharacter)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ASimpleNetworkCharacter(ASimpleNetworkCharacter&&); \
	ASimpleNetworkCharacter(const ASimpleNetworkCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASimpleNetworkCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASimpleNetworkCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASimpleNetworkCharacter) \
	NO_API virtual ~ASimpleNetworkCharacter();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_12_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class ASimpleNetworkCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
