// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(FObjectInitializer const& ObjectInit);

	//Override Functions
	void BeginPlay() override;
	void OnPossess(APawn* Pawn) override;

	// Get Black Board
	class UBlackboardComponent* getBlackboard() const;

	//Tree Components
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

private:
	class UBlackboardComponent* BlackboardComponent;
	
};
