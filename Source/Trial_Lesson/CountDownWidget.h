// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountDownWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRIAL_LESSON_API UCountDownWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Countdown")
	static UCountDownWidget* ShowCountdown(UObject* WorldCounttextObject);

public:
	UFUNCTION(BlueprintCallable, Category = "Countdown")
	void StartCountdown();

	UFUNCTION(BlueprintCallable, Category = "Countdown")
	void UpdateCountdown( );

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountdownText;

	int32 cressent_count;

	FTimerHandle countdowntimer;

	
};
