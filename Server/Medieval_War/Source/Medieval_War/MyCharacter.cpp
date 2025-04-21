#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyCharacter::AMyCharacter()
{
    // 캐릭터가 매 프레임 Tick을 받도록 설정
    PrimaryActorTick.bCanEverTick = true;

    // 캡슐 컴포넌트 설정
    GetCapsuleComponent()->InitCapsuleSize(34.f, 88.0f);

    // 캐릭터 무브먼트 컴포넌트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    // 컨트롤러가 캐릭터의 요(Yaw) 회전에만 영향을 주도록 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 스프링 암 생성 (캐릭터와 카메라 사이의 거리 조절)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // 팔로우 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 플레이어 컨트롤러 가져오기
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        // 로컬 플레이어의 Enhanced Input 서브시스템 가져오기
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // 맵핑 컨텍스트 추가
            Subsystem->RemoveMappingContext(DefaultMappingContext);
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced Input 컴포넌트로 캐스팅
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 이동 바인딩
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

        // 시선 바인딩
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		// 점프 바인딩
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // 공격 바인딩
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    // 입력 값 가져오기 (2D 벡터)
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 디버그 로그 출력
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green,
            FString::Printf(TEXT("Move Input - X: %.2f, Y: %.2f"), MovementVector.X, MovementVector.Y));
    }

    if (Controller != nullptr)
    {
        // 카메라 기준 방향 계산
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 전방 벡터 (Y축)
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // 우측 벡터 (X축)
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // 움직임 적용
        if (MovementVector.Y != 0.0f)  // 전후 이동 (W/S)
        {
            AddMovementInput(ForwardDirection, MovementVector.Y);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow,
                    FString::Printf(TEXT("Forward Input Applied: %.2f"), MovementVector.Y));
            }
        }

        if (MovementVector.X != 0.0f)  // 좌우 이동 (A/D)
        {
            AddMovementInput(RightDirection, MovementVector.X);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow,
                    FString::Printf(TEXT("Right Input Applied: %.2f"), MovementVector.X));
            }
        }
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    // 입력 값 가져오기 (2D 벡터)
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // 요(yaw) 회전 추가
        AddControllerYawInput(LookAxisVector.X);

        // 피치(pitch) 회전 추가
        AddControllerPitchInput(LookAxisVector.Y);
    }

    // 디버그 로그 출력
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
        FString::Printf(TEXT("Look Input - X: %.2f, Y: %.2f"), LookAxisVector.X, LookAxisVector.Y));
    }
}

void AMyCharacter::Jump()
{
    // 점프 함수 호출
    Super::Jump();

    // 디버그 로그 출력
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Jump Button Pressed"));
    }
}

void AMyCharacter::StopJumping()
{
	// 점프 중지 함수 호출
	Super::StopJumping();
}

void AMyCharacter::Attack()
{
    if (bIsAttacking)
        return; // 이미 공격 중이면 무시

    // 디버그 로그 출력
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack Button Pressed"));
    }

    bIsAttacking = true;

    // 애니메이션 재생
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            // 몽타주 재생 - 0번 섹션 사용
            float MontageLength = AnimInstance->Montage_Play(AttackMontage, 1.0f);

            // 몽타주 재생이 끝나면 bIsAttacking을 false로 설정
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    bIsAttacking = false;
                }, MontageLength, false);

            // 몽타주에 이벤트를 설정한 경우 아래와 같이 바인딩할 수 있음
            // AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
        }
    }
    else
    {
        // 몽타주가 없으면 빠르게 상태 리셋
        bIsAttacking = false;
    }

    // 여기에 실제 공격 로직 추가 (트레이스, 데미지 적용 등)
    // 예: LineTrace, SphereTrace 등을 사용하여 공격 판정
    // 또는 블루프린트에서 구현하기 위해 BlueprintImplementableEvent 사용
}