// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlanner.h"

UAIPlanner::UAIPlanner()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIPlanner::CurrentActionComplete(bool Success)
{
}

FPlannerNode UAIPlanner::FindOnOpen(FPlannerWorldState WorldState, bool& found)
{
	found = true;
	for(FPlannerNode n : OpenList)
	{
		if(n.WorldState.Matches(WorldState)) return n;
	}

	found = false;
	return FPlannerNode();
}

FPlannerNode UAIPlanner::PopAndClose()
{
	FPlannerNode Node = OpenList[0];
	float LowestF = Node.F();
	int NodeIndex = 0;
	
	for(int32 i = 0; i < OpenList.Num(); i++)
	{
		if(OpenList[i].F() < LowestF)
		{
			Node = OpenList[i];
			LowestF = Node.F();
			NodeIndex = i;
		}
	}
	
	ClosedList.Add(Node);
	OpenList.RemoveAt(NodeIndex);

	return Node;
}

void UAIPlanner::Plan(FPlannerWorldState Start, FPlannerWorldState Goal, bool& Success)
{
	Success = false;
	FString DebugStart = Start.ToString();
	FString DebugGoal = Goal.ToString();

	// Fail out if there are no actions available
	if(AvailableActions.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Planner has no actions"));
		return;
	}

	// Clear out old plan
	CurrentPlan = TArray<UPlannerAction*>();

	if(Start.Matches(Goal))
	{
		UE_LOG(LogTemp, Error, TEXT("Planner cannot plan when the start state and the goal state are the same!"));
	}

	// Feasible we'd re-use a planner, so clear out the prior results
	OpenList = TArray<FPlannerNode>();
	ClosedList = TArray<FPlannerNode>();

	// Create start node
	FPlannerNode StartingNode = FPlannerNode();
	StartingNode.Id = FGuid::NewGuid();
	StartingNode.WorldState = Start;
	StartingNode.G = 0;
	StartingNode.H = CalculateHeuristic(Start, Goal);
	StartingNode.Action = nullptr;
	OpenList.Add(StartingNode);

	while(OpenList.Num() > 0)
	{
		// Look for Node with the lowest-F-score on the open list. Switch it to closed,
		// and hang onto it -- this is our latest node.
		FPlannerNode Current = PopAndClose();

		// Is our current state the goal state? If so, we've found a path, yay.
		FString DebugCurrent = Current.WorldState.ToString();
		if(Current.WorldState.Matches(Goal))
		{
			UE_LOG(LogTemp, Error, TEXT("Goal found!"));
			TArray<UPlannerAction*> FinalPlan = TArray<UPlannerAction*>();
			do
			{
				FinalPlan.Add(Current.Action);
				Current = GetParent(Current);
			}while(Current.ParentId.IsValid());

			// Output final plan
			CurrentPlan = FinalPlan;
			Algo::Reverse(CurrentPlan);
			Success = true;
			return;
		}

		for(UPlannerAction* Action : Actions)
		{
			if(Action->MeetsConditions(Current.WorldState))
			{
				FPlannerWorldState Outcome = Action->AlterWorldState(Current.WorldState);
				FString DebugOutcome = Outcome.ToString();


				// Skip if already closed
				if(IsClosed(Outcome)) continue;

				// Look for node with this worldstate on open list
				bool foundOnOpen = false;
				FPlannerNode OutcomeNode = FindOnOpen(Outcome, foundOnOpen);

				// not a member of open list
				if(!foundOnOpen)
				{
					FPlannerNode Node = FPlannerNode();
					//const WorldState state, int g, int h, int parent_id, const Action* action
					Node.WorldState = Outcome;
					Node.G = Current.G + Action->GetCost();
					Node.H = CalculateHeuristic(Outcome, Goal);
					Node.ParentId = Current.Id;
					Node.Action = Action;
					Node.Id = FGuid::NewGuid();

					OpenList.Add(Node);
				} else // already a member of the open list
				{
					// check if the current G is better than the recorded G
					if(Current.G + Action->GetCost() < OutcomeNode.G)
					{
						OutcomeNode.ParentId = Current.Id; // make current its parent
						OutcomeNode.G = Current.G + Action->GetCost(); // recalc G & H
						OutcomeNode.H = CalculateHeuristic(Outcome, Goal);
						OutcomeNode.Action = Action;

						// resort open list to account for the new F
						// sorting likely invalidates the p_outcome_node iterator, but we don't need it anymore
						
					}
				}
			}
		}
	}

	UE_LOG(LogTemp, Error, TEXT("A* planner could not find a path from start to goal"));
}

void UAIPlanner::StartExecutingPlan()
{
}

void UAIPlanner::StopExecutingPlan()
{
}

TArray<UPlannerAction*> UAIPlanner::GetCurrentPlan()
{
	return CurrentPlan;
}

float UAIPlanner::CalculateHeuristic(const FPlannerWorldState& Start, const FPlannerWorldState& Goal)
{
	return Start.DistanceTo(Goal);
}

void UAIPlanner::BeginPlay()
{
	Super::BeginPlay();

	for(auto ActionClass : AvailableActions)
	{
		Actions.Add(NewObject<UPlannerAction>(this, ActionClass));
	}
}

FPlannerNode UAIPlanner::GetParent(FPlannerNode Node)
{
	for(FPlannerNode n : OpenList)
		if(n.Id == Node.ParentId)
			return n;

	for(FPlannerNode n : ClosedList)
		if(n.Id == Node.ParentId)
			return n;
	
	return FPlannerNode();
}

void UAIPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UAIPlanner::IsClosed(FPlannerWorldState WorldState)
{
	for(FPlannerNode n : ClosedList)
	{
		if(n.WorldState.Matches(WorldState))
			return true;
	}

	return false;
}
