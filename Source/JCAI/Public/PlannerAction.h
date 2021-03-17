// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "JCAI/PlannerWorldState.h"
#include "UObject/Object.h"
#include "PlannerAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JCAI_API UPlannerAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBehaviorTree* ActionBehavior;

	UFUNCTION(BlueprintImplementableEvent)
	bool MeetsConditions(FPlannerWorldState WorldState);

	UFUNCTION(BlueprintImplementableEvent)
	FPlannerWorldState AlterWorldState(const FPlannerWorldState WorldState);

	UFUNCTION(BlueprintImplementableEvent)
	float GetCost();
};
