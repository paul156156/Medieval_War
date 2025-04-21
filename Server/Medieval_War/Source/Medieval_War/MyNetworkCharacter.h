// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "MyNetworkCharacter.generated.h"

/**
 * 네트워킹 기능이 추가된 캐릭터 클래스
 */
UCLASS()
class MEDIEVAL_WAR_API AMyNetworkCharacter : public AMyCharacter
{
	GENERATED_BODY()

public:
	// 생성자
	AMyNetworkCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 네트워크 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Networking")
	class UNetworkPlayerComponent* NetworkComponent;

	// 서버에 연결
	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool ConnectToServer();

	// 서버 연결 해제
	UFUNCTION(BlueprintCallable, Category = "Networking")
	void DisconnectFromServer();

	// 다른 플레이어 캐릭터 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Networking")
	TSubclassOf<AActor> OtherPlayerCharacterClass;

protected:
	// 네트워크 이벤트 핸들러 - UFUNCTION 매크로 필요!
	UFUNCTION()
	void OnConnectionStatusChanged(bool IsConnected);

	UFUNCTION()
	void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping);

	UFUNCTION()
	void OnClientIdReceived(int32 ClientId);

	// 로직 처리 함수
	void OnNetworkConnected();
	void OnNetworkDisconnected();
};