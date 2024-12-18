// Copyright Akira Izumiya

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
  GENERATED_BODY()

  public:
    AAuraPlayerController ();
  
    virtual void PlayerTick (float DeltaTime) override;

  protected:
    virtual void BeginPlay () override;
    virtual void SetupInputComponent () override;

  private:
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> AuraContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    void Move (const FInputActionValue& InputActionValue);
    void CursorTrace ();
    FHitResult CursorHit;

    UPROPERTY()
    TScriptInterface<IEnemyInterface> LastActor;
    UPROPERTY()
    TScriptInterface<IEnemyInterface> CurrActor;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UAuraInputConfig> InputConfig;

    void AbilityInputPressed (FGameplayTag InputTag);
    void AbilityInputReleased (FGameplayTag InputTag);
    void AbilityInputHeld (FGameplayTag InputTag);

    UPROPERTY()
    TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

    UAuraAbilitySystemComponent* GetASC ();

    FVector CachedDestination = FVector::ZeroVector;
    float FollowTime = 0.f;
    float ShortPressThreshold = 0.5f;
    bool bAutoRunning = false;
    bool bTargeting = false;
  
    UPROPERTY(EditDefaultsOnly)
    float AutoRunAcceptanceRadius = 50.f;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USplineComponent> Spline;

    void AutoRun ();
};
