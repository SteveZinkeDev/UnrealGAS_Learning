// Copyright Akira Izumiya


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController (const UObject* WorldContextObject)
{
  if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
  {
    if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
    {
      AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
      UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
      UAttributeSet* AS = PS->GetAttributeSet();

      const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
      
      return HUD->GetOverlayWidgetController(WidgetControllerParams);
    }
  }

  return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController (const UObject* WorldContextObject)
{
  if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
  {
    if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
    {
      AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
      UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
      UAttributeSet* AS = PS->GetAttributeSet();

      const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
      
      return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
    }
  }

  return nullptr;
}
