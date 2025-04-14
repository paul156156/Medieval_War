// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "dummy_clientGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UNetworkManager;
#ifdef DUMMY_CLIENT_dummy_clientGameMode_generated_h
#error "dummy_clientGameMode.generated.h already included, missing '#pragma once' in dummy_clientGameMode.h"
#endif
#define DUMMY_CLIENT_dummy_clientGameMode_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer); \
	DECLARE_FUNCTION(execGetNetworkManager);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_CALLBACK_WRAPPERS
#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAdummy_clientGameMode(); \
	friend struct Z_Construct_UClass_Adummy_clientGameMode_Statics; \
public: \
	DECLARE_CLASS(Adummy_clientGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/dummy_client"), DUMMY_CLIENT_API) \
	DECLARE_SERIALIZER(Adummy_clientGameMode)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	Adummy_clientGameMode(Adummy_clientGameMode&&); \
	Adummy_clientGameMode(const Adummy_clientGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(DUMMY_CLIENT_API, Adummy_clientGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Adummy_clientGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Adummy_clientGameMode) \
	DUMMY_CLIENT_API virtual ~Adummy_clientGameMode();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_10_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_CALLBACK_WRAPPERS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMMY_CLIENT_API UClass* StaticClass<class Adummy_clientGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_dummy_clientGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
