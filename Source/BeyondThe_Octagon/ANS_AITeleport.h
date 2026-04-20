// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_AITeleport.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UANS_AITeleport : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	virtual void NotifyTick(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float offset = 50.0f; //Offset from player while attacking enemy

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float InterpretSpeed = 5.0f;

	
};
