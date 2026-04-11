// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTFindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UBTTFindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTFindPlayerLocation(FObjectInitializer const& ObjectInit);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& TreeComponent, uint8* NodeMemory);




	
};
