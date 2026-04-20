// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_AIAttackCollision.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UANS_AIAttackCollision : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;


	//
	UFUNCTION()
	void DoCollisionCheck(USkeletalMeshComponent* MeshComponent);


public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings");
	bool doAttackOnce;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings");
	float radius;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings");
	FName startSocket;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Settings");
	FName endSocket;


private:
	UPROPERTY()
	bool AttackOnceTrigger = false;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	bool debug = false;
	
};
