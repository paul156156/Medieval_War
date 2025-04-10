#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

// 패킷 타입 정의
enum class EPacketType : uint8_t
{
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2
};

// 벡터와 회전 구조체 정의
struct Vector3
{
    float X;
    float Y;
    float Z;
};

struct Rotator
{
    float Pitch;
    float Yaw;
    float Roll;
};

// 패킷 구조체 정의
#pragma pack(push, 1)
struct PacketHeader
{
    uint16_t PacketSize;
    EPacketType PacketType;
};

struct MovePacket
{
    PacketHeader Header;
    float ForwardValue;
    float RightValue;
    Vector3 Position;
    Rotator Rotation;
};

struct JumpPacket
{
    PacketHeader Header;
    bool IsJumping;
    Vector3 Position;
};

struct PositionUpdatePacket
{
    PacketHeader Header;
    Vector3 Position;
    Rotator Rotation;
    bool IsJumping;
};
#pragma pack(pop)

// 캐릭터 상태
struct Character
{
    Vector3 Position;
    Rotator Rotation;
    bool IsJumping;
    float ForwardValue;
    float RightValue;
};

// 더미 클라이언트 클래스
class DummyClient
{
public:
    DummyClient() : socket_(INVALID_SOCKET), isConnected_(false), isRunning_(true)
    {
        // 캐릭터 초기화
        character_.Position = { 0.0f, 0.0f, 0.0f };
        character_.Rotation = { 0.0f, 0.0f, 0.0f };
        character_.IsJumping = false;
        character_.ForwardValue = 0.0f;
        character_.RightValue = 0.0f;
    }

    ~DummyClient()
    {
        Disconnect();
    }

    bool Initialize()
    {
        // 윈속 초기화
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }

