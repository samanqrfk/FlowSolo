// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_Math.generated.h"

/**
 * base class for all arithmetic operators.
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_MathOperator : public UFlowNode
{
	GENERATED_BODY()

public:
	UFlowNode_MathOperator();

	virtual bool PerformPureCalculation_Implementation() override { PerformOp(); return true; }
	virtual bool IsPureNode_Implementation() const override { return true; }
	virtual void ExecuteInput(const FName& PinName) override;

protected:
	virtual void PerformOp() PURE_VIRTUAL(UFlowNode_ArithmeticOperatorFloat::PerformOp);
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ArithmeticOperatorFloat : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ArithmeticOperatorFloat();

	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	float Out;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ArithmeticOperatorInt : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ArithmeticOperatorInt();

	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	int32 A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	int32 B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	int32 Out;
};



//------------------------------------------------------------------------------
// FLOAT ARITHMETIC
//------------------------------------------------------------------------------

UCLASS(NotBlueprintable, meta = (DisplayName = "float + float"))
class FLOWSOLO_API UFlowNode_AddFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A + B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float - float"))
class FLOWSOLO_API UFlowNode_SubFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A - B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float * float"))
class FLOWSOLO_API UFlowNode_MulFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A * B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float / float"))
class FLOWSOLO_API UFlowNode_DivFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()
public:
	UFlowNode_DivFloat();

protected:
	virtual void PerformOp() override
	{
		Out = (B != 0.0f) ? (A / B) : 0.0f;
	}
};



//------------------------------------------------------------------------------
// INT32 ARITHMETIC
//------------------------------------------------------------------------------

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 + int32"))
class FLOWSOLO_API UFlowNode_AddInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A + B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 - int32"))
class FLOWSOLO_API UFlowNode_SubInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A - B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 * int32"))
class FLOWSOLO_API UFlowNode_MulInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A * B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 / int32"))
class FLOWSOLO_API UFlowNode_DivInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()

public:
	UFlowNode_DivInt();

protected:
	virtual void PerformOp() override
	{
		Out = (B != 0) ? (A / B) : 0;
	}
};



UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ComparisonOperatorFloat : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ComparisonOperatorFloat();

	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ComparisonOperatorInt : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ComparisonOperatorInt();
	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	int32 A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	int32 B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};



//------------------------------------------------------------------------------
// FLOAT COMPARISONS
//------------------------------------------------------------------------------

UCLASS(NotBlueprintable, meta = (DisplayName = "float < float"))
class FLOWSOLO_API UFlowNode_LTFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = (A < B); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float > float"))
class FLOWSOLO_API UFlowNode_GTFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = (A > B); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float <= float"))
class FLOWSOLO_API UFlowNode_LEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = (A <= B); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float >= float"))
class FLOWSOLO_API UFlowNode_GEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = (A >= B); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float == float"))
class FLOWSOLO_API UFlowNode_EQFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = FMath::IsNearlyEqual(A, B); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float != float"))
class FLOWSOLO_API UFlowNode_NEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = !FMath::IsNearlyEqual(A, B); }
};



//------------------------------------------------------------------------------
// INT COMPARISONS
//------------------------------------------------------------------------------

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 < int32"))
class FLOWSOLO_API UFlowNode_LTInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A < B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 > int32"))
class FLOWSOLO_API UFlowNode_GTInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A > B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 <= int32"))
class FLOWSOLO_API UFlowNode_LEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A <= B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 >= int32"))
class FLOWSOLO_API UFlowNode_GEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A >= B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 == int32"))
class FLOWSOLO_API UFlowNode_EQInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A == B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 != int32"))
class FLOWSOLO_API UFlowNode_NEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A != B; }
};


//------------------------------------------------------------------------------
// BOOL LOGIC
//------------------------------------------------------------------------------

/**
 * Abstract base for 2-input logical operators (AND, OR, XOR).
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_LogicalOperator_Binary : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_LogicalOperator_Binary();

	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	bool A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	bool B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};



UCLASS(NotBlueprintable, meta = (DisplayName = "bool AND"))
class FLOWSOLO_API UFlowNode_And : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A && B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool OR"))
class FLOWSOLO_API UFlowNode_Or : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A || B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool XOR"))
class FLOWSOLO_API UFlowNode_Xor : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A != B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool XNOR"))
class FLOWSOLO_API UFlowNode_EQBool : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()

protected:
	virtual void PerformOp() override { Out = A == B; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "NOT"))
class FLOWSOLO_API UFlowNode_Not : public UFlowNode_MathOperator
{
	GENERATED_BODY()

public:
	UFlowNode_Not();

	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	bool A;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};



UCLASS(NotBlueprintable, meta = (DisplayName = "If"))
class FLOWSOLO_API UFlowNode_If : public UFlowNode
{
	GENERATED_BODY()

public:
	UFlowNode_If();

	virtual void ExecuteInput(const FName& PinName) override;
	virtual void CachePinProperties() override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	bool Condition;
};