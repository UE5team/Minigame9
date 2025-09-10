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

	// アイテムの所持数を管理
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> ItemCounts;

	// アイテムを拾う関数
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PickupItem(AItemBase* Item);

	// 移動とジャンプ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// マウス回転
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

	// キャラ回転スピード
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseLookUpRate;

	// --- ここを追加 ---
private:
	FVector2D LookAxisValue; // Tickで回転処理用の入力値を保持

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// アイテムを拾った数
	UPROPERTY(BlueprintReadOnly, Category = "Items")
	int32 ItemCount;

	// アイテムを拾ったときに呼ぶ
	void AddItemCount( );

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraLocation(FVector NewLocation);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComp;
};
