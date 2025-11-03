// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_DoN.generated.h"

/**
 * Repeat Loop Body N times.
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "DoN"))
class FLOWSOLO_API UFlowNode_DoN final : public UFlowNode
{
	GENERATED_BODY()

	UFlowNode_DoN(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "DoN", meta = (ClampMin = 2, FlowDataPin = "Input"))
	int32 N;

	UPROPERTY(SaveGame)
	bool bBreak;

protected:
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;

	virtual void CachePinProperties() override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FString GetStatusString() const override;
#endif
};
