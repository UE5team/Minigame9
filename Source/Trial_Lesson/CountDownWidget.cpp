#include "CountDownWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

void UCountDownWidget::NativeConstruct( ) {
    Super::NativeConstruct( );
    cressent_count = 3;
}

void UCountDownWidget::StartCountdown( ) {
    cressent_count = 3;
    UpdateCountdown( );

    // 1�b���Ƃ�UpdateCountdown���Ăԃ^�C�}�[
    if ( GetWorld( ) ) {
        GetWorld( )->GetTimerManager( ).SetTimer( countdowntimer, this, &UCountDownWidget::UpdateCountdown, 1.0f, true );
    }

    UE_LOG( LogTemp, Warning, TEXT( "StartCountdown called" ) );
}

void UCountDownWidget::UpdateCountdown( ) {
    if ( !CountdownText ) {
        UE_LOG( LogTemp, Warning, TEXT( "CountdownText is nullptr!" ) );
        return; // nullptr�Ȃ牽�����Ȃ�
    } else {
        UE_LOG( LogTemp, Warning, TEXT( "CountdownText is valid: %d" ), cressent_count );
    }

    if ( cressent_count > 0 ) {
        CountdownText->SetText( FText::AsNumber( cressent_count ) );
        cressent_count--;
    } else {
        CountdownText->SetText( FText::FromString( TEXT( "GO!" ) ) );
        GetWorld( )->GetTimerManager( ).ClearTimer( countdowntimer );
        GetWorld( )->GetTimerManager( ).SetTimerForNextTick( [ this ] ( ) {
            this->RemoveFromParent( );
        } );
    }
}

UCountDownWidget* UCountDownWidget::ShowCountdown( UObject* WorldContextObject, TSubclassOf<UCountDownWidget> WidgetClass ) {
    if ( !WorldContextObject || !WidgetClass ) {
        UE_LOG( LogTemp, Warning, TEXT( "ShowCountdown: Invalid WorldContextObject or WidgetClass" ) );
        return nullptr;
    }

    // ���S��World���擾�inullptr�ł������Ȃ��j
    UWorld* World = WorldContextObject->GetWorld( );
    if ( !World ) {
        UE_LOG( LogTemp, Warning, TEXT( "ShowCountdown: World is nullptr" ) );
        return nullptr;
    }

    // Widget�𐶐�
    UCountDownWidget* Widget = CreateWidget<UCountDownWidget>( World, WidgetClass );
    if ( Widget ) {
        Widget->AddToViewport( 100 );
        Widget->StartCountdown( );
    }

    return Widget;
}

