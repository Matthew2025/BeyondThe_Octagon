// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_PlayerTeleport.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UANS_PlayerTeleport : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float offSet = 50.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float interpreteSpeed = 5.0f;




	
};
