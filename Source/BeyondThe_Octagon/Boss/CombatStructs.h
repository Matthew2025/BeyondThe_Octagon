
#pragma once

#include "CoreMinimal.h"
#include "CombatStructs.generated.h"

USTRUCT(BlueprintType)
struct FAttack
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* AttackMontage;


};