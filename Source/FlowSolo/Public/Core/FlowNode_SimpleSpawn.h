
#pragma once

#include "GameplayTagContainer.h"

#include "Nodes/FlowNode.h"

#include "Components/SpawnComponent.h"
#include "FlowNode_SimpleSpawn.generated.h"

USTRUCT()
struct FSimpleSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorClass;

	// min spawn range around the spawner in cm
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinRange;

	// max spawn range around the spawner in cm
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaxRange;

	UPROPERTY(EditAnywhere, Category = "Spawn AI")
	bool bNoCollisionFail;

	FSimpleSpawnParams()
		: MinRange(0)
		, MaxRange(0)
		, bNoCollisionFail(true)
	{
	}
};

/**
 * Spawn by Gameplay Tag
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Simple Spawn"))
class FLOWSOLO_API UFlowNode_SimpleSpawn : public UFlowNode
{
	GENERATED_BODY()

	UFlowNode_SimpleSpawn(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "SpawnPoint")
	FGameplayTagContainer IdentityTags;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (ShowOnlyInnerProperties, FlowDataPin = "Input"))
	FSimpleSpawnParams SpawnParams;

protected:
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;

	virtual void CachePinProperties() override;

#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
	virtual EDataValidationResult ValidateNode() override;
#endif
};
