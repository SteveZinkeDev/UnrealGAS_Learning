// Copyright Akira Izumiya


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth ()
{
  VitalityDefinition.AttributeToCapture = UAuraAttributeSet::GetVitalityAttribute();
  VitalityDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
  VitalityDefinition.bSnapshot = false;

  RelevantAttributesToCapture.Add(VitalityDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation (const FGameplayEffectSpec& Spec) const
{
  // Gather tags from source and target
  const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
  const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

  FAggregatorEvaluateParameters EvaluationParams;
  EvaluationParams.SourceTags = SourceTags;
  EvaluationParams.TargetTags = TargetTags;

  float Vitality = 0;
  GetCapturedAttributeMagnitude(VitalityDefinition, Spec, EvaluationParams, Vitality);
  Vitality = FMath::Max<float>(Vitality, 0.f);

  ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
  const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
  
  return 80.f + (2.5f * Vitality) + (10.f * PlayerLevel);
}
