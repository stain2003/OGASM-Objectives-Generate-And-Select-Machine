// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"
#include "GeneratorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObjectiveReevaluateDelegate);

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

protected:

	//Delegate to bind Objectives' update function to, broadcast by ReevaluateObjectivesTimerHandle
	FObjectiveReevaluateDelegate ObjectiveReevaluateDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator|Objectives")
	TArray<TSubclassOf<UObjectiveBase>> ObjectiveTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator|Objectives")
	TArray<TObjectPtr<UObjectiveBase>> Objectives;

	//Interval between update context event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator")
	float UpdateContextInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives Generator")
	float ReevaluateObjectivesInterval;
	
private:
	FTimerHandle UpdateContextTimerHandle;
	FTimerHandle ReevaluateObjectivesTimerHandle;
public:
	/************************************************API************************************************/
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
	void CallObjectivesUpdateDelegate() const;

	/*************************************************Context Related************************************************/
	//Instigator reference of APawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Context")
	TObjectPtr<APawn> OwnerPawn;

	//Player reference of ACharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Context")
	TObjectPtr<ACharacter> PlayerCharacter;
};
