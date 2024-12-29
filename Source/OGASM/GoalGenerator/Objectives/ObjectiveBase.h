// Fill out your copyright notice in the Description page of Project Settings.

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
	/***************************************
	 *Properties
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	bool bIsValid = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	float Weight = 0;

protected:
	/****************************************
	 *Context Info:
	 *Usually be set when initialized
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Objectives")
	TObjectPtr<UObjectiveGeneratorComponent> ObjectiveGenerator;

public:
	/****************************************
	 *APIs:
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitObjective();
	void InitObjective_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReevaluateObjective();
	void ReevaluateObjective_Implementation();

	
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
