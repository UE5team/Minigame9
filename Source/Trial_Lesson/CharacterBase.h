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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay( ) override;

protected:
	bool CanSlide( ) const;

public:
	ACharacterBase( );
	void AddItemCount( );

protected:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void StartJump( );
	void StopJump( );
	void ResetMoveBools( );
	void StartSlide( );
	void StopSlide( );

public:
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraLocation(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraDetached(bool bDetach);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void EnableMouseLook(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Status")
	void SetHp(int hp);

protected:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PickupItem(AItemBase* Item);


private:
	FVector2D LookAxisValue;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> ItemCounts;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> SlideAction;


public:
	UPROPERTY(BlueprintReadOnly, Category = "Items")
	int32 ItemCount;



private:
	bool isHorizontalMovementActive;

	bool isDead;

	UPROPERTY(EditDefaultsOnly, Category = "Sliding")
	float SlideDuration = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Sliding")
	float SlidingGroundFriction = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Sliding")
	float SlideImpulseForce = 1500.0f;

	FTimerHandle SlideTimerHandle;

	float DefaultGroundFriction;

	float DefaultCapsuleHalfHeight;

	int now_hp;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Sliding")
	bool bIsSliding;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseLookUpRate;
};
