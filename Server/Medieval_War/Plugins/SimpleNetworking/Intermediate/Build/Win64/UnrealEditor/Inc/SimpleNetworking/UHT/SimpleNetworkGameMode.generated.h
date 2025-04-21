// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SimpleNetworkGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USimpleNetworkManager;
#ifdef SIMPLENETWORKING_SimpleNetworkGameMode_generated_h
#error "SimpleNetworkGameMode.generated.h already included, missing '#pragma once' in SimpleNetworkGameMode.h"
#endif
#define SIMPLENETWORKING_SimpleNetworkGameMode_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer); \
	DECLARE_FUNCTION(execGetNetworkManager);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASimpleNetworkGameMode(); \
	friend struct Z_Construct_UClass_ASimpleNetworkGameMode_Statics; \
public: \
	DECLARE_CLASS(ASimpleNetworkGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), NO_API) \
	DECLARE_SERIALIZER(ASimpleNetworkGameMode)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ASimpleNetworkGameMode(ASimpleNetworkGameMode&&); \
	ASimpleNetworkGameMode(const ASimpleNetworkGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASimpleNetworkGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASimpleNetworkGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASimpleNetworkGameMode) \
	NO_API virtual ~ASimpleNetworkGameMode();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_11_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class ASimpleNetworkGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Medieval_War_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
