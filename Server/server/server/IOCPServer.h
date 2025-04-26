#pragma once
#include <unordered_map>
#include <mutex>
#include "ClientSession.h"
#include "Logger.h"

class IOCPServer {
public:
    // 생성자 및 소멸자
    IOCPServer();
    ~IOCPServer();

    // 공개 메서드
    bool Initialize(int port);  // 서버 초기화
    void Run();                 // 서버 실행

private:
    // 네트워크 관련 메서드
    void AcceptNewClients(SOCKET clientSocket, SOCKADDR_IN clientAddr);  // 새 클라이언트 접속 처리
    bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context = "Unknown");  // 패킷 전송
    bool StartRecv(ClientSession* client);  // 비동기 수신 시작
    void ProcessPacket(ClientSession* client, char* data, int length);  // 패킷 처리

    // 클라이언트 관리 메서드
    void SendClientId(ClientSession* client);  // 클라이언트 ID 전송
    void BroadcastNewPlayer(ClientSession* newClient);  // 새 플레이어 정보 브로드캐스트
    void SendExistingPlayers(ClientSession* newClient);  // 기존 플레이어 정보 전송
    void RemoveClient(int clientId);  // 클라이언트 제거
    void NotifyClientDisconnect(int disconnectedClientId);  // 클라이언트 연결 끊김 알림

    // 게임 로직 메서드
    void HandleInputPacket(ClientSession* client, const InputPacket* packet);  // 입력 패킷 처리
    void Update(float DeltaTime);  // 게임 상태 업데이트
    void BroadcastPosition(ClientSession* sourceClient);  // 위치 정보 브로드캐스트

    // 스레드 관련 메서드
    void WorkerThread();  // 작업자 스레드 구현
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);  // 작업자 스레드 진입점
    void CleanUp();  // 자원 정리

    // 유틸리티 메서드
    std::string GetSocketErrorString(int error) const;
    int GetClientCount() const;

    // 멤버 변수
    SOCKET listenSocket;  // 리스닝 소켓
    HANDLE completionPort;  // IOCP 핸들
    int nextClientId;  // 다음 클라이언트 ID
    bool isRunning;  // 서버 실행 상태

    // 컨테이너 및 동기화
    std::unordered_map<int, ClientSession*> clients;  // 클라이언트 맵
    mutable std::mutex clientsMutex;  // 클라이언트 접근 뮤텍스
};