// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SimpleNetworkManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef SIMPLENETWORKING_SimpleNetworkManager_generated_h
#error "SimpleNetworkManager.generated.h already included, missing '#pragma once' in SimpleNetworkManager.h"
#endif
#define SIMPLENETWORKING_SimpleNetworkManager_generated_h

#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_12_DELEGATE \
SIMPLENETWORKING_API void FOnPositionUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPositionUpdate, FVector const& NewPosition);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_13_DELEGATE \
SIMPLENETWORKING_API void FOnRotationUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnRotationUpdate, FRotator const& NewRotation);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_14_DELEGATE \
SIMPLENETWORKING_API void FOnConnectionStatusChanged_DelegateWrapper(const FMulticastScriptDelegate& OnConnectionStatusChanged, bool IsConnected);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_15_DELEGATE \
SIMPLENETWORKING_API void FOnPlayerUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerUpdate, int32 ClientId, FVector const& Position, FRotator const& Rotation, EPlayerState State);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_16_DELEGATE \
SIMPLENETWORKING_API void FOnClientIdReceived_DelegateWrapper(const FMulticastScriptDelegate& OnClientIdReceived, int32 ClientId);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetClientId); \
	DECLARE_FUNCTION(execGetLastErrorCode); \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execSendAttackPacket); \
	DECLARE_FUNCTION(execSendJumpPacket); \
	DECLARE_FUNCTION(execSendMovePacket); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer);


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSimpleNetworkManager(); \
	friend struct Z_Construct_UClass_USimpleNetworkManager_Statics; \
public: \
	DECLARE_CLASS(USimpleNetworkManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), NO_API) \
	DECLARE_SERIALIZER(USimpleNetworkManager)


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USimpleNetworkManager(USimpleNetworkManager&&); \
	USimpleNetworkManager(const USimpleNetworkManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USimpleNetworkManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USimpleNetworkManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USimpleNetworkManager)


#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_18_PROLOG
#define FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class USimpleNetworkManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Desktop_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
