// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkPlayerComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class USimpleNetworkManager;
#ifdef SIMPLENETWORKING_NetworkPlayerComponent_generated_h
#error "NetworkPlayerComponent.generated.h already included, missing '#pragma once' in NetworkPlayerComponent.h"
#endif
#define SIMPLENETWORKING_NetworkPlayerComponent_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnConnectionStatusChanged); \
	DECLARE_FUNCTION(execOnJumpStateUpdateReceived); \
	DECLARE_FUNCTION(execOnRotationUpdateReceived); \
	DECLARE_FUNCTION(execOnPositionUpdateReceived); \
	DECLARE_FUNCTION(execOnOtherPlayerRemoved); \
	DECLARE_FUNCTION(execOnOtherPlayerSpawned); \
	DECLARE_FUNCTION(execOnClientIdReceived); \
	DECLARE_FUNCTION(execOnPlayerUpdateReceived); \
	DECLARE_FUNCTION(execOnNetworkDisconnected); \
	DECLARE_FUNCTION(execOnNetworkConnected); \
	DECLARE_FUNCTION(execGetOtherPlayerCount); \
	DECLARE_FUNCTION(execGetLocalClientId); \
	DECLARE_FUNCTION(execRemoveAllOtherPlayers); \
	DECLARE_FUNCTION(execRemoveOtherPlayerCharacter); \
	DECLARE_FUNCTION(execSpawnOtherPlayerCharacter); \
	DECLARE_FUNCTION(execSendJumpState); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer); \
	DECLARE_FUNCTION(execSetNetworkManager);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNetworkPlayerComponent(); \
	friend struct Z_Construct_UClass_UNetworkPlayerComponent_Statics; \
public: \
	DECLARE_CLASS(UNetworkPlayerComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), NO_API) \
	DECLARE_SERIALIZER(UNetworkPlayerComponent)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNetworkPlayerComponent(UNetworkPlayerComponent&&); \
	UNetworkPlayerComponent(const UNetworkPlayerComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNetworkPlayerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNetworkPlayerComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNetworkPlayerComponent) \
	NO_API virtual ~UNetworkPlayerComponent();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_11_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class UNetworkPlayerComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_NetworkPlayerComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
