// Copyright Akira Izumiya


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor ()
{
  PrimaryActorTick.bCanEverTick = false;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
  SetRootComponent(Mesh);
  
  Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
  Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::BeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                     bool bFromSweep, const FHitResult& SweepResult)
{
  // TODO: Change this to apply a GameplayEffect. For now, using const_cast as a hack (learning purposes)
  IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
  if (!ASCInterface) return;

  const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()
                                              ->GetAttributeSet(UAuraAttributeSet::StaticClass()));
  UAuraAttributeSet* MutableAuraAS = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
  MutableAuraAS->SetHealth(AuraAttributeSet->GetHealth() + 25.f);

  Destroy();
}

void AAuraEffectActor::EndOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay ()
{
  Super::BeginPlay();

  Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::BeginOverlap);
  Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}
