// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ISimpleNetworkInterface.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef SIMPLENETWORKING_ISimpleNetworkInterface_generated_h
#error "ISimpleNetworkInterface.generated.h already included, missing '#pragma once' in ISimpleNetworkInterface.h"
#endif
#define SIMPLENETWORKING_ISimpleNetworkInterface_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual void OnOtherPlayerRemoved_Implementation(int32 ClientId) {}; \
	virtual void OnOtherPlayerSpawned_Implementation(AActor* OtherPlayerActor, int32 ClientId) {}; \
	virtual void OnClientIdReceived_Implementation(int32 ClientId) {}; \
	virtual void OnPlayerUpdateReceived_Implementation(int32 ClientId, FVector const& Position, FRotator const& Rotation, FVector const& Velocity, bool IsJumping) {}; \
	virtual void OnNetworkDisconnected_Implementation() {}; \
	virtual void OnNetworkConnected_Implementation() {}; \
	DECLARE_FUNCTION(execOnOtherPlayerRemoved); \
	DECLARE_FUNCTION(execOnOtherPlayerSpawned); \
	DECLARE_FUNCTION(execOnClientIdReceived); \
	DECLARE_FUNCTION(execOnPlayerUpdateReceived); \
	DECLARE_FUNCTION(execOnNetworkDisconnected); \
	DECLARE_FUNCTION(execOnNetworkConnected);


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_CALLBACK_WRAPPERS
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	SIMPLENETWORKING_API USimpleNetworkInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USimpleNetworkInterface(USimpleNetworkInterface&&); \
	USimpleNetworkInterface(const USimpleNetworkInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(SIMPLENETWORKING_API, USimpleNetworkInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USimpleNetworkInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USimpleNetworkInterface) \
	SIMPLENETWORKING_API virtual ~USimpleNetworkInterface();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUSimpleNetworkInterface(); \
	friend struct Z_Construct_UClass_USimpleNetworkInterface_Statics; \
public: \
	DECLARE_CLASS(USimpleNetworkInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/SimpleNetworking"), SIMPLENETWORKING_API) \
	DECLARE_SERIALIZER(USimpleNetworkInterface)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_GENERATED_UINTERFACE_BODY() \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~ISimpleNetworkInterface() {} \
public: \
	typedef USimpleNetworkInterface UClassType; \
	typedef ISimpleNetworkInterface ThisClass; \
	static void Execute_OnClientIdReceived(UObject* O, int32 ClientId); \
	static void Execute_OnNetworkConnected(UObject* O); \
	static void Execute_OnNetworkDisconnected(UObject* O); \
	static void Execute_OnOtherPlayerRemoved(UObject* O, int32 ClientId); \
	static void Execute_OnOtherPlayerSpawned(UObject* O, AActor* OtherPlayerActor, int32 ClientId); \
	static void Execute_OnPlayerUpdateReceived(UObject* O, int32 ClientId, FVector const& Position, FRotator const& Rotation, FVector const& Velocity, bool IsJumping); \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_9_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_CALLBACK_WRAPPERS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIMPLENETWORKING_API UClass* StaticClass<class USimpleNetworkInterface>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Plugins_SimpleNetworking_Source_SimpleNetworking_Public_ISimpleNetworkInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
