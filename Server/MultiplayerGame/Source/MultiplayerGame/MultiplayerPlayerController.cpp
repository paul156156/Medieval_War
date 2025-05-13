// MultiplayerPlayerController.cpp
// �÷��̾� ��Ʈ�ѷ� Ŭ���� ����

#include "MultiplayerPlayerController.h"
#include "MultiplayerGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerPlayerController::AMultiplayerPlayerController()
{
    bShowMouseCursor = false;
    DefaultMouseCursor = EMouseCursor::Default;
}

void AMultiplayerPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // ���� ��� ���� ��������
    GameMode = Cast<AMultiplayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AMultiplayerPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMultiplayerPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // ESC Ű �Է� ó�� ���ε�
    InputComponent->BindAction("Escape", IE_Pressed, this, &AMultiplayerPlayerController::OnEscapePressed);
}

void AMultiplayerPlayerController::ShowConnectionUI()
{
    if (!ConnectionWidgetClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ConnectionWidgetClass not set."));
        return;
    }

    if (!ConnectionWidget)
    {
        // ���� UI ���� ����
        ConnectionWidget = CreateWidget<UUserWidget>(this, ConnectionWidgetClass);
    }

    if (ConnectionWidget)
    {
        // ���� ǥ��
        ConnectionWidget->AddToViewport();

        // �Է� ��� ����
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(ConnectionWidget->GetCachedWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);

        // ���콺 Ŀ�� ǥ��
        bShowMouseCursor = true;
    }
}

void AMultiplayerPlayerController::OnConnectButtonClicked(const FString& IpAddress, int32 Port)
{
    if (GameMode)
    {
        // ���� ���� �õ�
        bool bConnected = GameMode->ConnectToServer(IpAddress, Port);

        if (bConnected)
        {
            // �������� ���ư���
            FInputModeGameOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = false;

            // ���� �����
            if (ConnectionWidget && ConnectionWidget->IsInViewport())
            {
                ConnectionWidget->RemoveFromParent();
            }
        }
    }
}

void AMultiplayerPlayerController::OnDisconnectButtonClicked()
{
    if (GameMode)
    {
        // ���� ���� ����
        GameMode->DisconnectFromServer();
    }

    // �������� ���ư���
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    bShowMouseCursor = false;

    // ���� �����
    if (ConnectionWidget && ConnectionWidget->IsInViewport())
    {
        ConnectionWidget->RemoveFromParent();
    }
}

void AMultiplayerPlayerController::OnEscapePressed()
{
    // UI ǥ�� ���¿� ���� ���
    if (ConnectionWidget && ConnectionWidget->IsInViewport())
    {
        // UI �ݱ�
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
        bShowMouseCursor = false;
        ConnectionWidget->RemoveFromParent();
    }
    else
    {
        // UI ����
        ShowConnectionUI();
    }
}