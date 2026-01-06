#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class TONGSIMROBOTEDITOR_API FTongSimRobotEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void PrintEditorMessage(const FString& Message);
};

TONGSIMROBOTEDITOR_API FTongSimRobotEditorModule& GetTongSimRobotEditorModule();