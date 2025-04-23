#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimpleNetworkingModule : public IModuleInterface
{
public:
    /** IModuleInterface 구현 */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};