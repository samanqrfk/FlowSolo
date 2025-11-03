// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "Core/FlowNode_DoN.h"
#include "FlowNodeMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_DoN)

UFlowNode_DoN::UFlowNode_DoN(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, N(2)
	, bBreak(false)
{
#if WITH_EDITOR
	Category = TEXT("Route");
	NodeDisplayStyle = FlowNodeStyle::Condition;
#endif

	InputPins.Empty();
	InputPins.Add(FFlowPin(TEXT("Execute")));
	InputPins.Add(FFlowPin(TEXT("Break")));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("LoopBody")));
	OutputPins.Add(FFlowPin(TEXT("Completed")));
}

void UFlowNode_DoN::ExecuteInput(const FName& PinName)
{
	if (PinName == TEXT("Execute"))
	{
		bBreak = false;
		for (int32 i = 0; i < N; ++i)
		{
			if (bBreak) break;
			TriggerOutput(TEXT("LoopBody"));
		}
		TriggerOutput(TEXT("Completed"), true);
		return;
	}
	if (PinName == TEXT("Break"))
	{
		bBreak = true;
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("ExecuteInput: Unknown pin!"));
}

void UFlowNode_DoN::Cleanup()
{
	Super::Cleanup();
}

void UFlowNode_DoN::CachePinProperties()
{
	Super::CachePinProperties();

	DECLARE_INPUT_PIN(N);
}

#if WITH_EDITOR
FString UFlowNode_DoN::GetNodeDescription() const
{
	return FString::FromInt(N);
}

FString UFlowNode_DoN::GetStatusString() const
{
	return TEXT("");
}
#endif
