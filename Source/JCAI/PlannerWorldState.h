#pragma once

#include "GameplayTagContainer.h"
#include "PlannerTrait.h"
#include "PlannerWorldState.generated.h"

USTRUCT(BlueprintType)
struct FPlannerWorldState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FGameplayTag, FPlannerTrait> Traits;

	bool Matches(const FPlannerWorldState& Other) const
	{

		for(const TPair<FGameplayTag, FPlannerTrait>& pair : Other.Traits)
		{
			if(!Traits.Contains(pair.Key)) return false;
			if(!(Traits[pair.Key].Matches(pair.Value))) return false; 
		}
		
		return true;
	}

	int32 DistanceTo(const FPlannerWorldState& Other) const
	{
		int32 result = 0;

		for(const TPair<FGameplayTag, FPlannerTrait>& pair : Traits)
		{
			if(!Other.Traits.Contains(pair.Key))
			{
				result++;
			} else {
				if(!(Other.Traits[pair.Key].Matches(pair.Value)))
				{
					result++;
				}
			}
		}
		
		return result;
	}

	FString ToString()
	{
		FString out = "";
		for(const TPair<FGameplayTag, FPlannerTrait>& pair : Traits)
		{
			out += pair.Key.ToString()+"="+FString::FromInt(pair.Value.IntValue)+", ";
		}
		return out;
	}
};