// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorComponent.h"

#include "../../../../Plugins/UnrealImGui-master/Source/ThirdParty/ImGuiLibrary/Include/imgui.h"
#include "Kismet/GameplayStatics.h"


UObjectiveGeneratorComponent::UObjectiveGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	//Default update context interval: 0.3s;
	UpdateContextInterval = 0.3f;
	//Default reevaluate objectives interval: 0.5s;
	ReevaluateObjectivesInterval = 0.5f;
}

void UObjectiveGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(this))
		{
			InitObjectives();
			World->GetTimerManager().SetTimer(UpdateContextTimerHandle, this, &UObjectiveGeneratorComponent::UpdateContext, UpdateContextInterval, true);
			World->GetTimerManager().SetTimer(ReevaluateObjectivesTimerHandle, this, &UObjectiveGeneratorComponent::CallObjectivesUpdateDelegate, ReevaluateObjectivesInterval, true);
		}
	}
}

void UObjectiveGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObjectiveGeneratorComponent::InitGenerator_Implementation()
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	OwnerPawn = Cast<APawn>(GetOwner());
}

void UObjectiveGeneratorComponent::InitObjectives_Implementation()
{
	for (auto Objective : Objectives)
	{
		ObjectiveReevaluateDelegate.AddDynamic(Objective, &UObjectiveBase::ReevaluateObjective);
	}
	
	if (ObjectiveReevaluateDelegate.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectiveReevaluateDelegate is bounded!!!!"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectiveReevaluateDelegate is not bounded!!!!"))
	}
	
}

void UObjectiveGeneratorComponent::UpdateContext_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Updating context!!!!"))
}

void UObjectiveGeneratorComponent::CallObjectivesUpdateDelegate() const
{
	ObjectiveReevaluateDelegate.Broadcast();
}

