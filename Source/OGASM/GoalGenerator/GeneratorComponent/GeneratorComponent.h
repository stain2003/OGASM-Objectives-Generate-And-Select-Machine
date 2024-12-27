// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"
#include "GeneratorComponent.generated.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives")
	TArray<TSubclassOf<UObjectiveBase>> ObjectiveTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Objectives")
	TArray<TObjectPtr<UObjectiveBase>> Objectives;
};
