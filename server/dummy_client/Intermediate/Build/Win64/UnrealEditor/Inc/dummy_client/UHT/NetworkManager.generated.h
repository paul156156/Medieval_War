// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DUMMY_CLIENT_NetworkManager_generated_h
#error "NetworkManager.generated.h already included, missing '#pragma once' in NetworkManager.h"
#endif
#define DUMMY_CLIENT_NetworkManager_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_54_DELEGATE \
DUMMY_CLIENT_API void FOnPositionUpdate_DelegateWrapper(const FMulticastScriptDelegate& OnPositionUpdate, FVector const& NewPosition);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsConnected); \
	DECLARE_FUNCTION(execSendJumpPacket); \
	DECLARE_FUNCTION(execSendMovePacket); \
	DECLARE_FUNCTION(execDisconnectFromServer); \
	DECLARE_FUNCTION(execConnectToServer);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNetworkManager(); \
	friend struct Z_Construct_UClass_UNetworkManager_Statics; \
public: \
	DECLARE_CLASS(UNetworkManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/dummy_client"), NO_API) \
	DECLARE_SERIALIZER(UNetworkManager)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNetworkManager(UNetworkManager&&); \
	UNetworkManager(const UNetworkManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNetworkManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNetworkManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNetworkManager)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_56_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h_59_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMMY_CLIENT_API UClass* StaticClass<class UNetworkManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_server_dummy_client_Source_dummy_client_NetworkManager_h


#define FOREACH_ENUM_EPACKETTYPE(op) \
	op(EPacketType::MOVE) \
	op(EPacketType::JUMP) \
	op(EPacketType::POSITION_UPDATE) 

enum class EPacketType : uint8;
template<> struct TIsUEnumClass<EPacketType> { enum { Value = true }; };
template<> DUMMY_CLIENT_API UEnum* StaticEnum<EPacketType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
