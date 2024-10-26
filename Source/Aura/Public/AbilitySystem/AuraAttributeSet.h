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

    /* Health */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Main Stats")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Main Stats")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

    UFUNCTION()
    void OnRep_MaxHealth (const FGameplayAttributeData& OldMaxHealth) const;
    UFUNCTION()
    void OnRep_Health (const FGameplayAttributeData& OldHealth) const;

    /* Mana */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Main Stats")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Main Stats")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

    UFUNCTION()
    void OnRep_MaxMana (const FGameplayAttributeData& OldMaxMana) const;
    UFUNCTION()
    void OnRep_Mana (const FGameplayAttributeData& OldMana) const;

  private:
    void SetEffectProperties (const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
