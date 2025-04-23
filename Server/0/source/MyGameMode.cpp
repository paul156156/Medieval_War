#include "MyGameMode.h"
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyGameMode::AMyGameMode()
{
    // 기본 폰 클래스를 우리의 캐릭터 클래스로 설정
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_MyCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    else
    {
        DefaultPawnClass = AMyCharacter::StaticClass();
    }
}