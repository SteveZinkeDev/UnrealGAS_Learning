// Copyright Akira Izumiya

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
        GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
        GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
        GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
        GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
  GENERATED_BODY()

  FEffectProperties ()
  {
  }

  FGameplayEffectContextHandle EffectContextHandle;

  UPROPERTY()
  UAbilitySystemComponent* SourceASC = nullptr;
  UPROPERTY()
  AActor* SourceAvatarActor = nullptr;
  UPROPERTY()
  AController* SourceController = nullptr;
  UPROPERTY()
  ACharacter* SourceCharacter = nullptr;

  UPROPERTY()
  UAbilitySystemComponent* TargetASC = nullptr;
  UPROPERTY()
  AActor* TargetAvatarActor = nullptr;
  UPROPERTY()
  AController* TargetController = nullptr;
  UPROPERTY()
  ACharacter* TargetCharacter = nullptr;
};

// typedef is specific to the FGameplayAttribute() signature but TStaticFuncPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
  GENERATED_BODY()

  public:
    UAuraAttributeSet ();

    virtual void GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange (const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PreAttributeBaseChange (const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void PostGameplayEffectExecute (const struct FGameplayEffectModCallbackData& Data) override;

    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

    /*
     * Primary Attributes
     */

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resistance, Category = "Primary Attributes")
    FGameplayAttributeData Resistance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resistance);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category = "Primary Attributes")
    FGameplayAttributeData Vitality;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vitality);


    UFUNCTION()
    void OnRep_Strength (const FGameplayAttributeData& OldStrength) const;
    UFUNCTION()
    void OnRep_Intelligence (const FGameplayAttributeData& OldIntelligence) const;
    UFUNCTION()
    void OnRep_Resistance (const FGameplayAttributeData& OldResistance) const;
    UFUNCTION()
    void OnRep_Vitality (const FGameplayAttributeData& OldVitality) const;

    /*
     * Secondary Attributes
     */

    /* Health */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Secondary Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

    UFUNCTION()
    void OnRep_MaxHealth (const FGameplayAttributeData& OldMaxHealth) const;
    UFUNCTION()
    void OnRep_Health (const FGameplayAttributeData& OldHealth) const;

    /* Mana */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Secondary Attributes")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

    UFUNCTION()
    void OnRep_MaxMana (const FGameplayAttributeData& OldMaxMana) const;
    UFUNCTION()
    void OnRep_Mana (const FGameplayAttributeData& OldMana) const;

    /* Other */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

    UFUNCTION()
    void OnRep_Armor (const FGameplayAttributeData& OldArmor) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

    UFUNCTION()
    void OnRep_ArmorPenetration (const FGameplayAttributeData& OldArmorPenetration) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

    UFUNCTION()
    void OnRep_BlockChance (const FGameplayAttributeData& OldBlockChance) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "Secondary Attributes")
    FGameplayAttributeData CritChance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritChance);

    UFUNCTION()
    void OnRep_CritChance (const FGameplayAttributeData& OldCritChance) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDamage, Category = "Secondary Attributes")
    FGameplayAttributeData CritDamage;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritDamage);

    UFUNCTION()
    void OnRep_CritDamage (const FGameplayAttributeData& OldCritDamage) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritResistance, Category = "Secondary Attributes")
    FGameplayAttributeData CritResistance;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritResistance);

    UFUNCTION()
    void OnRep_CritResistance (const FGameplayAttributeData& OldCritResistance) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

    UFUNCTION()
    void OnRep_HealthRegeneration (const FGameplayAttributeData& OldHealthRegeneration) const;


    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

    UFUNCTION()
    void OnRep_ManaRegeneration (const FGameplayAttributeData& OldManaRegeneration) const;

  private:
    void SetEffectProperties (const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
