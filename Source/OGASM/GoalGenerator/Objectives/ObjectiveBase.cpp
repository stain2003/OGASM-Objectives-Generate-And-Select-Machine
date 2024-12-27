// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveBase.h"

void UObjectiveBase::InitObjective_Implementation()
{
	UpdateObjectiveDelegate.AddDynamic(this, &UObjectiveBase::ReevaluateObjective);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.5f, FColor::Orange, FString("ReevaluateObjective_Implementation called!!!"));
	}
}

void UObjectiveBase::ReevaluateObjective_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.5f, FColor::Orange, FString("ReevaluateObjective_Implementation called!!!"));
	}
}
