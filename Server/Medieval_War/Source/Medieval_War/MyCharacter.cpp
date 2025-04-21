#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyCharacter::AMyCharacter()
{
    // ĳ���Ͱ� �� ������ Tick�� �޵��� ����
    PrimaryActorTick.bCanEverTick = true;

    // ĸ�� ������Ʈ ����
    GetCapsuleComponent()->InitCapsuleSize(34.f, 88.0f);

    // ĳ���� �����Ʈ ������Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    // ��Ʈ�ѷ��� ĳ������ ��(Yaw) ȸ������ ������ �ֵ��� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ������ �� ���� (ĳ���Ϳ� ī�޶� ������ �Ÿ� ����)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // �ȷο� ī�޶� ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // �÷��̾� ��Ʈ�ѷ� ��������
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        // ���� �÷��̾��� Enhanced Input ����ý��� ��������
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // ���� ���ؽ�Ʈ �߰�
            Subsystem->RemoveMappingContext(DefaultMappingContext);
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced Input ������Ʈ�� ĳ����
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // �̵� ���ε�
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

        // �ü� ���ε�
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		// ���� ���ε�
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // ���� ���ε�
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    // �Է� �� �������� (2D ����)
    FVector2D MovementVector = Value.Get<FVector2D>();

    // ����� �α� ���
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green,
            FString::Printf(TEXT("Move Input - X: %.2f, Y: %.2f"), MovementVector.X, MovementVector.Y));
    }

    if (Controller != nullptr)
    {
        // ī�޶� ���� ���� ���
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // ���� ���� (Y��)
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // ���� ���� (X��)
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // ������ ����
        if (MovementVector.Y != 0.0f)  // ���� �̵� (W/S)
        {
            AddMovementInput(ForwardDirection, MovementVector.Y);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow,
                    FString::Printf(TEXT("Forward Input Applied: %.2f"), MovementVector.Y));
            }
        }

        if (MovementVector.X != 0.0f)  // �¿� �̵� (A/D)
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
    // �Է� �� �������� (2D ����)
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // ��(yaw) ȸ�� �߰�
        AddControllerYawInput(LookAxisVector.X);

        // ��ġ(pitch) ȸ�� �߰�
        AddControllerPitchInput(LookAxisVector.Y);
    }

    // ����� �α� ���
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
        FString::Printf(TEXT("Look Input - X: %.2f, Y: %.2f"), LookAxisVector.X, LookAxisVector.Y));
    }
}

void AMyCharacter::Jump()
{
    // ���� �Լ� ȣ��
    Super::Jump();

    // ����� �α� ���
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Jump Button Pressed"));
    }
}

void AMyCharacter::StopJumping()
{
	// ���� ���� �Լ� ȣ��
	Super::StopJumping();
}

void AMyCharacter::Attack()
{
    if (bIsAttacking)
        return; // �̹� ���� ���̸� ����

    // ����� �α� ���
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack Button Pressed"));
    }

    bIsAttacking = true;

    // �ִϸ��̼� ���
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            // ��Ÿ�� ��� - 0�� ���� ���
            float MontageLength = AnimInstance->Montage_Play(AttackMontage, 1.0f);

            // ��Ÿ�� ����� ������ bIsAttacking�� false�� ����
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    bIsAttacking = false;
                }, MontageLength, false);

            // ��Ÿ�ֿ� �̺�Ʈ�� ������ ��� �Ʒ��� ���� ���ε��� �� ����
            // AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
        }
    }
    else
    {
        // ��Ÿ�ְ� ������ ������ ���� ����
        bIsAttacking = false;
    }

    // ���⿡ ���� ���� ���� �߰� (Ʈ���̽�, ������ ���� ��)
    // ��: LineTrace, SphereTrace ���� ����Ͽ� ���� ����
    // �Ǵ� �������Ʈ���� �����ϱ� ���� BlueprintImplementableEvent ���
}