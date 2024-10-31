// Copyright Akira Izumiya

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native Gameplay Tags 
 */

struct FAuraGameplayTags
{
  public:
    static const FAuraGameplayTags& Get () { return GameplayTags; }

    static void InitializeNativeGameplayTags ();

    FGameplayTag Attributes_Primary_Strength;
    FGameplayTag Attributes_Primary_Intelligence;
    FGameplayTag Attributes_Primary_Resistance;
    FGameplayTag Attributes_Primary_Vitality;
  
    FGameplayTag Attributes_Secondary_MaxHealth;
    FGameplayTag Attributes_Secondary_MaxMana;
  
    FGameplayTag Attributes_Secondary_Armor;
    FGameplayTag Attributes_Secondary_ArmorPenetration;
    FGameplayTag Attributes_Secondary_BlockChance;
    FGameplayTag Attributes_Secondary_CritChance;
    FGameplayTag Attributes_Secondary_CritDamage;
    FGameplayTag Attributes_Secondary_CritResistance;
    FGameplayTag Attributes_Secondary_HealthRegeneration;
    FGameplayTag Attributes_Secondary_ManaRegeneration;

  protected:

  private:
    static FAuraGameplayTags GameplayTags;
};
