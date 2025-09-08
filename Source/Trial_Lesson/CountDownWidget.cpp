// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UCountDownWidget::StartCountdown()
{
	cressent_count = 3;
	UpdateCountdown();
	GetWorld()->GetTimerManager().SetTimer(countdowntimer, this, &UCountDownWidget::UpdateCountdown, 1.0f, true);
}

void UCountDownWidget::NativeConstruct()
{
	Super::NativeConstruct();
	cressent_count = 3;
}

UCountDownWidget* UCountDownWidget::ShowCountdown(UObject* WorldContextObject)
{
	if (!WorldContextObject) 
	{
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	if (!World)
	{
		return nullptr;
	}

	UCountDownWidget* Widget = CreateWidget<UCountDownWidget>(World, UCountDownWidget::StaticClass());

	if (Widget)
	{
		Widget->AddToViewport(100);
		Widget->StartCountdown();
	}

	return Widget;
}

void UCountDownWidget::UpdateCountdown()
{
	if (!CountdownText) 
	{
		return;
	}

	if (cressent_count>0)
	{
		CountdownText->SetText(FText::AsNumber(cressent_count));
		cressent_count--;
	}
	else
	{
	/*	CountdownText->SetText(FText::FromString(TEXT("GO!"))); (
			GetWorld()->GetTimerManager().ClearTimer(countdowntimer);
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
			{
				this->RemoveFromPersent();
			});*/
	}
}