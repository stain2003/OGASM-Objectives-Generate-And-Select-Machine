// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorComponent.h"

#include "../../../../Plugins/UnrealImGui-master/Source/ThirdParty/ImGuiLibrary/Include/imgui.h"


UObjectiveGeneratorComponent::UObjectiveGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UObjectiveGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UObjectiveGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ImGui::ShowDemoWindow();
}

