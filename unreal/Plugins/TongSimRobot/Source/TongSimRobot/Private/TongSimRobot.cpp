#include "TongSimRobot.h"

static FName TongSimRobotModuleName("TongSimRobot");

void FTongSimRobotModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("FTongSimRobotModule (Runtime) 模块已加载！"));
}

void FTongSimRobotModule::ShutdownModule()
{
    UE_LOG(LogTemp, Log, TEXT("FTongSimRobotModule (Runtime) 模块已卸载！"));
}

void FTongSimRobotModule::PrintRuntimeMessage(const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("[Runtime 模块] %s"), *Message);
}

FTongSimRobotModule& GetTongSimRobotModule()
{
    return FModuleManager::LoadModuleChecked<FTongSimRobotModule>(TongSimRobotModuleName);
}

IMPLEMENT_MODULE(FTongSimRobotModule, TongSimRobot)