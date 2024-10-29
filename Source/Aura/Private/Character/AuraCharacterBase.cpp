// Copyright Akira Izumiya


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase ()
{
  PrimaryActorTick.bCanEverTick = false;

  Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
  Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
  Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent () const
{
  return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay ()
{
  Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo ()
{
}

void AAuraCharacterBase::ApplyEffectToSelf (TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
  check(IsValid(GetAbilitySystemComponent()));
  check(IsValid(GameplayEffectClass));
  
  FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
  ContextHandle.AddSourceObject(this);
  
  const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
  
  //GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
  GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AAuraCharacterBase::InitializeDefaultAttributes () const
{
  ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
  ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
  ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}
