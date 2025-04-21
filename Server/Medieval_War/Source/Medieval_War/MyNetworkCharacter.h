// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "MyNetworkCharacter.generated.h"

/**
 * ��Ʈ��ŷ ����� �߰��� ĳ���� Ŭ����
 */
UCLASS()
class MEDIEVAL_WAR_API AMyNetworkCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:
	// ������
	AMyNetworkCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ��Ʈ��ũ ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Networking")
	class UNetworkPlayerComponent* NetworkComponent;

	// ������ ����
	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool ConnectToServer();

	// ���� ���� ����
	UFUNCTION(BlueprintCallable, Category = "Networking")
	void DisconnectFromServer();

	// �ٸ� �÷��̾� ĳ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Networking")
	TSubclassOf<AActor> OtherPlayerCharacterClass;

protected:
	// ��Ʈ��ũ �̺�Ʈ �ڵ鷯 - UFUNCTION ��ũ�� �ʿ�!
	UFUNCTION()
	void OnConnectionStatusChanged(bool IsConnected);

	UFUNCTION()
	void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping);

	UFUNCTION()
	void OnClientIdReceived(int32 ClientId);

	// ���� ó�� �Լ�
	void OnNetworkConnected();
	void OnNetworkDisconnected();
};