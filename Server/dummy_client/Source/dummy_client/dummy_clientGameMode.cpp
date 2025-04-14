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
    // �⺻ �� Ŭ���� ����
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

void Adummy_clientGameMode::BeginPlay()
{
    Super::BeginPlay();

    // ��Ʈ��ũ �Ŵ��� ����
    NetworkManager = NewObject<UNetworkManager>(this);

    // ���� ���� ���� UI ����
    if (ConnectionStatusWidgetClass)
    {
        ConnectionStatusWidget = CreateWidget<UUserWidget>(GetWorld(), ConnectionStatusWidgetClass);
        if (ConnectionStatusWidget)
        {
            ConnectionStatusWidget->AddToViewport();
        }
    }

    // �ڵ� ���� ������ ��� ������ ����
    if (bAutoConnect && NetworkManager)
    {
        FTimerHandle ConnectTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ConnectTimerHandle, this, &Adummy_clientGameMode::ConnectToServer, 1.0f, false);
    }
}

void Adummy_clientGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // ���� ���� ����
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
    }

    // UI ����
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
        // ���� ���� �õ�
        bool bConnected = NetworkManager->ConnectToServer(ServerIP, ServerPort);

        // ���� ��� �α�
        if (bConnected)
        {
            UE_LOG(LogTemp, Display, TEXT("Successfully connected to server %s:%d"), *ServerIP, ServerPort);
            OnServerConnected();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server %s:%d"), *ServerIP, ServerPort);
            OnServerConnectionFailed();

            // �翬�� �õ� ���� (�ɼ�)
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