        // 소켓 생성
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket_ == INVALID_SOCKET)
        {
            std::cerr << "Socket creation failed" << std::endl;
            WSACleanup();
            return false;
        }

        return true;
    }

    bool Connect(const char* ip, int port)
    {
        // 서버 주소 설정
        SOCKADDR_IN serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip, &serverAddr.sin_addr);

        // 서버 연결
        if (connect(socket_, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        {
            std::cerr << "Failed to connect to server: " << ip << ":" << port << std::endl;
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
            WSACleanup();
            return false;
        }

        isConnected_ = true;
        std::cout << "Connected to server: " << ip << ":" << port << std::endl;

        // 수신 스레드 시작
        receiveThread_ = std::thread(&DummyClient::ReceiveLoop, this);

        return true;
    }

    void Disconnect()
    {
        isRunning_ = false;

        if (receiveThread_.joinable())
        {
            receiveThread_.join();
        }

        if (socket_ != INVALID_SOCKET)
        {
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
        }

        WSACleanup();
        isConnected_ = false;
    }

    void MoveForward(float value)
    {
        character_.ForwardValue = value;
        SendMovePacket();
    }

    void MoveRight(float value)
    {
        character_.RightValue = value;
        SendMovePacket();
    }

    void Jump(bool isJumping)
    {
        character_.IsJumping = isJumping;
        SendJumpPacket();
    }

    void UpdatePosition(float x, float y, float z)
    {
        character_.Position.X = x;
        character_.Position.Y = y;
        character_.Position.Z = z;
    }

    void UpdateRotation(float pitch, float yaw, float roll)
    {
        character_.Rotation.Pitch = pitch;
        character_.Rotation.Yaw = yaw;
        character_.Rotation.Roll = roll;
    }

    bool IsConnected() const
    {
        return isConnected_;
    }

    void Run()
    {
        std::cout << "더미 클라이언트가 실행 중" << std::endl;

        while (isRunning_ && isConnected_)
        {
            if (_kbhit())
            {
                int key = _getch();
                ProcessInput(key);
            }

            // 가상 이동 시뮬레이션 (캐릭터 위치 업데이트)
            if (character_.ForwardValue != 0.0f || character_.RightValue != 0.0f)
            {
                character_.Position.X += character_.ForwardValue * 0.1f;
                character_.Position.Y += character_.RightValue * 0.1f;
                SendMovePacket();
            }

            // 점프 시뮬레이션
            if (character_.IsJumping)
            {
                static float jumpHeight = 0.0f;
                static float jumpVelocity = 0.5f;

                jumpHeight += jumpVelocity;
                jumpVelocity -= 0.05f;

                character_.Position.Z = jumpHeight;

                if (jumpHeight <= 0.0f)
                {
                    jumpHeight = 0.0f;
                    jumpVelocity = 0.5f;
                    character_.IsJumping = false;
                    character_.Position.Z = 0.0f;
                    SendJumpPacket();
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));  // 약 60 FPS
        }
    }

private:
    void ProcessInput(int key)
    {
        switch (key)
        {
        case 'w':
        case 'W':
            MoveForward(1.0f);
            break;
        case 's':
        case 'S':
            MoveForward(-1.0f);
            break;
        case 'a':
        case 'A':
            MoveRight(-1.0f);
            break;
        case 'd':
        case 'D':
            MoveRight(1.0f);
            break;
        case ' ':
            Jump(true);
            break;
        case 27:  // ESC key
            isRunning_ = false;
            break;
        default:
            // 키를 뗐을 때의 처리
            MoveForward(0.0f);
            MoveRight(0.0f);
            break;
        }
    }

    void SendMovePacket()
    {
        if (!isConnected_)
            return;

        MovePacket packet;
        packet.Header.PacketType = EPacketType::MOVE;
        packet.Header.PacketSize = sizeof(MovePacket);
        packet.ForwardValue = character_.ForwardValue;
        packet.RightValue = character_.RightValue;
        packet.Position = character_.Position;
        packet.Rotation = character_.Rotation;

        send(socket_, reinterpret_cast<char*>(&packet), sizeof(packet), 0);

        std::cout << "Move 패킷 전송: Forward=" << character_.ForwardValue
            << ", Right=" << character_.RightValue
            << ", Pos=(" << character_.Position.X << ", "
            << character_.Position.Y << ", "
            << character_.Position.Z << ")" << std::endl;
    }

    void SendJumpPacket()
    {
        if (!isConnected_)
            return;

        JumpPacket packet;
        packet.Header.PacketType = EPacketType::JUMP;
        packet.Header.PacketSize = sizeof(JumpPacket);
        packet.IsJumping = character_.IsJumping;
        packet.Position = character_.Position;

        send(socket_, reinterpret_cast<char*>(&packet), sizeof(packet), 0);

        std::cout << "Jump 패킷 전송: IsJumping=" << (character_.IsJumping ? "true" : "false")
            << ", Pos=(" << character_.Position.X << ", "
            << character_.Position.Y << ", "
            << character_.Position.Z << ")" << std::endl;
    }

    void ReceiveLoop()
    {
        char buffer[1024];
        while (isRunning_ && isConnected_)
        {
            int bytesReceived = recv(socket_, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0)
            {
                std::cout << "서버와 연결이 끊어졌습니다." << std::endl;
                isConnected_ = false;
                break;
            }

            ProcessPacket(buffer, bytesReceived);
        }
    }

    void ProcessPacket(char* data, int length)
    {
        if (length < sizeof(PacketHeader))
            return;

        PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

        switch (header->PacketType)
        {
        case EPacketType::POSITION_UPDATE:
        {
            if (length >= sizeof(PositionUpdatePacket))
            {
                PositionUpdatePacket* packet = reinterpret_cast<PositionUpdatePacket*>(data);

                std::cout << "위치 업데이트 수신: Pos=("
                    << packet->Position.X << ", "
                    << packet->Position.Y << ", "
                    << packet->Position.Z << "), IsJumping="
                    << (packet->IsJumping ? "true" : "false") << std::endl;
            }
            break;
        }
        default:
            break;
        }
    }

    SOCKET socket_;
    bool isConnected_;
    bool isRunning_;
    std::thread receiveThread_;
    Character character_;
};

int main(int argc, char* argv[])
{
    const char* serverIP = "127.0.0.1";
    int serverPort = 9000;

    // 명령줄 인자로 서버 IP와 포트를 받을 수 있음
    if (argc > 1)
        serverIP = argv[1];
    if (argc > 2)
        serverPort = atoi(argv[2]);

    DummyClient client;
    if (!client.Initialize())
    {
        std::cerr << "클라이언트 초기화 실패" << std::endl;
        return 1;
    }

    if (!client.Connect(serverIP, serverPort))
    {
        std::cerr << "서버 연결 실패" << std::endl;
        return 1;
    }

    client.Run();

    std::cout << "클라이언트를 종료합니다." << std::endl;
    return 0;
}