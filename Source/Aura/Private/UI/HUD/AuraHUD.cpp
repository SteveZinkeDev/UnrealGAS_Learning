// Copyright Akira Izumiya


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController (const FWidgetControllerParams& WCParams)
{
  if (OverlayWidgetController == nullptr)
  {
    OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
    OverlayWidgetController->SetWidgetControllerParams(WCParams);
    OverlayWidgetController->BindCallbacksToDependencies();
  }

  return OverlayWidgetController;
}

void AAuraHUD::InitOverlay (APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
  ensureMsgf(OverlayWidgetClass, TEXT("Overlay Widget Class not initialized, please fill out BP_AuraHUD"));
  ensureMsgf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class not initialized, please fill out BP_AuraHUD"));
  
  UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
  OverlayWidget = Cast<UAuraUserWidget>(Widget);

  const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
  UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

  OverlayWidget->SetWidgetController(WidgetController);
  WidgetController->BroadcastInitialValues();
  
  Widget->AddToViewport();
}
