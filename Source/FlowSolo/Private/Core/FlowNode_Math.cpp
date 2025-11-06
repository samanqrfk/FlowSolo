// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "Core/FlowNode_Math.h"
#include "FlowAsset.h"
#include "FlowNodeMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_Math)

UFlowNode_MathOperator::UFlowNode_MathOperator()
{
#if WITH_EDITOR
	Category = TEXT("Math");
#endif
	InputPins.Empty();
	OutputPins.Empty();
	AllowedSignalModes = { EFlowSignalMode::Enabled, EFlowSignalMode::Disabled };
}


UFlowNode_ArithmeticOperatorFloat::UFlowNode_ArithmeticOperatorFloat()
	: A(0.0f), B(0.0f), Out(0.0f)
{
#if WITH_EDITOR
	Category += TEXT("|Arithmetic");
#endif
}
UFlowNode_ArithmeticOperatorInt::UFlowNode_ArithmeticOperatorInt()
	: A(0), B(0), Out(0)
{
#if WITH_EDITOR
	Category += TEXT("|Arithmetic");
#endif
}


UFlowNode_DivFloat::UFlowNode_DivFloat()
{
	B = 1.0f;
}
UFlowNode_DivInt::UFlowNode_DivInt()
{
	B = 1;
}


UFlowNode_ComparisonOperatorFloat::UFlowNode_ComparisonOperatorFloat()
	: A(0.0f), B(0.0f), Out(false)
{
#if WITH_EDITOR
	Category += TEXT("|Comparison");
#endif
}
UFlowNode_ComparisonOperatorInt::UFlowNode_ComparisonOperatorInt()
	: A(0), B(0), Out(false)
{
#if WITH_EDITOR
	Category += TEXT("|Comparison");
#endif
}


UFlowNode_LogicalOperator_Binary::UFlowNode_LogicalOperator_Binary() : A(false), B(false), Out(false)
{
#if WITH_EDITOR
	Category += TEXT("|Logic");
#endif
}
UFlowNode_Not::UFlowNode_Not() : A(false), Out(true)
{
#if WITH_EDITOR
	Category += TEXT("|Logic");
#endif
}

void UFlowNode_ArithmeticOperatorFloat::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_INPUT_PIN(B);
	DECLARE_OUTPUT_PIN(Out);
}
void UFlowNode_ArithmeticOperatorInt::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_INPUT_PIN(B);
	DECLARE_OUTPUT_PIN(Out);
}
void UFlowNode_ComparisonOperatorFloat::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_INPUT_PIN(B);
	DECLARE_OUTPUT_PIN(Out);
}
void UFlowNode_ComparisonOperatorInt::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_INPUT_PIN(B);
	DECLARE_OUTPUT_PIN(Out);
}
void UFlowNode_LogicalOperator_Binary::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_INPUT_PIN(B);
	DECLARE_OUTPUT_PIN(Out);
}
void UFlowNode_Not::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(A);
	DECLARE_OUTPUT_PIN(Out);
}

UFlowNode_If::UFlowNode_If() : Condition(false)
{
#if WITH_EDITOR
	Category = TEXT("Route|Logic");
	NodeDisplayStyle = FlowNodeStyle::Logic;
#endif
	InputPins.Empty();
	InputPins.Add(FFlowPin(TEXT("Execute")));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("True")));
	OutputPins.Add(FFlowPin(TEXT("False")));

	AllowedSignalModes = { EFlowSignalMode::Enabled, EFlowSignalMode::Disabled };
}

void UFlowNode_If::ExecuteInput(const FName& PinName)
{
	if (PinName == TEXT("Execute"))
	{
		if (Condition)
		{
			TriggerOutput(TEXT("True"), true);
		}
		else
		{
			TriggerOutput(TEXT("False"), true);
		}
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Unknown pin!"))
}

void UFlowNode_If::CachePinProperties()
{
	Super::CachePinProperties();
	DECLARE_INPUT_PIN(Condition);
}
