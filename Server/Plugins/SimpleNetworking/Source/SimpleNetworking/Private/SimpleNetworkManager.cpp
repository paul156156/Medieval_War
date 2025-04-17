// SimpleNetworkManager.cpp
#include "SimpleNetworkManager.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USimpleNetworkManager::USimpleNetworkManager()
    : Socket(nullptr)
    , bIsConnected(false)
    , LastErrorCode(0)
    , LocalClientId(-1)
{
    // 수신 버퍼 초기화
    FMemory::Memzero(RecvBuffer, sizeof(RecvBuffer));
}

USimpleNetworkManager::~USimpleNetworkManager()
{
    // 소멸자에서 소켓 해제
    DisconnectFromServer();
}

bool USimpleNetworkManager::ConnectToServer(const FString& IPAddress, int32 Port)
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

    // 논블로킹 모드 설정
    Socket->SetNonBlocking(true);

    // 연결 성공
    bIsConnected = true;
    UE_LOG(LogTemp, Display, TEXT("Connected to server %s:%d"), *IPAddress, Port);

    // 패킷 수신 타이머 설정
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            PacketReceiverTimerHandle,
            FTimerDelegate::CreateUObject(this, &USimpleNetworkManager::ProcessIncomingPackets),
            0.01f, // 10ms 간격으로 패킷 수신 확인
            true
        );
    }

    // 연결 상태 변경 이벤트 발생
    OnConnectionStatusChanged.Broadcast(true);

    return true;
}

void USimpleNetworkManager::DisconnectFromServer()
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
        LocalClientId = -1;  // 클라이언트 ID 초기화

        UE_LOG(LogTemp, Display, TEXT("Disconnected from server"));

        // 연결 상태 변경 이벤트 발생
        OnConnectionStatusChanged.Broadcast(false);
    }
}

void USimpleNetworkManager::SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation)
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

    // 속도 정보 추가
    FVector Velocity = FVector::ZeroVector;

    // 캐릭터에서 속도 가져오기
    ACharacter* Character = Cast<ACharacter>(GetOuter());
    if (Character)
    {
        Velocity = Character->GetVelocity();
    }

    Packet.Velocity.X = Velocity.X;
    Packet.Velocity.Y = Velocity.Y;
    Packet.Velocity.Z = Velocity.Z;

    // 패킷 전송
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FMovePacket), BytesSent);

    // 전송 실패 시 연결 상태 체크
    if (!bSuccess || BytesSent != sizeof(FMovePacket))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to send Move packet! Sent %d of %d bytes"),
               BytesSent, sizeof(FMovePacket));
        CheckConnectionStatus();
    }
    else
    {
        // 디버그 로그 (Verbose 레벨)
        UE_LOG(LogTemp, Verbose, TEXT("Sent Move Packet: Forward=%.2f, Right=%.2f, Pos=(%.2f,%.2f,%.2f), Vel=(%.2f,%.2f,%.2f)"),
               ForwardValue, RightValue, Position.X, Position.Y, Position.Z, Velocity.X, Velocity.Y, Velocity.Z);
    }
}

void USimpleNetworkManager::SendJumpPacket(bool IsJumping, const FVector& Position)
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

    // 속도 정보 추가
    FVector Velocity = FVector::ZeroVector;

    // 캐릭터에서 속도 가져오기
    ACharacter* Character = Cast<ACharacter>(GetOuter());
    if (Character)
    {
        Velocity = Character->GetVelocity();
    }

    Packet.Velocity.X = Velocity.X;
    Packet.Velocity.Y = Velocity.Y;
    Packet.Velocity.Z = Velocity.Z;

    // 패킷 전송
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FJumpPacket), BytesSent);

    // 전송 실패 시 연결 상태 체크
    if (!bSuccess || BytesSent != sizeof(FJumpPacket))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to send Jump packet! Sent %d of %d bytes"),
               BytesSent, sizeof(FJumpPacket));
        CheckConnectionStatus();
    }
    else
    {
        // 디버그 로그 (Verbose 레벨)
        UE_LOG(LogTemp, Verbose, TEXT("Sent Jump Packet: Jumping=%s, Pos=(%.2f,%.2f,%.2f), Vel=(%.2f,%.2f,%.2f)"),
               IsJumping ? TEXT("true") : TEXT("false"), Position.X, Position.Y, Position.Z, Velocity.X, Velocity.Y, Velocity.Z);
    }
}

