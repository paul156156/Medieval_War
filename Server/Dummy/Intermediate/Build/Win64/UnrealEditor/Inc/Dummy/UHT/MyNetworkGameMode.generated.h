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
#ifdef DUMMY_MyNetworkGameMode_generated_h
#error "MyNetworkGameMode.generated.h already included, missing '#pragma once' in MyNetworkGameMode.h"
#endif
#define DUMMY_MyNetworkGameMode_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleInitialPositionReceived); \
	DECLARE_FUNCTION(execHandlePlayerPositionUpdated); \
	DECLARE_FUNCTION(execHandlePlayerDisconnected); \
	DECLARE_FUNCTION(execHandleClientIdAssigned); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyNetworkGameMode(); \
	friend struct Z_Construct_UClass_AMyNetworkGameMode_Statics; \
public: \
	DECLARE_CLASS(AMyNetworkGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Dummy"), NO_API) \
	DECLARE_SERIALIZER(AMyNetworkGameMode)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyNetworkGameMode(AMyNetworkGameMode&&); \
	AMyNetworkGameMode(const AMyNetworkGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyNetworkGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyNetworkGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyNetworkGameMode) \
	NO_API virtual ~AMyNetworkGameMode();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_15_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMMY_API UClass* StaticClass<class AMyNetworkGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Source_Dummy_MyNetworkGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
