// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveBase.h"
#include "OGASM/GoalGenerator/GeneratorComponent/GeneratorComponent.h"

void UObjectiveBase::InitObjective_Implementation(UObjectiveGeneratorComponent* Generator)
{
	if (Generator != nullptr)
	{
		ObjectiveGenerator = Generator;
		ObjectiveGenerator->ObjectiveReevaluateDelegate.AddDynamic(this, &UObjectiveBase::ReevaluateObjective);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Initialization failed!: Invalid ObjectiveGenerator pointer!"), *this->GetName())
	}
	UE_LOG(LogTemp, Warning, TEXT("%s: InitObjective_Implementation called!!!"), *this->GetName())
}

void UObjectiveBase::ReevaluateObjective_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: ReevaluateObjective_Implementation called!!!"), *this->GetName())
}
