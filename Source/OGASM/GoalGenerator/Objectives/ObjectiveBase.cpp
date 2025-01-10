// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveBase.h"
#include "OGASM/GoalGenerator/GeneratorComponent/GeneratorComponent.h"

/*
 * c++ objective initialization implement
 */
void UObjectiveBase::InitObjective_Implementation(UObjectiveGeneratorComponent* Generator)
{
	//Binding ReevaluateObjective_Implementation() 'RO' to ObjectiveReevaluateDelegate() of Objective Generator
	//RO will be called once generator set timer to call this delegate
	if (Generator != nullptr)
	{
		ObjectiveGenerator = Generator;
		ObjectiveGenerator->ObjectiveReevaluateDelegate.AddDynamic(this, &UObjectiveBase::ReevaluateObjective);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Initialization failed!: Invalid ObjectiveGenerator pointer!"), *this->GetName())
	}
}

/*
 * C++ objective reevaluate implementation
 */
void UObjectiveBase::ReevaluateObjective_Implementation(UObjectiveGeneratorComponent* Generator)
{
	check(Generator != nullptr);
}
