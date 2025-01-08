// Fill out your copyright notice in the Description page of Project Settings.


#include "UK2Node_imGUI.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "GraphEditorSettings.h"
#include "K2Node_CallFunction.h"
#include "imgui.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"

#define LOCTEXT_NAMESPACE "UK2Node_IMGUI"

namespace PinName
{
	const FName TemplateInput = "TemplateInputNodeName";
	static const FName APinName = "Objective Array";
	static const FName BPinName = "B";
	static const FName CPinName = "C";
	static const FName DPinName = "D";
}

void UUK2Node_imGUI::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	
	UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);
		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

bool UUK2Node_imGUI::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin,
	FString& OutReason) const
{
	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

void UUK2Node_imGUI::PreloadRequiredAssets()
{
	Super::PreloadRequiredAssets();
}

void UUK2Node_imGUI::SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const
{
	MutatablePin.PinToolTip = UEdGraphSchema_K2::TypeToText(MutatablePin.PinType).ToString();

	UEdGraphSchema_K2 const* const K2Schema = Cast<const UEdGraphSchema_K2>(GetSchema());
	if (K2Schema != nullptr)
	{
		MutatablePin.PinToolTip += TEXT(" ");
		MutatablePin.PinToolTip += K2Schema->GetPinDisplayName(&MutatablePin).ToString();
	}

	MutatablePin.PinToolTip += FString(TEXT("\n")) + PinDescription.ToString();
}

UEdGraphPin* UUK2Node_imGUI::GetTemplatePin() const
{
	UEdGraphPin* Pin = FindPinChecked(PinName::TemplateInput);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}

void UUK2Node_imGUI::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	Super::PinDefaultValueChanged(Pin);
}

void UUK2Node_imGUI::PostReconstructNode()
{
	Super::PostReconstructNode();
}

FSlateIcon UUK2Node_imGUI::GetIconAndTint(FLinearColor& OutColor) const
{
	static FSlateIcon Icon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
	return Icon;
}

FLinearColor UUK2Node_imGUI::GetNodeTitleColor() const
{
	return GetDefault<UGraphEditorSettings>()->DelegatePinTypeColor;
}

void UUK2Node_imGUI::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
}

void UUK2Node_imGUI::AllocateDefaultPins()
{
	// 创建一个输入引脚,输入类型为 UEdGraphSchema_K2::PC_Exec (就是蓝图节点左上角的小三角形), 引脚名称为  UEdGraphSchema_K2::PN_Execute
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	// 创建一个输入引脚,输入类型为 UEdGraphSchema_K2::PC_Exec (就是蓝图节点右上角的小三角形), 引脚名称为  UEdGraphSchema_K2::PN_Then
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	
	/*UEdGraphPin* InputPinA = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, PinName::APinName);
	UEdGraphPin* OutputPinB = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Float, PinName::BPinName);

	SetPinToolTip(*InputPinA, LOCTEXT("InputPin.PinA_Wildcard", "input pin wildcard!"));*/

	FEdGraphPinType PinTypeA;
	PinTypeA.PinCategory = UEdGraphSchema_K2::PC_Object;
	PinTypeA.PinSubCategoryObject = UObjectiveBase::StaticClass();
	PinTypeA.ContainerType = EPinContainerType::Array;
	
	UEdGraphPin* InputPinA = CreatePin(EGPD_Input, PinTypeA, PinName::APinName);

	
	Super::AllocateDefaultPins();
}

void UUK2Node_imGUI::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	
	UK2Node_CallFunction* ShowIMGUIFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	ShowIMGUIFunction->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UUK2Node_imGUI, ShowIMGUIDemoWindow), StaticClass());
	ShowIMGUIFunction->AllocateDefaultPins();

	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *ShowIMGUIFunction->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *ShowIMGUIFunction->GetThenPin());

	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PinName::APinName), *ShowIMGUIFunction->FindPinChecked(TEXT("Objective")));
	
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ShowIMGUIFunction, this);
	
	BreakAllNodeLinks();
}

void UUK2Node_imGUI::ShowIMGUIDemoWindow(TArray<UObjectiveBase*> Objective)
{
	for (auto obj : Objective)
	{
		if (obj != nullptr)
		{
			ImGui::Begin("UUK2Node_imGUI");
			ImGui::Text("%s", TCHAR_TO_UTF8(*obj->GetName()));
			ImGui::End();
		}
	}
}

#undef LOCTEXT_NAMESPACE