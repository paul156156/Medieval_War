// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GamePlay/MyPlayerController.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYPROJECT_MyPlayerController_generated_h
#error "MyPlayerController.generated.h already included, missing '#pragma once' in MyPlayerController.h"
#endif
#define MYPROJECT_MyPlayerController_generated_h

#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyPlayerController(); \
	friend struct Z_Construct_UClass_AMyPlayerController_Statics; \
public: \
	DECLARE_CLASS(AMyPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API) \
	DECLARE_SERIALIZER(AMyPlayerController)


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AMyPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AMyPlayerController(AMyPlayerController&&); \
	AMyPlayerController(const AMyPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyPlayerController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AMyPlayerController) \
	NO_API virtual ~AMyPlayerController();


#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_12_PROLOG
#define FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> MYPROJECT_API UClass* StaticClass<class AMyPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Blues_Documents_GitHub_Medieval_War_Client_MyProject_Source_MyProject_Private_GamePlay_MyPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
