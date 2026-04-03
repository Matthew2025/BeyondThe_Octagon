// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.generated.h"

UENUM(BlueprintType)
//Different Damage Types
enum class EDamageType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical UMETA(DisplayName = "Physical"),
	Environmental UMETA(DisplayName = "Environmental"),

};

UENUM(BlueprintType)
//Respond to Damage
enum class EDamageResponse : uint8
{

	None UMETA(DisplayName = "None"),
	HitReaction UMETA(DisplayName = "Hit Reaction"),
	Knockback UMETA(DisplayName = "Knockback"),
	Stagger UMETA(DisplayName = "Stagger"),
	Stun UMETA(DisplayName = "Stun"),

};


USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Damage Amount
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Person Dealing the Damage
	AActor* DamageCauser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Can the attack be countered
	bool CanBeCountered = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Can the attack be blocked
	bool CanBeBlocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Can the attack hurt invincible character
	bool ShouldDamageInvincible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Is the attack uninterruptable
	bool ShouldForceInterrupt = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType = EDamageType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageResponse DamageResponse = EDamageResponse::None;






};


