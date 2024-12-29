﻿// Fill out your copyright notice in the Description page of Project Settings.


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
}

void UObjectiveGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObjectiveGeneratorComponent::InitGenerator_Implementation()
{
	bIsInit = true;
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	OwnerPawn = Cast<APawn>(GetOwner());
}

void UObjectiveGeneratorComponent::InitObjectives_Implementation()
{
	for (auto cls : ObjectiveTypes)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: Constructing Objectives"), *GetOwner()->GetName())
		if (cls != nullptr && cls->IsChildOf(UObjectiveBase::StaticClass()))
		{
			UObjectiveBase* Objective = NewObject<UObjectiveBase>(GetTransientPackage(), cls);
			Objective->InitObjective(this);
			Objectives.Add(Objective);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid objective class, check if is null or not child of UObjectiveBase"))
		}
	}
}

void UObjectiveGeneratorComponent::StartContextUpdateTimer()
{
	if (GEngine && bIsInit)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(this))
		{
			World->GetTimerManager().SetTimer(UpdateContextTimerHandle, this, &UObjectiveGeneratorComponent::UpdateContext, UpdateContextInterval, true);
		}
	}
}

void UObjectiveGeneratorComponent::StartObjectiveReevaluateTimer()
{
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(this))
		{
			World->GetTimerManager().SetTimer(ReevaluateObjectivesTimerHandle, this, &UObjectiveGeneratorComponent::CallObjectivesUpdateDelegate, ReevaluateObjectivesInterval, true);
		}
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