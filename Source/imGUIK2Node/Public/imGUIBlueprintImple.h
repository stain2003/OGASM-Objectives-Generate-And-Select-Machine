#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FimGUIK2NodeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
