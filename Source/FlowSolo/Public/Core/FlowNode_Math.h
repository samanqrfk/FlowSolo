// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_Math.generated.h"

/**
 * base class for all arithmetic operators.
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ArithmeticOperator : public UFlowNode
{
	GENERATED_BODY()

public:
	UFlowNode_ArithmeticOperator();

	virtual void ExecuteInput(const FName& PinName) override;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ArithmeticOperatorFloat : public UFlowNode_ArithmeticOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ArithmeticOperatorFloat();

	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

protected:
	virtual float PerformOp(const float InA, const float InB) const PURE_VIRTUAL(UFlowNode_ArithmeticOperatorFloat::PerformOp, return 0.0f; );

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	float Out;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ArithmeticOperatorInt : public UFlowNode_ArithmeticOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ArithmeticOperatorInt();

	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

protected:
	virtual int32 PerformOp(const int32 InA, const int32 InB) const PURE_VIRTUAL(UFlowNode_ArithmeticOperatorInt::PerformOp, return 0; );

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
	virtual float PerformOp(const float InA, const float InB) const override { return InA + InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float - float"))
class FLOWSOLO_API UFlowNode_SubFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual float PerformOp(const float InA, const float InB) const override { return InA - InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float * float"))
class FLOWSOLO_API UFlowNode_MulFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual float PerformOp(const float InA, const float InB) const override { return InA * InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float / float"))
class FLOWSOLO_API UFlowNode_DivFloat : public UFlowNode_ArithmeticOperatorFloat
{
	GENERATED_BODY()
public:
	UFlowNode_DivFloat();
protected:
	virtual float PerformOp(const float InA, const float InB) const override
	{
		return (InB != 0.0f) ? (InA / InB) : 0.0f;
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
	virtual int32 PerformOp(const int32 InA, const int32 InB) const override { return InA + InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 - int32"))
class FLOWSOLO_API UFlowNode_SubInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()
protected:
	virtual int32 PerformOp(const int32 InA, const int32 InB) const override { return InA - InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 * int32"))
class FLOWSOLO_API UFlowNode_MulInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()
protected:
	virtual int32 PerformOp(const int32 InA, const int32 InB) const override { return InA * InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 / int32"))
class FLOWSOLO_API UFlowNode_DivInt : public UFlowNode_ArithmeticOperatorInt
{
	GENERATED_BODY()
public:
	UFlowNode_DivInt();
protected:
	virtual int32 PerformOp(const int32 InA, const int32 InB) const override
	{
		return (InB != 0) ? (InA / InB) : 0;
	}
};



/**
 * base class for all comparison operators.
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ComparisonOperator : public UFlowNode
{
	GENERATED_BODY()

public:
	UFlowNode_ComparisonOperator();

	virtual void ExecuteInput(const FName& PinName) override;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ComparisonOperatorFloat : public UFlowNode_ComparisonOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ComparisonOperatorFloat();

	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

protected:
	virtual bool PerformOp(const float InA, const float InB) const PURE_VIRTUAL(UFlowNode_ComparisonOperatorFloat::PerformComp, return false; );

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float A;

	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	float B;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};

UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_ComparisonOperatorInt : public UFlowNode_ComparisonOperator
{
	GENERATED_BODY()

public:
	UFlowNode_ComparisonOperatorInt();
	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const PURE_VIRTUAL(UFlowNode_ComparisonOperatorInt::PerformComp, return false; );

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
	virtual bool PerformOp(const float InA, const float InB) const override { return (InA < InB); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float > float"))
class FLOWSOLO_API UFlowNode_GTFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const float InA, const float InB) const override { return (InA > InB); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float <= float"))
class FLOWSOLO_API UFlowNode_LEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const float InA, const float InB) const override { return (InA <= InB); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float >= float"))
class FLOWSOLO_API UFlowNode_GEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const float InA, const float InB) const override { return (InA >= InB); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float == float"))
class FLOWSOLO_API UFlowNode_EQFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const float InA, const float InB) const override { return FMath::IsNearlyEqual(InA, InB); }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "float != float"))
class FLOWSOLO_API UFlowNode_NEFloat : public UFlowNode_ComparisonOperatorFloat
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const float InA, const float InB) const override { return !FMath::IsNearlyEqual(InA, InB); }
};



//------------------------------------------------------------------------------
// INT COMPARISONS
//------------------------------------------------------------------------------

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 < int32"))
class FLOWSOLO_API UFlowNode_LTInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA < InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 > int32"))
class FLOWSOLO_API UFlowNode_GTInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA > InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 <= int32"))
class FLOWSOLO_API UFlowNode_LEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA <= InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 >= int32"))
class FLOWSOLO_API UFlowNode_GEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA >= InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 == int32"))
class FLOWSOLO_API UFlowNode_EQInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA == InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "int32 != int32"))
class FLOWSOLO_API UFlowNode_NEInt : public UFlowNode_ComparisonOperatorInt
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(const int32 InA, const int32 InB) const override { return InA != InB; }
};



/**
 * base class for all logical operators.
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_LogicalOperator : public UFlowNode
{
	GENERATED_BODY()

public:
	UFlowNode_LogicalOperator();

	virtual void ExecuteInput(const FName& PinName) override;
};

//------------------------------------------------------------------------------
// BOOL LOGIC
//------------------------------------------------------------------------------

/**
 * Abstract base for 2-input logical operators (AND, OR, XOR).
 */
UCLASS(NotBlueprintable, Abstract)
class FLOWSOLO_API UFlowNode_LogicalOperator_Binary : public UFlowNode_LogicalOperator
{
	GENERATED_BODY()

public:
	UFlowNode_LogicalOperator_Binary();

	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

protected:
	virtual bool PerformOp(bool InA, bool InB) const PURE_VIRTUAL(UFlowNode_LogicalOperator_Binary::PerformOp, return false; );

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
	virtual bool PerformOp(bool InA, bool InB) const override { return InA && InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool OR"))
class FLOWSOLO_API UFlowNode_Or : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(bool InA, bool InB) const override { return InA || InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool XOR"))
class FLOWSOLO_API UFlowNode_Xor : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(bool InA, bool InB) const override { return InA != InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "bool XNOR"))
class FLOWSOLO_API UFlowNode_EQBool : public UFlowNode_LogicalOperator_Binary
{
	GENERATED_BODY()
protected:
	virtual bool PerformOp(bool InA, bool InB) const override { return InA == InB; }
};

UCLASS(NotBlueprintable, meta = (DisplayName = "NOT"))
class FLOWSOLO_API UFlowNode_Not : public UFlowNode_LogicalOperator
{
	GENERATED_BODY()

public:
	UFlowNode_Not();

	virtual void CachePinProperties() override;
	virtual bool EvaluateAndGetOutputValue(const FName OutputPinName, FProperty*& OutProperty, const void*& OutDataPtr) override;

public:
	UPROPERTY(EditAnywhere, SaveGame, meta = (FlowDataPin = "Input"))
	bool A;

	UPROPERTY(SaveGame, meta = (FlowDataPin = "Output"))
	bool Out;
};



UCLASS(NotBlueprintable, meta = (DisplayName = "If"))
class FLOWSOLO_API UFlowNode_If : public UFlowNode_LogicalOperator
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