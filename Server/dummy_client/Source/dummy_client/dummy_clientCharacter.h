#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "dummy_clientCharacter.generated.h"

class UNetworkManager;

// �ٸ� �÷��̾� ĳ���� ���� ����ü
USTRUCT()
struct FOtherPlayerInfo
{
    GENERATED_BODY()

    int32 ClientId;  // Ŭ���̾�Ʈ ID �߰�
    FVector TargetPosition;
    FRotator TargetRotation;
    float PositionInterpolationTime;
    float RotationInterpolationTime;
    bool IsJumping;

    FOtherPlayerInfo()
        : ClientId(-1)  // �ʱⰪ -1�� ����
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
    /** ī�޶� �� ������Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    /** �ȷο� ī�޶� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    /** ��Ʈ��ũ �Ŵ��� ���۷��� */
    UPROPERTY()
    UNetworkManager* NetworkManager;

    /** ��Ʈ��ũ ������Ʈ Ȱ��ȭ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    bool bEnableNetworkUpdates;

    /** ������ ��ġ ���� �ð� */
    float LastPositionSentTime;

    /** ��ġ ���� ���� (��) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    float PositionUpdateInterval;

    /** ���� �÷��̾� Ŭ���̾�Ʈ ID */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Networking)
    int32 LocalClientId;

    /** �ٸ� �÷��̾� ĳ���� Ŭ���� */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Networking)
    TSubclassOf<AActor> OtherPlayerCharacterClass;

    /** �ٸ� �÷��̾� ĳ���� �� */
    UPROPERTY()
    TMap<AActor*, FOtherPlayerInfo> OtherPlayers;

    /** Ŭ���̾�Ʈ ID ���� */
    UFUNCTION()
    void OnClientIdReceived(int32 ClientId);

    /** �÷��̾� ������Ʈ ���� (���� �Լ�) */
    UFUNCTION()
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& NewPosition, const FRotator& NewRotation, bool IsJumping);

    /** �ٸ� �÷��̾� ��ġ ������Ʈ ���� (���Ž�) */
    UFUNCTION()
    void OnPositionUpdateReceived(const FVector& NewPosition);

    /** �ٸ� �÷��̾� ȸ�� ������Ʈ ���� (���Ž�) */
    UFUNCTION()
    void OnRotationUpdateReceived(const FRotator& NewRotation);

    /** �ٸ� �÷��̾� ���� ���� ������Ʈ ���� (���Ž�) */
    UFUNCTION()
    void OnJumpStateUpdateReceived(bool IsJumping);

    /** ��Ʈ��ũ ���� ���� ���� */
    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);

    /** �ٸ� �÷��̾� ĳ���� ������Ʈ */
    void UpdateOtherPlayerCharacters(float DeltaTime);

    /** �ٸ� �÷��̾� ĳ���� ���� ���� ���� */
    AActor* SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId = -1);

    /** �ٸ� �÷��̾� ĳ���� ���� */
    UFUNCTION()
    void RemoveOtherPlayerCharacter(int32 ClientId);

    /** ��Ʈ��ũ ����� �̺�Ʈ */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnNetworkConnected();

    /** ��Ʈ��ũ ���� ������ �̺�Ʈ */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnNetworkDisconnected();

    /** �ٸ� �÷��̾� ������ �̺�Ʈ */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId);

    /** �ٸ� �÷��̾� ���ŵ� �̺�Ʈ */
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnOtherPlayerRemoved(int32 ClientId);

    ///// �⺻ �Է� ���� �Լ� /////
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
    /** ���̽��Ϸ���Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** ���̽����/�ٿ��Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

    /** ���� Ŭ���̾�Ʈ ID ��ȯ */
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLocalClientId() const { return LocalClientId; }

    /** �ٸ� �÷��̾� ĳ���� ���� ��ȯ */
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetOtherPlayerCount() const { return OtherPlayers.Num(); }

protected:
    // ĳ���� �ʱ�ȭ
    virtual void BeginPlay() override;

    // �� ������ ȣ��
    virtual void Tick(float DeltaTime) override;

    // ��Ʈ��ũ �Ŵ��� �ʱ�ȭ
    void InitializeNetworkManager();

    // ������ ��ġ ����
    void SendPositionToServer();

public:
    // ���� �̺�Ʈ (�������̵�)
    virtual void Jump() override;
    virtual void StopJumping() override;

    // �ٸ� �÷��̾� ĳ���� ���� (�����κ��� ���� ��ġ ������)
    UFUNCTION(BlueprintCallable, Category = "Networking")
    AActor* SpawnOtherPlayerCharacter(const FVector& Position, int32 InClientId = -1)
    {
        return SpawnOtherPlayerCharacterInternal(Position, InClientId);
    }

    // ��� �ٸ� �÷��̾� ĳ���� ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void RemoveAllOtherPlayers();
};