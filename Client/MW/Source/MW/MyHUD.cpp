// MyHUD.cpp

#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "NetworkManager.h"

AMyHUD::AMyHUD()
{
    bShowConnectionStatus = true;
    bShowFPS = true;
    bShowPlayerCount = true;

    bIsConnected = false;
    PlayerCount = 0;
    FPS = 0.0f;

    CurrentMessage = FString();
    MessageRemainingTime = 0.0f;
    bShowMessage = false;

    LastFPSUpdateTime = 0.0f;
    FrameCount = 0;
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        if (UNetworkManager* NetworkManager = World->GetGameInstance()->GetSubsystem<UNetworkManager>())
        {
            NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyHUD::OnConnectionStatusChanged);
            NetworkManager->OnPlayerJoined.AddDynamic(this, &AMyHUD::OnPlayerCountChanged);
            NetworkManager->OnPlayerLeft.AddDynamic(this, &AMyHUD::OnPlayerCountChanged);
        }
    }
}

void AMyHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FrameCount++;
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastFPSUpdateTime > 1.0f)
    {
        FPS = FrameCount / (CurrentTime - LastFPSUpdateTime);
        LastFPSUpdateTime = CurrentTime;
        FrameCount = 0;
    }

    if (bShowMessage)
    {
        MessageRemainingTime -= DeltaSeconds;
        if (MessageRemainingTime <= 0.0f)
        {
            bShowMessage = false;
        }
    }
}

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    FVector2D CanvasSize(Canvas->ClipX, Canvas->ClipY);
    const FLinearColor TextColor = FLinearColor::White;
    const float FontScale = 1.0f;

    if (bShowConnectionStatus)
    {
        FString StatusText = bIsConnected ? TEXT("Connected to server") : TEXT("Disconnected from server");
        FLinearColor StatusColor = bIsConnected ? FLinearColor::Green : FLinearColor::Red;
        DrawText(StatusText, StatusColor, 10.0f, 10.0f, GEngine->GetSmallFont(), FontScale);
    }

    if (bShowFPS)
    {
        DrawText(FString::Printf(TEXT("FPS: %.1f"), FPS), TextColor, 10.0f, 30.0f, GEngine->GetSmallFont(), FontScale);
    }

    if (bShowPlayerCount)
    {
        DrawText(FString::Printf(TEXT("Players: %d"), PlayerCount), TextColor, 10.0f, 50.0f, GEngine->GetSmallFont(), FontScale);
    }

    if (bShowMessage)
    {
        float TextWidth, TextHeight;
        GetTextSize(CurrentMessage, TextWidth, TextHeight, GEngine->GetMediumFont(), 1.2f);
        DrawText(CurrentMessage, TextColor, (CanvasSize.X - TextWidth) * 0.5f, CanvasSize.Y * 0.7f, GEngine->GetMediumFont(), 1.2f);
    }
}

void AMyHUD::SetConnectionStatus(bool bNewIsConnected)
{
    if (bIsConnected != bNewIsConnected)
    {
        bIsConnected = bNewIsConnected;
        ShowMessage(bIsConnected ? TEXT("Connected to server.") : TEXT("Disconnected from server."));
    }
}

void AMyHUD::UpdatePlayerCount(int32 Count)
{
    PlayerCount = Count;
}

void AMyHUD::ShowMessage(const FString& Message, float Duration)
{
    CurrentMessage = Message;
    MessageRemainingTime = Duration;
    bShowMessage = true;
}

void AMyHUD::UpdatePlayerCountFromManager()
{
    if (UWorld* World = GetWorld())
    {
        if (UNetworkManager* NetworkManager = World->GetGameInstance()->GetSubsystem<UNetworkManager>())
        {
            PlayerCount = NetworkManager->GetKnownPlayerCount();
        }
    }
}

void AMyHUD::OnConnectionStatusChanged(bool bConnected)
{
    SetConnectionStatus(bConnected);
}

void AMyHUD::OnPlayerCountChanged(int32 )
{
    UpdatePlayerCountFromManager();
}
