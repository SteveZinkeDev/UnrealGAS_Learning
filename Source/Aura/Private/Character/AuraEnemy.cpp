// Copyright Akira Izumiya


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy ()
{
  GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
  GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
  Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

  AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
  AbilitySystemComponent->SetIsReplicated(true);
  AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

  AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay ()
{
  Super::BeginPlay();

  InitAbilityActorInfo();
}

void AAuraEnemy::InitAbilityActorInfo ()
{
  AbilitySystemComponent->InitAbilityActorInfo(this, this);
  Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}

void AAuraEnemy::HighlightActor ()
{
  GetMesh()->SetRenderCustomDepth(true);
  Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor ()
{
  GetMesh()->SetRenderCustomDepth(false);
  Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel ()
{
  return Level;
}
