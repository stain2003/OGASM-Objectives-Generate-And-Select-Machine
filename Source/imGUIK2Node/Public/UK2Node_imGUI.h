// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "OGASM/GoalGenerator/Objectives/ObjectiveBase.h"
#include "UK2Node_imGUI.generated.h"

/**
 * 
 */
USTRUCT()
struct FTemplateStructure
{
	GENERATED_BODY()
	bool BBoolean;
	float FFloat;
};
UCLASS()
class IMGUIK2NODE_API UUK2Node_imGUI : public UK2Node
{
	GENERATED_BODY()

public:
	//~ Begin UEdGraphNode Interface._
	virtual void AllocateDefaultPins() override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PostReconstructNode() override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	//~ End UEdGraphNode Interface._

	//~ Begin UK2Node Interface_
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	virtual void PreloadRequiredAssets() override;
	void SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const;
	//~ End UK2Node Interface_

	//Custom function
	UEdGraphPin* GetTemplatePin() const;

	UFUNCTION(BlueprintCallable)
	static void ShowIMGUIDemoWindow(TArray<UObjectiveBase*> Objective);
};
