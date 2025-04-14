#include "NetworkManager.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "IPAddress.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

UNetworkManager::UNetworkManager()
    : Socket(nullptr)
    , bIsConnected(false)
    , LastErrorCode(0)
{
    // 수신 버퍼 초기화
    FMemory::Memzero(RecvBuffer, sizeof(RecvBuffer));
}

UNetworkManager::~UNetworkManager()
{
    // 소멸자에서 소켓 해제
    DisconnectFromServer();
}

bool UNetworkManager::ConnectToServer(const FString& IPAddress, int32 Port)
{
    // 이미 연결되어 있으면 연결 해제
    if (Socket)
    {
        DisconnectFromServer();
    }

    // 소켓 서브시스템 가져오기
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Socket Subsystem not found"));
        LastErrorCode = 1;
        return false;
    }

    // 소켓 생성
    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Default TCP Socket"), true);
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
        LastErrorCode = 2;
        return false;
    }

    // 서버 엔드포인트 설정
    FIPv4Address ServerIP;
    FIPv4Address::Parse(IPAddress, ServerIP);
    ServerEndpoint = FIPv4Endpoint(ServerIP, Port);

    // 서버 연결
    if (!Socket->Connect(*ServerEndpoint.ToInternetAddr()))
    {
        LastErrorCode = SocketSubsystem->GetLastErrorCode();
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server %s:%d (Error: %d)"),
            *IPAddress, Port, LastErrorCode);
        SocketSubsystem->DestroySocket(Socket);
        Socket = nullptr;
        return false;
    }

    // 논블록킹 모드 설정
    Socket->SetNonBlocking(true);

    // 연결 성공
    bIsConnected = true;
    UE_LOG(LogTemp, Display, TEXT("Connected to server %s:%d"), *IPAddress, Port);

    // 패킷 수신 타이머 설정
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            PacketReceiverTimerHandle,
            FTimerDelegate::CreateUObject(this, &UNetworkManager::ProcessIncomingPackets),
            0.01f, // 10ms 간격으로 패킷 수신 확인
            true
        );
    }

    return true;
}

void UNetworkManager::DisconnectFromServer()
{
    if (Socket)
    {
        // 타이머 해제
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().ClearTimer(PacketReceiverTimerHandle);
        }

        // 소켓 닫기
        ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (SocketSubsystem)
        {
            Socket->Close();
            SocketSubsystem->DestroySocket(Socket);
            Socket = nullptr;
        }

        bIsConnected = false;
        UE_LOG(LogTemp, Display, TEXT("Disconnected from server"));
    }
}

void UNetworkManager::SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation)
{
    if (!IsConnected())
    {
        return;
    }

    // 이동 패킷 생성
    FMovePacket Packet;
    Packet.Header.PacketType = EPacketType::MOVE;
    Packet.Header.PacketSize = sizeof(FMovePacket);
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.Position.X = Position.X;
    Packet.Position.Y = Position.Y;
    Packet.Position.Z = Position.Z;
    Packet.Rotation.Pitch = Rotation.Pitch;
    Packet.Rotation.Yaw = Rotation.Yaw;
    Packet.Rotation.Roll = Rotation.Roll;

    // 패킷 전송
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FMovePacket), BytesSent);

    // 전송 실패 시 연결 상태 체크
    if (!bSuccess || BytesSent != sizeof(FMovePacket))
    {
        CheckConnectionStatus();
    }
}

void UNetworkManager::SendJumpPacket(bool IsJumping, const FVector& Position)
{
    if (!IsConnected())
    {
        return;
    }

    // 점프 패킷 생성
    FJumpPacket Packet;
    Packet.Header.PacketType = EPacketType::JUMP;
    Packet.Header.PacketSize = sizeof(FJumpPacket);
    Packet.IsJumping = IsJumping;
    Packet.Position.X = Position.X;
    Packet.Position.Y = Position.Y;
    Packet.Position.Z = Position.Z;

    // 패킷 전송
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FJumpPacket), BytesSent);

    // 전송 실패 시 연결 상태 체크
    if (!bSuccess || BytesSent != sizeof(FJumpPacket))
    {
        CheckConnectionStatus();
    }
}

void UNetworkManager::ProcessIncomingPackets()
{
    if (!IsConnected())
    {
        return;
    }

    uint32 PendingDataSize = 0;

    // 수신 대기 데이터 크기 확인
    if (Socket->HasPendingData(PendingDataSize) && PendingDataSize > 0)
    {
        // 데이터 수신
        int32 BytesRead = 0;
        bool bSuccess = Socket->Recv(RecvBuffer, FMath::Min(PendingDataSize, (uint32)sizeof(RecvBuffer)), BytesRead);

        if (!bSuccess)
        {
            CheckConnectionStatus();
            return;
        }

        if (BytesRead >= sizeof(FPacketHeader))
        {
            // 패킷 헤더 추출
            FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(RecvBuffer);

            // 패킷 타입에 따른 처리
            switch (Header->PacketType)
            {
            case EPacketType::POSITION_UPDATE:
                if (BytesRead >= sizeof(FPositionUpdatePacket))
                {
                    HandlePositionUpdatePacket(reinterpret_cast<FPositionUpdatePacket*>(RecvBuffer));
                }
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type received: %d"), (int32)Header->PacketType);
                break;
            }
        }
    }
}

void UNetworkManager::HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet)
{
    if (!Packet)
    {
        return;
    }

    // 위치 정보 추출
    FVector NewPosition(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FRotator NewRotation(Packet->Rotation.Pitch, Packet->Rotation.Yaw, Packet->Rotation.Roll);
    bool bIsJumping = Packet->IsJumping;

    // 델리게이트 호출
    OnPositionUpdate.Broadcast(NewPosition);
    OnRotationUpdate.Broadcast(NewRotation);
    OnJumpStateUpdate.Broadcast(bIsJumping);

    // 디버그 로그
    UE_LOG(LogTemp, Verbose, TEXT("Position Update: X=%.2f Y=%.2f Z=%.2f, Jumping=%s"),
        Packet->Position.X, Packet->Position.Y, Packet->Position.Z,
        Packet->IsJumping ? TEXT("true") : TEXT("false"));
}

bool UNetworkManager::IsConnected() const
{
    return Socket != nullptr && bIsConnected;
}

void UNetworkManager::CheckConnectionStatus()
{
    if (!Socket)
    {
        bIsConnected = false;
        return;
    }

    // 소켓 연결 상태 확인
    bool bConnectionLost = false;

    // 간단한 연결 테스트 (0바이트 전송)
    int32 BytesSent = 0;
    if (!Socket->Send(nullptr, 0, BytesSent))
    {
        ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (SocketSubsystem)
        {
            LastErrorCode = SocketSubsystem->GetLastErrorCode();
            if (LastErrorCode != 0)
            {
                bConnectionLost = true;
            }
        }
    }

    if (bConnectionLost)
    {
        UE_LOG(LogTemp, Warning, TEXT("Connection to server lost (Error: %d)"), LastErrorCode);
        bIsConnected = false;
        OnConnectionStatusChanged.Broadcast(false);

        // 연결 해제 처리
        DisconnectFromServer();
    }
}