#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "dummy_clientCharacter.generated.h"

class UNetworkManager;

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

    /** 다른 플레이어 위치 수신 처리 */
    UFUNCTION()
    void OnPositionUpdateReceived(const FVector& NewPosition);

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
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void SpawnOtherPlayerCharacter(const FVector& Position);
};