#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class TONGSIMROBOT_API FTongSimRobotModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void PrintRuntimeMessage(const FString& Message);
};

TONGSIMROBOT_API FTongSimRobotModule& GetTongSimRobotModule();