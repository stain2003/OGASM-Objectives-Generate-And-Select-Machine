// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorComponent.h"

#include "../../../../Plugins/UnrealImGui-master/Source/ThirdParty/ImGuiLibrary/Include/imgui.h"
#include "Kismet/GameplayStatics.h"




#define CHECK_GENERATOR_INITIALIZED(bIsInit) \
if (!bIsInit) { \
UE_LOG(LogTemp, Error, TEXT("[Error] Calling function: %s failed: Generator is not initialized!"), TEXT(__FUNCTION__)); \
return; \
}

#define CHECK_GENERATOR_INITIALIZED_WITH_WARNING(bIsInit) \
if (!bIsInit) { \
UE_LOG(LogTemp, Warning, TEXT("[Warning] %s: Generator is not initialized, initialize it first!"), TEXT(__FUNCTION__)); \
}



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

	/*ImGui::Begin("Generator");
	for (auto obj : Objectives)
	{
		FString name = this->GetName();
		ImGui::Text("%s", TCHAR_TO_UTF8(*name));
	}
	ImGui::End();*/
}

void UObjectiveGeneratorComponent::InitGenerator_Implementation()
{
	bIsInit = true;
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	OwnerPawn = Cast<APawn>(GetOwner());
}

void UObjectiveGeneratorComponent::InitObjectives_Implementation()
{
	CHECK_GENERATOR_INITIALIZED(bIsInit)
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
	CHECK_GENERATOR_INITIALIZED(bIsInit)
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(this))
		{
			World->GetTimerManager().SetTimer(UpdateContextTimerHandle, this, &UObjectiveGeneratorComponent::UpdateContext, UpdateContextInterval, true);
		}
	}
}

void UObjectiveGeneratorComponent::StartObjectiveReevaluateTimer()
{
	CHECK_GENERATOR_INITIALIZED_WITH_WARNING(bIsInit)
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
}

void UObjectiveGeneratorComponent::CallObjectivesUpdateDelegate() const
{
	ObjectiveReevaluateDelegate.Broadcast();
}