// MultiplayerBaseCharacter.cpp
#include "MultiplayerBaseCharacter.h"

void AMultiplayerBaseCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    SetActorTransform(NewTransform);
    // ���� ������Ʈ�� ����Ŭ�������� ����
}