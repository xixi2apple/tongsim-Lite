#include "TongSimRobotEditor.h"
#include "TongSimRobot.h"

static FName TongSimRobotEditorModuleName("TongSimRobotEditor");

void FTongSimRobotEditorModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("TongSimRobotEditor (Editor) 模块已加载！"));

    GetTongSimRobotModule().PrintRuntimeMessage("从 Editor 模块调用 Runtime 方法！");
}

void FTongSimRobotEditorModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("TongSimRobotEditor (Editor) 模块已卸载！"));
}

void FTongSimRobotEditorModule::PrintEditorMessage(const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("[Editor 模块] %s"), *Message);
}

FTongSimRobotEditorModule& GetTongSimRobotEditorModule()
{
    return FModuleManager::LoadModuleChecked<FTongSimRobotEditorModule>(TongSimRobotEditorModuleName);
}

IMPLEMENT_MODULE(FTongSimRobotEditorModule, TongSimRobotEditor)