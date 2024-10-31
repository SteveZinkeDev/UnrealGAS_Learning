// Copyright Akira Izumiya


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController ()
{
  bReplicates = true;

  Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick (float DeltaTime)
{
  Super::PlayerTick(DeltaTime);

  CursorTrace();
  AutoRun();
}

void AAuraPlayerController::AutoRun ()
{
  if (!bAutoRunning) return;
  
  if (APawn* ControlledPawn = GetPawn())
  {
    const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
    const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
    ControlledPawn->AddMovementInput(Direction);

    const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
    if (DistanceToDestination <= AutoRunAcceptanceRadius)
    {
      bAutoRunning = false;
    }
  }
}

void AAuraPlayerController::BeginPlay ()
{
  Super::BeginPlay();
  check(AuraContext);

  UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
  if (Subsystem) Subsystem->AddMappingContext(AuraContext, 0);

  bShowMouseCursor = true;
  DefaultMouseCursor = EMouseCursor::Default;

  FInputModeGameAndUI InputModeData;
  InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
  InputModeData.SetHideCursorDuringCapture(false);

  SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent ()
{
  Super::SetupInputComponent();

  UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

  AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

  AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, &ThisClass::AbilityInputHeld);
}

void AAuraPlayerController::Move (const FInputActionValue& InputActionValue)
{
  /*
   * The commented code below is from the course and both unnecessary as well as error-prone (with the current setup).
   * The camera will be fixed in this game, hence the X/Y directions will also be in accordance with the world axes.
   * With the commented code below, the movement will depend on the rotation of the player start,
   * meaning if it's rotated by 180 degrees, all inputs will be reversed...
   * -> Inheriting Yaw during start would solve this problem but again, this isn't even what we want according to the course.
   */

  /*const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
  const FRotator Rotation = GetControlRotation();
  const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

  const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
  const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

  if (APawn* ControlledPawn = GetPawn<APawn>())
  {
    ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
    ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
  }*/

  const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

  if (APawn* ControlledPawn = GetPawn<APawn>())
  {
    ControlledPawn->AddMovementInput(FVector::ForwardVector, InputAxisVector.Y);
    ControlledPawn->AddMovementInput(FVector::RightVector, InputAxisVector.X);
  }
}

void AAuraPlayerController::CursorTrace ()
{
  GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

  if (!CursorHit.bBlockingHit) return;

  LastActor = CurrActor;
  CurrActor = CursorHit.GetActor();

  if (LastActor == CurrActor) return;

  if (CurrActor != nullptr)
  {
    CurrActor->HighlightActor();
  }
  if (LastActor != nullptr)
  {
    LastActor->UnHighlightActor();
  }
}

void AAuraPlayerController::AbilityInputPressed (FGameplayTag InputTag)
{
  if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB))
  {
    bTargeting = (CurrActor != nullptr);
    bAutoRunning = false;
  }
}

void AAuraPlayerController::AbilityInputReleased (FGameplayTag InputTag)
{
  // not LMB || LMB while targeting an enemy -> use ability
  if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB) || bTargeting)
  {
    if (GetASC())
    {
      GetASC()->AbilityInputTagReleased(InputTag);
    }
  }
  else // move
  {
    const APawn* ControlledPawn = GetPawn();
    if (FollowTime <= ShortPressThreshold && ControlledPawn)
    {
      if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,
                                                                                          ControlledPawn->GetActorLocation(),
                                                                                          CachedDestination))
      {
        Spline->ClearSplinePoints();
        for (const FVector& PointLoc : NavPath->PathPoints)
        {
          Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
        }
        
        if (!NavPath->PathPoints.IsEmpty()) CachedDestination = NavPath->PathPoints.Last();
        bAutoRunning = true;
      }
    }
      
    bTargeting = false;
    FollowTime = 0.f;
  }
}

void AAuraPlayerController::AbilityInputHeld (FGameplayTag InputTag)
{
  // not LMB || LMB while targeting an enemy -> use ability
  if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB) || bTargeting)
  {
    if (GetASC())
    {
      GetASC()->AbilityInputTagHeld(InputTag);
    }
  }
  else // move
  {
    FollowTime += GetWorld()->GetDeltaSeconds();
    
    if (CursorHit.bBlockingHit)
    {
      CachedDestination = CursorHit.ImpactPoint;
    }

    if (APawn* ControlledPawn = GetPawn())
    {
      const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
      ControlledPawn->AddMovementInput(WorldDirection);
    }
  }
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC ()
{
  if (AuraAbilitySystemComponent == nullptr)
  {
    AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
  }

  return AuraAbilitySystemComponent;
}
