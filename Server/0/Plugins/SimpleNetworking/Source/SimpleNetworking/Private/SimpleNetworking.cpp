#include "SimpleNetworking.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FSimpleNetworkingModule"

void FSimpleNetworkingModule::StartupModule()
{
    // 모듈 시작시 필요한 초기화 코드
    UE_LOG(LogTemp, Log, TEXT("SimpleNetworking 모듈이 시작되었습니다."));
}

void FSimpleNetworkingModule::ShutdownModule()
{
    // 모듈 종료시 필요한 정리 코드
    UE_LOG(LogTemp, Log, TEXT("SimpleNetworking 모듈이 종료되었습니다."));
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSimpleNetworkingModule, SimpleNetworking)