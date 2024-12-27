// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"
#include "GeneratorComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OGASM_API UGoalGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGoalGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objective Info")
	TArray<TSubclassOf<UObjectiveBase>> ObjectiveTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objective Info")
	TArray<TObjectPtr<UObjectiveBase>> Objectives;
};
