// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FreeflowCombatData.generated.h"

UENUM(BlueprintType)
enum class EAttackHitDirection : uint8
{
	None UMETA(DisplayName = "None"),
	forward UMETA(DisplayName = "Forward"),
	backward UMETA(DisplayName = "Backward"),
	left UMETA(DisplayName = "Left"),
	right UMETA(DisplayName = "Right")

};

UENUM(BlueprintType)
enum class EAIStates: uint8
{
	GetInRange,
	GetBack,
	Wait,
	LookForWeapons,
	Strafe,
	Attack

};

USTRUCT(BlueprintType)
struct FPlayerAttackAnimationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float offSet;

	FPlayerAttackAnimationData()
	{
		playRate = 1.0f;
		offSet = 100.0f;
	}
};

/**
 * 
 */
// UCLASS()
// class BEYONDTHE_OCTAGON_API UFreeflowCombatData : public UObject
// {
// 	GENERATED_BODY()
	
// };
