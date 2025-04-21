// SimpleNetworkGameMode.cpp
#include "SimpleNetworkGameMode.h"
#include "SimpleNetworkManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "TimerManager.h"

ASimpleNetworkGameMode::ASimpleNetworkGameMode()
    : NetworkManager(nullptr)
    , ServerIP(TEXT("127.0.0.1"))
    , ServerPort(9000)
    , bAutoConnect(false)
    , bAutoReconnect(false)
    , ReconnectInterval(5.0f)
{
    // 기본 설정
}

void ASimpleNetworkGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // 네트워크 매니저 생성
    if (!NetworkManager)
    {
        NetworkManager = NewObject<USimpleNetworkManager>(this);
    }
    
    // 자동 연결 설정 확인
    if (bAutoConnect)
    {
        // 람다 함수를 사용한 타이머 설정
        FTimerHandle ConnectTimerHandle;
        FTimerDelegate ConnectDelegate;
        ConnectDelegate.BindLambda([this]() {
            this->ConnectToServer();
        });
        
        GetWorld()->GetTimerManager().SetTimer(
            ConnectTimerHandle,
            ConnectDelegate,
            1.0f,
            false
        );
    }
}

void ASimpleNetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 서버 연결 해제
    DisconnectFromServer();
        
    Super::EndPlay(EndPlayReason);
}

USimpleNetworkManager* ASimpleNetworkGameMode::GetNetworkManager() const
{
    return NetworkManager;
}

void ASimpleNetworkGameMode::ConnectToServer()
{
    if (!NetworkManager)
    {
        UE_LOG(LogTemp, Error, TEXT("SimpleNetworkGameMode: NetworkManager is null"));
        // 연결 실패 이벤트 호출
        //OnServerConnectionFailed();
        return;
    }
    
    // 서버 연결 시도
    bool bConnected = NetworkManager->ConnectToServer(ServerIP, ServerPort);
    
    if (bConnected)
    {
        UE_LOG(LogTemp, Display, TEXT("Successfully connected to server %s:%d"), *ServerIP, ServerPort);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server %s:%d"), *ServerIP, ServerPort);
        
        // 자동 재연결 설정 확인
        if (bAutoReconnect)
        {
            FTimerHandle ReconnectTimerHandle;
            FTimerDelegate ReconnectDelegate;
            ReconnectDelegate.BindLambda([this]() {
                this->ConnectToServer();
            });
            
            GetWorld()->GetTimerManager().SetTimer(
                ReconnectTimerHandle,
                ReconnectDelegate,
                ReconnectInterval,
                false
            );
            
            UE_LOG(LogTemp, Display, TEXT("Scheduled reconnect in %.1f seconds"), ReconnectInterval);
        }
    }
}

void ASimpleNetworkGameMode::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
        // 연결 해제 이벤트 호출
        //OnServerDisconnected();
    }
}