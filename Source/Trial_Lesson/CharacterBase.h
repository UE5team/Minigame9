#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ItemBase.h"
#include "CharacterBase.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS(Blueprintable)
class TRIAL_LESSON_API ACharacterBase : public ACharacter {
	GENERATED_BODY( )

public:
	ACharacterBase( );

protected:
	virtual void BeginPlay( ) override;

	// �A�C�e���̏��������Ǘ�
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> ItemCounts;

	// �A�C�e�����E���֐�
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PickupItem(AItemBase* Item);

	// �ړ��ƃW�����v
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// �}�E�X��]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void StartJump( );
	void StopJump( );
	void ResetMoveBools( );

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bFrontMoveActionExist;
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bBackMoveActionExist;
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bLeftMoveActionExist;
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bRightMoveActionExist;
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bJumpActionExist;

	// �L������]�X�s�[�h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseLookUpRate;

	// --- ������ǉ� ---
private:
	FVector2D LookAxisValue; // Tick�ŉ�]�����p�̓��͒l��ێ�

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// �A�C�e�����E������
	UPROPERTY(BlueprintReadOnly, Category = "Items")
	int32 ItemCount;

	// �A�C�e�����E�����Ƃ��ɌĂ�
	void AddItemCount( );

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraLocation(FVector NewLocation);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComp;
};
