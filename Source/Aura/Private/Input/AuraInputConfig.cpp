// Copyright Akira Izumiya


#include "Input/AuraInputConfig.h"
#include "GameplayTagContainer.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag (const FGameplayTag& InputTag, bool bLogNotFound) const
{
  for (const FAuraInputAction& IA : AbilityInputActions)
  {
    if (IA.InputAction && IA.InputTag.MatchesTagExact(InputTag))
    {
      return IA.InputAction;
    }
  }

  if (bLogNotFound)
  {
    UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]"),
                                *InputTag.ToString(), *GetNameSafe(this));
  }

  return nullptr;
}
