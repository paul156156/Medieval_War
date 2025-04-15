#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "dummy_clientCharacter.generated.h"

class UNetworkManager;

// 다른 플레이어 캐릭터 정보 구조체
USTRUCT()
struct FOtherPlayerInfo
{
    GENERATED_BODY()

    int32 ClientId;  // 클라이언트 ID 추가
    FVector TargetPosition;
    FRotator TargetRotation;
    float PositionInterpolationTime;
    float RotationInterpolationTime;
    bool IsJumping;

    FOtherPlayerInfo()
        : ClientId(-1)  // 초기값 -1로 설정
        , TargetPosition(FVector::ZeroVector)
        , TargetRotation(FRotator::ZeroRotator)
        , PositionInterpolationTime(0.0f)
        , RotationInterpolationTime(0.0f)
        , IsJumping(false)
    {
    }
};

UCLASS(config = Game)
class Adummy_clientCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    Adummy_clientCharacter();

protected:
    /** 카메라 붐 컴포넌트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    /** 팔로우 카메라 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    /** 네트워크 매니저 레퍼런스 */
    UPROPERTY()
    UNetworkManager* NetworkManager;

    /** 네트워크 업데이트 활성화 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    bool bEnableNetworkUpdates;

    /** 마지막 위치 전송 시간 */
    float LastPositionSentTime;

    /** 위치 전송 간격 (초) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    float PositionUpdateInterval;

    /** 로컬 플레이어 클라이언트 ID */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Networking)
    int32 LocalClientId;

    /** 다른 플레이어 캐릭터 클래스 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Networking)
    TSubclassOf<AActor> OtherPlayerCharacterClass;

    /** 다른 플레이어 캐릭터 맵 */
    UPROPERTY()
    TMap<AActor*, FOtherPlayerInfo> OtherPlayers;

    /** 클라이언트 ID 수신 */
    UFUNCTION()
    void OnClientIdReceived(int32 ClientId);

    /** 플레이어 업데이트 수신 (통합 함수) */
    UFUNCTION()
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& NewPosition, const FRotator& NewRotation, bool IsJumping);

    /** 다른 플레이어 위치 업데이트 수신 (레거시) */
    UFUNCTION()
    void OnPositionUpdateReceived(const FVector& NewPosition);

    /** 다른 플레이어 회전 업데이트 수신 (레거시) */
    UFUNCTION()
    void OnRotationUpdateReceived(const FRotator& NewRotation);

    /** 다른 플레이어 점프 상태 업데이트 수신 (레거시) */
    UFUNCTION()
    void OnJumpStateUpdateReceived(bool IsJumping);

    /** 네트워크 연결 상태 변경 */
    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);

    /** 다른 플레이어 캐릭터 업데이트 */
    void UpdateOtherPlayerCharacters(float DeltaTime);

    /** 다른 플레이어 캐릭터 스폰 내부 구현 */
    AActor* SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId = -1);

    /** 다른 플레이어 캐릭터 제거 */
    UFUNCTION()
    void RemoveOtherPlayerCharacter(int32 ClientId);

    /** 네트워크 연결됨 이벤트 */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnNetworkConnected();

    /** 네트워크 연결 해제됨 이벤트 */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnNetworkDisconnected();

    /** 다른 플레이어 스폰됨 이벤트 */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId);

    /** 다른 플레이어 제거됨 이벤트 */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnOtherPlayerRemoved(int32 ClientId);

    ///// 기본 입력 관련 함수 /////
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
    /** 베이스턴레이트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** 베이스룩업/다운레이트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

    /** 현재 클라이언트 ID 반환 */
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLocalClientId() const { return LocalClientId; }

    /** 다른 플레이어 캐릭터 개수 반환 */
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetOtherPlayerCount() const { return OtherPlayers.Num(); }

protected:
    // 캐릭터 초기화
    virtual void BeginPlay() override;

    // 매 프레임 호출
    virtual void Tick(float DeltaTime) override;

    // 네트워크 매니저 초기화
    void InitializeNetworkManager();

    // 서버에 위치 전송
    void SendPositionToServer();

public:
    // 점프 이벤트 (오버라이드)
    virtual void Jump() override;
    virtual void StopJumping() override;

    // 다른 플레이어 캐릭터 스폰 (서버로부터 받은 위치 정보로)
    UFUNCTION(BlueprintCallable, Category = "Networking")
    AActor* SpawnOtherPlayerCharacter(const FVector& Position, int32 InClientId = -1)
    {
        return SpawnOtherPlayerCharacterInternal(Position, InClientId);
    }

    // 모든 다른 플레이어 캐릭터 제거
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void RemoveAllOtherPlayers();
};