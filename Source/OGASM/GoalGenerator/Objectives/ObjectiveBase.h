﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ObjectiveBase.generated.h"

/**
 * 
 */

class UObjectiveGeneratorComponent;
UCLASS()
class OGASM_API UObjectiveBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	 /*Properties
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	bool bIsValid = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	float Weight = 0;

protected:
	/*
	 * Context Info:
	 * Usually be set when initialized
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Objectives")
	TObjectPtr<UObjectiveGeneratorComponent> ObjectiveGenerator;

public:
	 /*APIs:
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitObjective(UObjectiveGeneratorComponent* Generator);
	void InitObjective_Implementation(UObjectiveGeneratorComponent* Generator);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReevaluateObjective(UObjectiveGeneratorComponent* Generator);
	void ReevaluateObjective_Implementation(UObjectiveGeneratorComponent* Generator);

	
	//Force inline function
	//Get generator of this objective, not editable
	UFUNCTION(BlueprintCallable)
	const UObjectiveGeneratorComponent* GetGoalGenerator() const
	{
		return ObjectiveGenerator;
	}

	//Set generator of this objective
	UFUNCTION(BlueprintCallable)
	void SetGoalGenerator(UObjectiveGeneratorComponent* inObjectiveGenerator)
	{
		ObjectiveGenerator = inObjectiveGenerator;
	}
};
