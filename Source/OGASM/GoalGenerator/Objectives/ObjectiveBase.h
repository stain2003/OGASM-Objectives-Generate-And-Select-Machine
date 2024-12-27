// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ObjectiveBase.generated.h"

/**
 * 
 */
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateObjective);

UCLASS()
class OGASM_API UObjectiveBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/*Properties*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	bool bIsValid = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Objectives")
	float Weight = 0;
	
	/*Delegate*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpdateObjective UpdateObjectiveDelegate;

	/*Usable API*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitObjective();
	void InitObjective_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReevaluateObjective();
	void ReevaluateObjective_Implementation();
};
