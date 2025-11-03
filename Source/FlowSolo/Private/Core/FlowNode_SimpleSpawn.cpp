// Copyright https://github.com/MothCocoon/FlowSolo/graphs/contributors

#include "Core/FlowNode_SimpleSpawn.h"
#include "FlowNodeMacros.h"
#include "FlowSubsystem.h"

UFlowNode_SimpleSpawn::UFlowNode_SimpleSpawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Actor");
#endif

	InputPins = { TEXT("Spawn") };
	OutputPins = { TEXT("Spawned") };
}

void UFlowNode_SimpleSpawn::ExecuteInput(const FName& PinName)
{
	if (IdentityTags.IsValid())
	{
		if (PinName == TEXT("Spawn"))
		{
			int32 SpawnCount = 0;
			for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::Any))
			{
				FVector SpawnLocation = FoundComponent->GetOwner()->GetActorLocation();
				{
					FVector RandomDirection = FMath::VRand();
					RandomDirection.Z = 0.0f; // XY plane only
					RandomDirection.Normalize();
					float RandomDistance = FMath::FRandRange(SpawnParams.MinRange, SpawnParams.MaxRange);
					SpawnLocation += (RandomDirection * RandomDistance);
				}

				AActor* SpawnedActor = GetWorld()->SpawnActor(SpawnParams.ActorClass, &SpawnLocation);
				//if (SpawnedActor)
				//{
				//	SpawnedActor->SetActorScale3D(SpawnedActor->GetActorScale3D() * SpawnParams.ActorScale);
				//}

				SpawnCount++;
			}

			if (SpawnCount > 0)
			{
				TriggerOutput(TEXT("Spawned"), true);
				return;
			}
		}
	}
	else
	{
		LogError(MissingIdentityTag);
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawn failed!"));
	TriggerFirstOutput(true);
}

void UFlowNode_SimpleSpawn::Cleanup()
{
}

void UFlowNode_SimpleSpawn::CachePinProperties()
{
	Super::CachePinProperties();

	DECLARE_INPUT_PIN(SpawnParams);
}

#if WITH_EDITOR
FString UFlowNode_SimpleSpawn::GetNodeDescription() const
{
	const FString ClassString = SpawnParams.ActorClass ? SpawnParams.ActorClass->GetFName().ToString() : TEXT("Missing Actor Class!");
	return GetIdentityTagsDescription(IdentityTags) + LINE_TERMINATOR + ClassString;
}

EDataValidationResult UFlowNode_SimpleSpawn::ValidateNode()
{
	if (IdentityTags.IsEmpty() || SpawnParams.ActorClass == nullptr)
	{
		if (IdentityTags.IsEmpty())
		{
			ValidationLog.Error<UFlowNode>(*UFlowNode::MissingIdentityTag, this);
		}
		if (SpawnParams.ActorClass == nullptr)
		{
			ValidationLog.Error<UFlowNode>(TEXT("Actor Class is missing or invalid"), this);
		}

		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif
