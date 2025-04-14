#include "dummy_clientGameMode.h"
#include "dummy_clientCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

Adummy_clientGameMode::Adummy_clientGameMode()
    : NetworkManager(nullptr)
    , ServerIP(TEXT("127.0.0.1"))
    , ServerPort(9000)
    , bAutoConnect(true)
    , bAutoReconnect(false)
    , ReconnectInterval(5.0f)
    , ConnectionStatusWidgetClass(nullptr)
    , ConnectionStatusWidget(nullptr)
{
    // 기본 폰 클래스 설정
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

void Adummy_clientGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 네트워크 매니저 생성
    NetworkManager = NewObject<UNetworkManager>(this);

    // 서버 연결 상태 UI 생성
    if (ConnectionStatusWidgetClass)
    {
        ConnectionStatusWidget = CreateWidget<UUserWidget>(GetWorld(), ConnectionStatusWidgetClass);
        if (ConnectionStatusWidget)
        {
            ConnectionStatusWidget->AddToViewport();
        }
    }

    // 자동 연결 설정된 경우 서버에 연결
    if (bAutoConnect && NetworkManager)
    {
        FTimerHandle ConnectTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ConnectTimerHandle, this, &Adummy_clientGameMode::ConnectToServer, 1.0f, false);
    }
}

void Adummy_clientGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // 서버 연결 해제
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
    }

    // UI 제거
    if (ConnectionStatusWidget)
    {
        ConnectionStatusWidget->RemoveFromParent();
        ConnectionStatusWidget = nullptr;
    }
}

UNetworkManager* Adummy_clientGameMode::GetNetworkManager() const
{
    return NetworkManager;
}

void Adummy_clientGameMode::ConnectToServer()
{
    if (NetworkManager)
    {
        // 서버 연결 시도
        bool bConnected = NetworkManager->ConnectToServer(ServerIP, ServerPort);

        // 연결 결과 로그
        if (bConnected)
        {
            UE_LOG(LogTemp, Display, TEXT("Successfully connected to server %s:%d"), *ServerIP, ServerPort);
            OnServerConnected();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server %s:%d"), *ServerIP, ServerPort);
            OnServerConnectionFailed();

            // 재연결 시도 설정 (옵션)
            if (bAutoReconnect)
            {
                FTimerHandle ReconnectTimerHandle;
                GetWorld()->GetTimerManager().SetTimer(ReconnectTimerHandle, this, &Adummy_clientGameMode::ConnectToServer, ReconnectInterval, false);
            }
        }
    }
}

void Adummy_clientGameMode::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
        OnServerDisconnected();
    }
}