// MultiplayerPlayerController.cpp
// 플레이어 컨트롤러 클래스 구현

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

    // 게임 모드 참조 가져오기
    GameMode = Cast<AMultiplayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AMultiplayerPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMultiplayerPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // ESC 키 입력 처리 바인딩
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
        // 연결 UI 위젯 생성
        ConnectionWidget = CreateWidget<UUserWidget>(this, ConnectionWidgetClass);
    }

    if (ConnectionWidget)
    {
        // 위젯 표시
        ConnectionWidget->AddToViewport();

        // 입력 모드 설정
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(ConnectionWidget->GetCachedWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);

        // 마우스 커서 표시
        bShowMouseCursor = true;
    }
}

void AMultiplayerPlayerController::OnConnectButtonClicked(const FString& IpAddress, int32 Port)
{
    if (GameMode)
    {
        // 서버 연결 시도
        bool bConnected = GameMode->ConnectToServer(IpAddress, Port);

        if (bConnected)
        {
            // 게임으로 돌아가기
            FInputModeGameOnly InputMode;
            SetInputMode(InputMode);
            bShowMouseCursor = false;

            // 위젯 숨기기
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
        // 서버 연결 종료
        GameMode->DisconnectFromServer();
    }

    // 게임으로 돌아가기
    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
    bShowMouseCursor = false;

    // 위젯 숨기기
    if (ConnectionWidget && ConnectionWidget->IsInViewport())
    {
        ConnectionWidget->RemoveFromParent();
    }
}

void AMultiplayerPlayerController::OnEscapePressed()
{
    // UI 표시 상태에 따라 토글
    if (ConnectionWidget && ConnectionWidget->IsInViewport())
    {
        // UI 닫기
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
        bShowMouseCursor = false;
        ConnectionWidget->RemoveFromParent();
    }
    else
    {
        // UI 열기
        ShowConnectionUI();
    }
}