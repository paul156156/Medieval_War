// MultiplayerBaseCharacter.cpp
#include "MultiplayerBaseCharacter.h"

void AMultiplayerBaseCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    SetActorTransform(NewTransform);
    // 상태 업데이트는 서브클래스에서 구현
}