// Copyright Akira Izumiya


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet ()
{
  InitMaxHealth(400.f);
  InitHealth(300.f);
  InitMaxMana(200.f);
  InitMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps (TArray<FLifetimeProperty>& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange (const FGameplayAttribute& Attribute, float& NewValue)
{
  Super::PreAttributeChange(Attribute, NewValue);

  NewValue = FMath::Max(0.f, NewValue);

  if (Attribute == GetHealthAttribute())
  {
    NewValue = FMath::Min(GetMaxHealth(), NewValue);
  }
  else if (Attribute == GetManaAttribute())
  {
    NewValue = FMath::Min(GetMaxMana(), NewValue);
  }
}

void UAuraAttributeSet::PreAttributeBaseChange (const FGameplayAttribute& Attribute, float& NewValue) const
{
  Super::PreAttributeBaseChange(Attribute, NewValue);

  NewValue = FMath::Max(0.f, NewValue);

  if (Attribute == GetHealthAttribute())
  {
    NewValue = FMath::Min(GetMaxHealth(), NewValue);
  }
  else if (Attribute == GetManaAttribute())
  {
    NewValue = FMath::Min(GetMaxMana(), NewValue);
  }
}

void UAuraAttributeSet::PostGameplayEffectExecute (const struct FGameplayEffectModCallbackData& Data)
{
  Super::PostGameplayEffectExecute(Data);

  FEffectProperties Props;
  SetEffectProperties(Data, Props);
}

void UAuraAttributeSet::SetEffectProperties (const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
  // Source = causer of the effect | Target = target of the effect (owner of this AS)

  Props.EffectContextHandle = Data.EffectSpec.GetContext();
  Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

  if (IsValid(Props.SourceASC))
  {
    Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
    Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
    
    if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
    {
      if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
      {
        Props.SourceController = Pawn->GetController();
      }
    }

    if (Props.SourceController)
    {
      Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
    }
  }

  Props.TargetAvatarActor = Data.Target.GetAvatarActor();
  Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
  Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
  Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
}

void UAuraAttributeSet::OnRep_MaxHealth (const FGameplayAttributeData& OldMaxHealth) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Health (const FGameplayAttributeData& OldHealth) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxMana (const FGameplayAttributeData& OldMaxMana) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_Mana (const FGameplayAttributeData& OldMana) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}
