// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "FreeflowCombat_ANS_SlowDownRate.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UFreeflowCombat_ANS_SlowDownRate : public UAnimNotifyState
{
	GENERATED_BODY()

	UFreeflowCombat_ANS_SlowDownRate();



public:

	//Used for debugginf distance and playRate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug;

	// Max Range of Distance the animation will slow down for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float maxDistance;

	// Minimum Range of Distance the animation will slow down for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float minDistance;

	// Max PlayRate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float maxPlayRate;

	//Minimum Play Rate - Don't go below 0.2 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float minPlayRate;

	//




public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


private:
	UPROPERTY()
	float lowestPlayRate = 0.2f;

	UPROPERTY()
	FVector StartPlayerLocation;

	
};
