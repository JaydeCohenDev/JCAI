// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlannerAction.h"
#include "PlannerWorldState.h"
#include "Components/ActorComponent.h"
#include "AIPlanner.generated.h"

USTRUCT(BlueprintType)
struct FPlannerNode
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlannerWorldState WorldState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGuid ParentId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float G;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float H;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlannerAction* Action;

	float F()
	{
		return G + H;
	}

	bool LowerFThan(FPlannerNode& Other){
		return F() < Other.F();
	}

	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JCAI_API UAIPlanner : public UActorComponent
{
	GENERATED_BODY()

public:
	UAIPlanner();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<TSubclassOf<UPlannerAction>> AvailableActions;

	// Filled from available actions on start
	UPROPERTY()
	TArray<UPlannerAction*> Actions;

	UFUNCTION()
	FPlannerNode FindOnOpen(FPlannerWorldState WorldState, bool& found);

	UFUNCTION()
	FPlannerNode PopAndClose();
	
	UFUNCTION(BlueprintCallable)
	void Plan(FPlannerWorldState Start, FPlannerWorldState Goal, bool& Success);

	UFUNCTION(BlueprintCallable)
	void StartExecutingPlan();

	UFUNCTION(BlueprintCallable)
	void StopExecutingPlan();

	UFUNCTION(BlueprintCallable)
	TArray<UPlannerAction*> GetCurrentPlan();

	UFUNCTION()
	float CalculateHeuristic(const FPlannerWorldState& Start, const FPlannerWorldState& Goal);

	UFUNCTION()
	bool IsClosed(FPlannerWorldState WorldState);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	FPlannerNode GetParent(FPlannerNode Node);

	UPROPERTY()
	TArray<UPlannerAction*> CurrentPlan;

	UPROPERTY()
	TArray<FPlannerNode> OpenList;

	UPROPERTY()
	TArray<FPlannerNode> ClosedList;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

