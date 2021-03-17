#pragma once

#include "PlannerTrait.generated.h"

USTRUCT(BlueprintType)
struct FPlannerTrait
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 IntValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FloatValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector VectorValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UObject> ClassValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* ObjectValue;

	bool Matches(const FPlannerTrait& Other) const
	{
		return IntValue == Other.IntValue && FloatValue == Other.FloatValue && VectorValue == Other.VectorValue &&
            ClassValue == Other.ClassValue && ObjectValue == Other.ObjectValue;
	}
	
};