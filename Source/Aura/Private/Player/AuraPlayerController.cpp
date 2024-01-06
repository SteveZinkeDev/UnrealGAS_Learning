// Copyright Akira Izumiya


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController ()
{
  bReplicates = true;
}

void AAuraPlayerController::PlayerTick (float DeltaTime)
{
  Super::PlayerTick(DeltaTime);

  CursorTrace();
}

void AAuraPlayerController::BeginPlay ()
{
  Super::BeginPlay();
  check(AuraContext);

  UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
  check(Subsystem);

  Subsystem->AddMappingContext(AuraContext, 0);

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

  UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

  EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move (const FInputActionValue& InputActionValue)
{
  /*
   * The commented code below is from the course and both unnecessary as well as error-prone (with the current setup).
   * The camera will be fixed in this game, hence the X/Y directions will also be in accordance with the world axes.
   * With the commented code below, the movement will depend on the rotation of the player start,
   * meaning if it's rotation by 180 degrees, all inputs will be reversed...
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
  FHitResult CursorHit;
  GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

  if (!CursorHit.bBlockingHit) return;

  LastActor = CurrActor;
  CurrActor = Cast<IEnemyInterface>(CursorHit.GetActor());

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
