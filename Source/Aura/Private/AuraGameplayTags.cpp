// Copyright Akira Izumiya


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags ()
{
  UGameplayTagsManager& Mgr = UGameplayTagsManager::Get();
  
  GameplayTags.Attributes_Primary_Strength = Mgr.AddNativeGameplayTag(FName("Attributes.Primary.Strength"));
  GameplayTags.Attributes_Primary_Intelligence = Mgr.AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"));
  GameplayTags.Attributes_Primary_Resistance = Mgr.AddNativeGameplayTag(FName("Attributes.Primary.Resistance"));
  GameplayTags.Attributes_Primary_Vitality = Mgr.AddNativeGameplayTag(FName("Attributes.Primary.Vitality"));
  
  GameplayTags.Attributes_Secondary_MaxHealth = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"));
  GameplayTags.Attributes_Secondary_MaxMana = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"));
  
  GameplayTags.Attributes_Secondary_Armor = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"));
  GameplayTags.Attributes_Secondary_ArmorPenetration = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"));
  GameplayTags.Attributes_Secondary_BlockChance = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"));
  GameplayTags.Attributes_Secondary_CritChance = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.CritChance"));
  GameplayTags.Attributes_Secondary_CritDamage = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"));
  GameplayTags.Attributes_Secondary_CritResistance = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.CritResistance"));
  GameplayTags.Attributes_Secondary_HealthRegeneration = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"));
  GameplayTags.Attributes_Secondary_ManaRegeneration = Mgr.AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"));

  
  GameplayTags.Input_LMB = Mgr.AddNativeGameplayTag(FName("Input.LMB"));
  GameplayTags.Input_RMB = Mgr.AddNativeGameplayTag(FName("Input.RMB"));
  GameplayTags.Input_1 = Mgr.AddNativeGameplayTag(FName("Input.1"));
  GameplayTags.Input_2 = Mgr.AddNativeGameplayTag(FName("Input.2"));
  GameplayTags.Input_3 = Mgr.AddNativeGameplayTag(FName("Input.3"));
  GameplayTags.Input_4 = Mgr.AddNativeGameplayTag(FName("Input.4"));
}
