// Copyright Akira Izumiya

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
  GENERATED_BODY()

  public:
    virtual void BroadcastInitialValues () override;
    virtual void BindCallbacksToDependencies () override;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxHealthChangedSignature OnMaxHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnMaxManaChangedSignature OnMaxManaChanged;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnManaChangedSignature OnManaChanged;

  protected:
    void MaxHealthChanged (const FOnAttributeChangeData& Data) const;
    void HealthChanged (const FOnAttributeChangeData& Data) const;
  
    void MaxManaChanged (const FOnAttributeChangeData& Data) const;
    void ManaChanged (const FOnAttributeChangeData& Data) const;
};
