// MultiplayerHUD.cpp
// 게임 HUD 클래스 구현

#include "MultiplayerHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerHUD::AMultiplayerHUD()
{
    // 기본 설정
    bShowConnectionStatus = true;
    bShowFPS = true;
    bShowPlayerCount = true;

    // 상태 초기화
    bIsConnected = false;
    PlayerCount = 0;
    FPS = 0.0f;

    // 메시지 초기화
    CurrentMessage = FString();
    MessageRemainingTime = 0.0f;
    bShowMessage = false;

    // FPS 계산 초기화
    LastFPSUpdateTime = 0.0f;
    FrameCount = 0;
}

void AMultiplayerHUD::BeginPlay()
{
    Super::BeginPlay();
}

void AMultiplayerHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // FPS 계산
    FrameCount++;
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastFPSUpdateTime > 1.0f)
    {
        FPS = FrameCount / (CurrentTime - LastFPSUpdateTime);
        LastFPSUpdateTime = CurrentTime;
        FrameCount = 0;
    }

    // 메시지 타이머 업데이트
    if (bShowMessage)
    {
        MessageRemainingTime -= DeltaSeconds;
        if (MessageRemainingTime <= 0.0f)
        {
            bShowMessage = false;
        }
    }
}

void AMultiplayerHUD::DrawHUD()
{
    Super::DrawHUD();

    // 캔버스 크기 가져오기
    FVector2D CanvasSize;
    CanvasSize.X = Canvas->ClipX;
    CanvasSize.Y = Canvas->ClipY;

    // 텍스트 색상 및 크기 설정
    const FLinearColor TextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    const float FontScale = 1.0f;

    // 연결 상태 표시
    if (bShowConnectionStatus)
    {
        FString StatusText = bIsConnected ? TEXT("Connected to server") : TEXT("Disconnected from server");
        FLinearColor StatusColor = bIsConnected ? FLinearColor(0.0f, 1.0f, 0.0f, 1.0f) : FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);

        DrawText(StatusText, StatusColor, 10.0f, 10.0f, GEngine->GetSmallFont(), FontScale);
    }

    // FPS 표시
    if (bShowFPS)
    {
        FString FPSText = FString::Printf(TEXT("FPS: %.1f"), FPS);
        DrawText(FPSText, TextColor, 10.0f, 30.0f, GEngine->GetSmallFont(), FontScale);
    }

    // 플레이어 수 표시
    if (bShowPlayerCount)
    {
        FString PlayerCountText = FString::Printf(TEXT("Players: %d"), PlayerCount);
        DrawText(PlayerCountText, TextColor, 10.0f, 50.0f, GEngine->GetSmallFont(), FontScale);
    }

    // 메시지 표시
    if (bShowMessage)
    {
        // 화면 중앙에 메시지 표시
        float TextWidth, TextHeight;
        GetTextSize(CurrentMessage, TextWidth, TextHeight, GEngine->GetMediumFont(), 1.2f);

        const float X = (CanvasSize.X - TextWidth) * 0.5f;
        const float Y = CanvasSize.Y * 0.7f;

        DrawText(CurrentMessage, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), X, Y, GEngine->GetMediumFont(), 1.2f);
    }
}

void AMultiplayerHUD::SetConnectionStatus(bool bNewIsConnected)
{
    if (bIsConnected != bNewIsConnected)
    {
        bIsConnected = bNewIsConnected;

        // 연결 상태 변경 시 메시지 표시
        if (bIsConnected)
        {
            ShowMessage(TEXT("Connected to server."));
        }
        else
        {
            ShowMessage(TEXT("Disconnected from server."));
        }
    }
}

void AMultiplayerHUD::UpdatePlayerCount(int32 Count)
{
    PlayerCount = Count;
}

void AMultiplayerHUD::ShowMessage(const FString& Message, float Duration)
{
    CurrentMessage = Message;
    MessageRemainingTime = Duration;
    bShowMessage = true;
}