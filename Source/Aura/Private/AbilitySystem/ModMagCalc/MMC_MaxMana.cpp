// Copyright Akira Izumiya


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana ()
{
  IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
  IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
  IntelligenceDefinition.bSnapshot = false;

  RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation (const FGameplayEffectSpec& Spec) const
{
  // Gather tags from source and target
  const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
  const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

  FAggregatorEvaluateParameters EvaluationParams;
  EvaluationParams.SourceTags = SourceTags;
  EvaluationParams.TargetTags = TargetTags;

  float Intelligence = 0;
  GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluationParams, Intelligence);
  Intelligence = FMath::Max<float>(Intelligence, 0.f);

  ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
  const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
  
  return 50.f + (5.f * Intelligence) + (5.f * PlayerLevel);
}
