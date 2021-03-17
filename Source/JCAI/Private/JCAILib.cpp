// Fill out your copyright notice in the Description page of Project Settings.


#include "JCAILib.h"

FPlannerWorldState UJCAILib::ClearTrait(FPlannerWorldState WorldState, FGameplayTag Trait)
{
	WorldState.Traits.Remove(Trait);
	return WorldState;
}

FPlannerWorldState UJCAILib::SetIntTrait(FPlannerWorldState WorldState, FGameplayTag Trait, int32 Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.IntValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetIntTrait(FPlannerWorldState WorldState, FGameplayTag Trait, int32& IntValue)
{
	IntValue = 0;
	if(WorldState.Traits.Contains(Trait))
	{
		IntValue = WorldState.Traits[Trait].IntValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetStringTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FString Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.StringValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetStringTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FString& StringValue)
{
	StringValue = "";
	if(WorldState.Traits.Contains(Trait))
	{
		StringValue = WorldState.Traits[Trait].StringValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetBoolTrait(FPlannerWorldState WorldState, FGameplayTag Trait, bool Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.BoolValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetBoolTrait(FPlannerWorldState WorldState, FGameplayTag Trait, bool& BoolValue)
{
	BoolValue = false;
	if(WorldState.Traits.Contains(Trait))
	{
		BoolValue = WorldState.Traits[Trait].BoolValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetFloatTrait(FPlannerWorldState WorldState, FGameplayTag Trait, float Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.FloatValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetFloatTrait(FPlannerWorldState WorldState, FGameplayTag Trait, float& FloatValue)
{
	FloatValue = 0.f;
	if(WorldState.Traits.Contains(Trait))
	{
		FloatValue = WorldState.Traits[Trait].FloatValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetVectorTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FVector Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.VectorValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetVectorTrait(FPlannerWorldState WorldState, FGameplayTag Trait, FVector& VectorValue)
{
	VectorValue = FVector::ZeroVector;
	if(WorldState.Traits.Contains(Trait))
	{
		VectorValue = WorldState.Traits[Trait].VectorValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetClassTrait(FPlannerWorldState WorldState, FGameplayTag Trait,
	TSubclassOf<UObject> Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.ClassValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetClassTrait(FPlannerWorldState WorldState, FGameplayTag Trait,
	TSubclassOf<UObject>& ClassValue)
{
	ClassValue = nullptr;
	if(WorldState.Traits.Contains(Trait))
	{
		ClassValue = WorldState.Traits[Trait].ClassValue;
	}
	return WorldState;
}

FPlannerWorldState UJCAILib::SetObjectTrait(FPlannerWorldState WorldState, FGameplayTag Trait, UObject* Value)
{
	FPlannerTrait TVal = FPlannerTrait();
	TVal.ObjectValue = Value;
	
	WorldState.Traits.Add(Trait, TVal);
	
	return WorldState;
}

FPlannerWorldState UJCAILib::GetObjectTrait(FPlannerWorldState WorldState, FGameplayTag Trait, UObject*& ObjectValue)
{
	ObjectValue = nullptr;
	if(WorldState.Traits.Contains(Trait))
	{
		ObjectValue = WorldState.Traits[Trait].ObjectValue;
	}
	return WorldState;
}
