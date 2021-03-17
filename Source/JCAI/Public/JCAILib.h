// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JCAI/PlannerWorldState.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JCAILib.generated.h"

/**
 * 
 */
UCLASS()
class JCAI_API UJCAILib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState ClearTrait(FPlannerWorldState WorldState, FGameplayTag Trait);
	
	UFUNCTION(BlueprintCallable)
	static FPlannerWorldState SetIntTrait(FPlannerWorldState WorldState, FGameplayTag Trait, int32 Value);

	UFUNCTION(BlueprintCallable)
	static FPlannerWorldState GetIntTrait(FPlannerWorldState WorldState, FGameplayTag Trait, int32& IntValue);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState SetStringTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FString Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetStringTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FString& StringValue);

	UFUNCTION(BlueprintCallable)
	static FPlannerWorldState SetBoolTrait(FPlannerWorldState WorldState, FGameplayTag Trait, bool Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetBoolTrait(FPlannerWorldState WorldState, FGameplayTag Trait, bool& IntValue);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState SetFloatTrait(FPlannerWorldState WorldState, FGameplayTag Trait, float Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetFloatTrait(FPlannerWorldState WorldState, FGameplayTag Trait, float& FloatValue);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState SetVectorTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FVector Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetVectorTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FVector& VectorValue);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState SetClassTrait(FPlannerWorldState WorldState, FGameplayTag Trait, TSubclassOf<UObject> Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetClassTrait(FPlannerWorldState WorldState, FGameplayTag Trait, TSubclassOf<UObject>& ClassValue);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState SetObjectTrait(FPlannerWorldState WorldState, FGameplayTag Trait, UObject* Value);

	UFUNCTION(BlueprintCallable)
    static FPlannerWorldState GetObjectTrait(FPlannerWorldState WorldState, FGameplayTag Trait, UObject*& ObjectValue);
};
