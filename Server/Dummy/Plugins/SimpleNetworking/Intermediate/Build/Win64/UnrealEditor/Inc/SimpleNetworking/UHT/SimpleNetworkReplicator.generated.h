// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SimpleNetworkReplicator.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef SIMPLENETWORKING_SimpleNetworkReplicator_generated_h
#error "SimpleNetworkReplicator.generated.h already included, missing '#pragma once' in SimpleNetworkReplicator.h"
#endif
#define SIMPLENETWORKING_SimpleNetworkReplicator_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_12_DELEGATE \
SIMPLENETWORKING_API void FOnClientIdAssigned_DelegateWrapper(const FMulticastScriptDelegate& OnClientIdAssigned, int32 ClientId);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_17_DELEGATE \
SIMPLENETWORKING_API void FOnPlayerDisconnected_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerDisconnected, int32 ClientId);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_25_DELEGATE \
SIMPLENETWORKING_API void FOnMyInitialPositionReceived_DelegateWrapper(const FMulticastScriptDelegate& OnMyInitialPositionReceived, int32 ClientId, FVector Position, FVector Velocity, EPlayerState State);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_36_DELEGATE \
SIMPLENETWORKING_API void FOnPlayerPositionUpdated_DelegateWrapper(const FMulticastScriptDelegate& OnPlayerPositionUpdated, int32 ClientId, FVector NewPosition, float NewYaw, float NewRoll, FVector NewVelocity, EPlayerState State, float Timestamp);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_41_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSimpleNetworkReplicator(); \
	friend struct Z_Construct_UClass_USimpleNetworkReplicator_Statics; \
public: \
	DECLARE_CLASS(USimpleNetworkReplicator, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), NO_API) \
	DECLARE_SERIALIZER(USimpleNetworkReplicator)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_41_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USimpleNetworkReplicator(USimpleNetworkReplicator&&); \
	USimpleNetworkReplicator(const USimpleNetworkReplicator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USimpleNetworkReplicator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USimpleNetworkReplicator); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USimpleNetworkReplicator) \
	NO_API virtual ~USimpleNetworkReplicator();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_38_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_41_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_41_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h_41_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class USimpleNetworkReplicator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Server_Dummy_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_SimpleNetworkReplicator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
