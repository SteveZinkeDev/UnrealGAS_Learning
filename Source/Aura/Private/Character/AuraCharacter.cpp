// Copyright Akira Izumiya


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter ()
{
  GetCharacterMovement()->bOrientRotationToMovement = true;
  GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
  GetCharacterMovement()->bConstrainToPlane = true;
  GetCharacterMovement()->bSnapToPlaneAtStart = true;

  bUseControllerRotationPitch = false;
  bUseControllerRotationRoll = false;
  bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy (AController* NewController)
{
  Super::PossessedBy(NewController);

  // Init ability actor infos for the server
  InitAbilityActorInfo();
  AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState ()
{
  Super::OnRep_PlayerState();

  // Init ability actor infos for the client
  InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel ()
{
  const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
  check(AuraPlayerState);
  
  return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::InitAbilityActorInfo ()
{
  AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
  check(AuraPlayerState);
  
  AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
  AttributeSet = AuraPlayerState->GetAttributeSet();

  AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
  Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

  InitializeDefaultAttributes();

  AAuraPlayerController* APC = Cast<AAuraPlayerController>(GetController());
  if (APC)
  {
    AAuraHUD* AHUD = Cast<AAuraHUD>(APC->GetHUD());
    if (AHUD)
    {
      AHUD->InitOverlay(APC, AuraPlayerState, AbilitySystemComponent, AttributeSet);
    }
  }
}
