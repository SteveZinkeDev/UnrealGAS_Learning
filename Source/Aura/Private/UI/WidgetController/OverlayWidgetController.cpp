// Copyright Akira Izumiya


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
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
  UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);

  AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
    [this](const FOnAttributeChangeData& Data)
    {
      OnMaxHealthChanged.Broadcast(Data.NewValue);
    }
  );

  AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
    [this](const FOnAttributeChangeData& Data)
    {
      OnHealthChanged.Broadcast(Data.NewValue);
    }
  );

  AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
    [this](const FOnAttributeChangeData& Data)
    {
      OnMaxManaChanged.Broadcast(Data.NewValue);
    }
  );

  AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
    [this](const FOnAttributeChangeData& Data)
    {
      OnManaChanged.Broadcast(Data.NewValue);
    }
  );

  AuraASC->EffectAssetTags.AddLambda(
    [this](const FGameplayTagContainer& AssetTags)
    {
      for (const FGameplayTag& Tag : AssetTags)
      {
        // "A.1" MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
        FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
        if (!Tag.MatchesTag(MessageTag)) continue;
        
        const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
        MessageWidgetRowDelegate.Broadcast(*Row);
      }
    }
  );
}
