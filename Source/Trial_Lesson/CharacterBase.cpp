#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// コンストラクタ
ACharacterBase::ACharacterBase()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
    PlayerCamera->SetupAttachment(SpringArmComp);
    PrimaryActorTick.bCanEverTick = true;

    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    bUseControllerRotationYaw = true;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = false;
    }

    // 移動フラグ初期化
    bFrontMoveActionExist = false;
    bBackMoveActionExist = false;
    bLeftMoveActionExist = false;
    bRightMoveActionExist = false;
    bJumpActionExist = false;
    isHorizontalMovementActive = true;

    ItemCount = 0;
}

// アイテム取得
void ACharacterBase::PickupItem(AItemBase* Item)
{
    if (!Item) return;

    int32* Count = ItemCounts.Find(Item->GetItemName());
    if (Count)
    {
        (*Count)++;
    }
    else
    {
        ItemCounts.Add(Item->GetItemName(), 1);
    }
}

// ゲーム開始時
void ACharacterBase::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
    if (!PlayerCamera)
    {
        PlayerCamera = FindComponentByClass<UCameraComponent>( );
        if (PlayerCamera)
        {
            UE_LOG(LogTemp, Log, TEXT("Camera Find"));
        }
    }
}

// 入力設定
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
        EIC->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACharacterBase::ResetMoveBools);

        EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacterBase::StartJump);
        EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacterBase::StopJump);

        EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACharacterBase::Look);
    }
}

// 移動処理
void ACharacterBase::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller)
    {
        if (isHorizontalMovementActive) {
            AddMovementInput(GetActorForwardVector( ), MovementVector.Y);
        }
        AddMovementInput(GetActorRightVector( ), MovementVector.X);
    }

    bFrontMoveActionExist = ( MovementVector.X > 0.1f );
    bBackMoveActionExist = ( MovementVector.X < -0.1f );
    bRightMoveActionExist = (MovementVector.Y > 0.1f);
    bLeftMoveActionExist = (MovementVector.Y < -0.1f);
}

// ジャンプ開始
void ACharacterBase::StartJump()
{
    bJumpActionExist = true;
    Jump();
}

// ジャンプ終了
void ACharacterBase::StopJump()
{
    bJumpActionExist = false;
    StopJumping();
}

// 移動フラグリセット
void ACharacterBase::ResetMoveBools()
{
    bFrontMoveActionExist = false;
    bBackMoveActionExist = false;
    bLeftMoveActionExist = false;
    bRightMoveActionExist = false;
}

// 視点操作
void ACharacterBase::Look(const FInputActionValue& Value)
{
    LookAxisValue = Value.Get<FVector2D>();

    if (!LookAxisValue.IsNearlyZero())
    {
        //UE_LOG(LogTemp, Warning, TEXT("LookAxisValue: X=%f, Y=%f"), LookAxisValue.X, LookAxisValue.Y);
    }
}

// Tick処理
void ACharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Controller && !LookAxisValue.IsNearlyZero())
    {
        AddControllerYawInput(LookAxisValue.X * BaseTurnRate * DeltaTime);
        AddControllerPitchInput(LookAxisValue.Y * BaseLookUpRate * DeltaTime);
    }
}

// アイテムカウント増加（デバッグ用）
void ACharacterBase::AddItemCount()
{
    ItemCount++;

}

void ACharacterBase::SetCameraLocation(FVector NewLocation) 
{
    if (PlayerCamera)
    {
        PlayerCamera->SetWorldLocation(NewLocation);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCamera not L"));
    }
}

void ACharacterBase::SetCameraRotation(FRotator NewRotation) {
    if (PlayerCamera)
    {
        PlayerCamera->SetWorldRotation(NewRotation);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCamera not R"));
    }
}

void ACharacterBase::SetCameraDetached(bool bDetach) 
{
    if (bDetach)
    {
        PlayerCamera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        UE_LOG(LogTemp, Warning, TEXT("Camera Detach"));
    }
    else
    {
        if (SpringArmComp)
        {
            PlayerCamera->AttachToComponent(SpringArmComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            UE_LOG(LogTemp, Warning, TEXT("Camera Attach"));
        }
    }
}

void ACharacterBase::EnableMouseLook(bool bEnable) {
    if (!bEnable)
    {
        bUseControllerRotationYaw = false;
        isHorizontalMovementActive = false;
    }
    else
    {
        bUseControllerRotationYaw = true;
        isHorizontalMovementActive = true;
    }
}
