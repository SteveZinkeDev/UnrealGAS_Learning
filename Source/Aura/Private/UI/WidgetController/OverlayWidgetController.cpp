// Copyright Akira Izumiya


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValues ()
{
  const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
  
  OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
  OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
  
  OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
  OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies ()
{
  const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
                          .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
                          .AddUObject(this, &UOverlayWidgetController::HealthChanged);

  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
                          .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

  AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
                          .AddUObject(this, &UOverlayWidgetController::ManaChanged);
}

void UOverlayWidgetController::MaxHealthChanged (const FOnAttributeChangeData& Data) const
{
  OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HealthChanged (const FOnAttributeChangeData& Data) const
{
  OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged (const FOnAttributeChangeData& Data) const
{
  OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged (const FOnAttributeChangeData& Data) const
{
  OnManaChanged.Broadcast(Data.NewValue);
}