void USimpleNetworkManager::ProcessIncomingPackets()
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
            UE_LOG(LogTemp, Warning, TEXT("Failed to receive data from server"));
            CheckConnectionStatus();
            return;
        }

        if (BytesRead >= sizeof(FPacketHeader))
        {
            // 패킷 헤더 추출
            FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(RecvBuffer);

            // 패킷 내용 디버그 로그
            UE_LOG(LogTemp, Display, TEXT("Received packet - Type: %d, Size: %d, BytesRead: %d"),
                   (int32)Header->PacketType, Header->PacketSize, BytesRead);

            // 패킷 타입에 따른 처리
            switch (Header->PacketType)
            {
            case EPacketType::POSITION_UPDATE:
                if (BytesRead >= sizeof(FPositionUpdatePacket))
                {
                    FPositionUpdatePacket* Packet = reinterpret_cast<FPositionUpdatePacket*>(RecvBuffer);
                    UE_LOG(LogTemp, Display, TEXT("Position Update Packet - Client ID: %d, Pos: (%.1f, %.1f, %.1f), Vel: (%.1f, %.1f, %.1f)"),
                           Packet->ClientId, Packet->Position.X, Packet->Position.Y, Packet->Position.Z,
                           Packet->Velocity.X, Packet->Velocity.Y, Packet->Velocity.Z);
                    HandlePositionUpdatePacket(Packet);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Incomplete position update packet received"));
                }
                break;
            case EPacketType::CLIENT_ID:
                if (BytesRead >= sizeof(FClientIdPacket))
                {
                    FClientIdPacket* Packet = reinterpret_cast<FClientIdPacket*>(RecvBuffer);
                    UE_LOG(LogTemp, Display, TEXT("Client ID Packet - Client ID: %d"), Packet->ClientId);
                    HandleClientIdPacket(Packet);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Incomplete client ID packet received"));
                }
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type received: %d"), (int32)Header->PacketType);
                break;
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received incomplete packet header, size: %d"), BytesRead);
        }
    }
}

void USimpleNetworkManager::HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet)
{
    if (!Packet)
    {
        return;
    }

    // 위치 정보 추출
    FVector NewPosition(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FRotator NewRotation(Packet->Rotation.Pitch, Packet->Rotation.Yaw, Packet->Rotation.Roll);
    FVector NewVelocity(Packet->Velocity.X, Packet->Velocity.Y, Packet->Velocity.Z);
    bool bIsJumping = Packet->IsJumping;
    int32 ClientId = Packet->ClientId;

    // 로컬 플레이어의 업데이트는 무시 (서버에서 전송해도)
    if (ClientId == LocalClientId)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Ignored position update for local player (ID: %d)"), ClientId);
        return;
    }

    // 기존 델리게이트 호출 (레거시 지원을 위해 유지)
    OnPositionUpdate.Broadcast(NewPosition);
    OnRotationUpdate.Broadcast(NewRotation);
    OnJumpStateUpdate.Broadcast(bIsJumping);

    // 통합 플레이어 업데이트 델리게이트 호출 (새로운 방식, 속도 정보 포함)
    OnPlayerUpdate.Broadcast(ClientId, NewPosition, NewRotation, NewVelocity, bIsJumping);

    // 디버그 로그
    UE_LOG(LogTemp, Verbose, TEXT("Position Update from client %d: Pos=(%.1f,%.1f,%.1f), Vel=(%.1f,%.1f,%.1f), Jumping=%s"),
           ClientId, NewPosition.X, NewPosition.Y, NewPosition.Z,
           NewVelocity.X, NewVelocity.Y, NewVelocity.Z,
           bIsJumping ? TEXT("true") : TEXT("false"));
}

void USimpleNetworkManager::HandleClientIdPacket(const FClientIdPacket* Packet)
{
    if (!Packet)
    {
        return;
    }

    // 클라이언트 ID 저장
    LocalClientId = Packet->ClientId;

    // 클라이언트 ID 수신 이벤트 발생
    OnClientIdReceived.Broadcast(LocalClientId);

    UE_LOG(LogTemp, Display, TEXT("Received client ID: %d"), LocalClientId);
}

bool USimpleNetworkManager::IsConnected() const
{
    return Socket != nullptr && bIsConnected;
}

void USimpleNetworkManager::CheckConnectionStatus()
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