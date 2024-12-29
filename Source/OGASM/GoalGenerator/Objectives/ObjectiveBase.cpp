// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveBase.h"

void UObjectiveBase::InitObjective_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: InitObjective_Implementation called!!!"), *this->GetName())
}

void UObjectiveBase::ReevaluateObjective_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: ReevaluateObjective_Implementation called!!!"), *this->GetName())
}
