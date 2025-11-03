// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "Core/FlowNode_Math.h"
#include "FlowAsset.h"
#include "FlowNodeMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_Math)

UFlowNode_ArithmeticOperator::UFlowNode_ArithmeticOperator()
{
#if WITH_EDITOR
	Category = TEXT("Math|Arithmetic");
#endif
	InputPins.Empty();
	OutputPins.Empty();
	AllowedSignalModes = { EFlowSignalMode::Enabled, EFlowSignalMode::Disabled };
}
UFlowNode_ComparisonOperator::UFlowNode_ComparisonOperator()
{
#if WITH_EDITOR
	Category = TEXT("Math|Comparison");
#endif
	InputPins.Empty();
	OutputPins.Empty();
	AllowedSignalModes = { EFlowSignalMode::Enabled, EFlowSignalMode::Disabled };
}
UFlowNode_LogicalOperator::UFlowNode_LogicalOperator()
{
#if WITH_EDITOR
	Category = TEXT("Math|Logic");
#endif
	InputPins.Empty();
	OutputPins.Empty();
	AllowedSignalModes = { EFlowSignalMode::Enabled, EFlowSignalMode::Disabled };
}


UFlowNode_ArithmeticOperatorFloat::UFlowNode_ArithmeticOperatorFloat()
	: A(0.0f), B(0.0f), Out(0.0f)
{
}
UFlowNode_ArithmeticOperatorInt::UFlowNode_ArithmeticOperatorInt()
	: A(0), B(0), Out(0)
{
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
}
UFlowNode_ComparisonOperatorInt::UFlowNode_ComparisonOperatorInt()
	: A(0), B(0), Out(false)
{
}


UFlowNode_LogicalOperator_Binary::UFlowNode_LogicalOperator_Binary() : A(false), B(false), Out(false)
{
}
UFlowNode_Not::UFlowNode_Not() : A(false), Out(true)
{
}


void UFlowNode_ArithmeticOperator::ExecuteInput(const FName& PinName)
{
	TriggerFirstOutput(true);
}
void UFlowNode_ComparisonOperator::ExecuteInput(const FName& PinName)
{
	TriggerFirstOutput(true);
}
void UFlowNode_LogicalOperator::ExecuteInput(const FName& PinName)
{
	TriggerFirstOutput(true);
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


bool UFlowNode_ArithmeticOperatorFloat::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	// 1. Check if the pin being requested is our "Out" pin.
	// 2. When this is called, the Flow framework has already populated A and B
	//    by evaluating their input connections (if any).
	// 3. We just call the virtual PerformOp to get the result.

	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_ArithmeticOperatorFloat, Out))
	{
		Out = PerformOp(A, B);

		// Set the output pointers for the Flow framework
		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}

	return false;
}

bool UFlowNode_ArithmeticOperatorInt::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_ArithmeticOperatorInt, Out))
	{
		Out = PerformOp(A, B);

		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}

	return false;
}

bool UFlowNode_ComparisonOperatorFloat::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_ComparisonOperatorFloat, Out))
	{
		Out = PerformOp(A, B);

		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}
	return false;
}

bool UFlowNode_ComparisonOperatorInt::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_ComparisonOperatorInt, Out))
	{
		Out = PerformOp(A, B);

		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}
	return false;
}

bool UFlowNode_LogicalOperator_Binary::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_LogicalOperator_Binary, Out))
	{
		Out = PerformOp(A, B);

		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}
	return false;
}

bool UFlowNode_Not::EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr)
{
	if (OutputPinName == GET_MEMBER_NAME_CHECKED(UFlowNode_Not, Out))
	{
		Out = !A;

		OutProperty = GetOutputProperty(OutputPinName);
		OutDataPtr = OutProperty->ContainerPtrToValuePtr<void>(this);
		return true;
	}
	return false;
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
