// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"
#include "GeneratorComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObjectiveReevaluateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectiveReevaluateDelegate, UObjectiveGeneratorComponent*, Generator);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OGASM_API UObjectiveGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectiveGeneratorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	/***************************************************************************************************************
	 * Generator Related:
	 */
public:
	//Delegate to bind Objectives' update function to, broadcast by ReevaluateObjectivesTimerHandle
	UPROPERTY(BlueprintAssignable)
	FObjectiveReevaluateDelegate ObjectiveReevaluateDelegate;
	
protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator|Objectives")
	TArray<TSubclassOf<UObjectiveBase>> ObjectiveTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator|Objectives")
	TArray<TObjectPtr<UObjectiveBase>> Objectives;

	//Interval between update context event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator")
	float UpdateContextInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator")
	float ReevaluateObjectivesInterval;
	UPROPERTY(BlueprintReadOnly, Category= "Objectives Generator")
	bool bIsInit = false;
	
private:
	FTimerHandle UpdateContextTimerHandle;
	FTimerHandle ReevaluateObjectivesTimerHandle;

	
public:
	/*************************************************************************************************************
	 * Context Related:
	 */
	/*
	 * Reference Category
	 */
	//Instigator reference of APawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Context|Reference")
	TObjectPtr<APawn> OwnerPawn;

	//Player reference of ACharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Context|Reference")
	TObjectPtr<ACharacter> PlayerCharacter;


	/*
	 * Distance Category
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Context|Distance")
	float PlayerDistance = 0.f;

public:
	/****************************************************************************************************************
	 * API:
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Objective Generator")
	void InitGenerator();
	void InitGenerator_Implementation();

	//Construct objectives and call initialization function for each
	//TODO: Not finished objective construction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Objective Generator")
	void InitObjectives();
	void InitObjectives_Implementation();

	//Function used to call update Context
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Objective Generator")
	void UpdateContext();
	void UpdateContext_Implementation();

	//Function used to call UpdateObjectiveDelegate, which will then broadcast to ReevaluateObjective function
	UFUNCTION(BlueprintCallable)
	void CallObjectivesUpdateDelegate();

	//Function used to call up context-update timer, interval can be set by changing"UpdateContextInterval"
	UFUNCTION(BlueprintCallable)
	void StartContextUpdateTimer();

	//Function used to call up context-update timer, interval can be set by changing"UpdateContextInterval"
	//Component need to be initialized first
	UFUNCTION(BlueprintCallable)
	void StartObjectiveReevaluateTimer();
};
