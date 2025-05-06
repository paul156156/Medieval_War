// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EPlayerState : uint8;
#ifdef DUMMY_MyCharacter_generated_h
#error "MyCharacter.generated.h already included, missing '#pragma once' in MyCharacter.h"
#endif
#define DUMMY_MyCharacter_generated_h

#define FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_16_DELEGATE \
DUMMY_API void FOnCharacterStateChanged_DelegateWrapper(const FMulticastScriptDelegate& OnCharacterStateChanged, EPlayerState NewState, FVector const& Position, FRotator const& Rotation);


#define FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyCharacter(); \
	friend struct Z_Construct_UClass_AMyCharacter_Statics; \
public: \
	DECLARE_CLASS(AMyCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Dummy"), NO_API) \
	DECLARE_SERIALIZER(AMyCharacter)


#define FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyCharacter(AMyCharacter&&); \
	AMyCharacter(const AMyCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyCharacter) \
	NO_API virtual ~AMyCharacter();


#define FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_18_PROLOG
#define FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DUMMY_API UClass* StaticClass<class AMyCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Desktop_Dummy_Source_Dummy_MyCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
