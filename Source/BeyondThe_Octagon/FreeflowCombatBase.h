// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "FreeflowCombatData.h"
#include "FreeflowCombatBase.generated.h"



//Blueprintable - a blueprint class can be a child of this component
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEYONDTHE_OCTAGON_API UFreeflowCombatBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFreeflowCombatBase();

	//Blueprint Implementable Event - Don't need to define in C++ but defined in Blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAttackHitDirection HitDirection(AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayHitMontage(EAttackHitDirection HitDirection);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentEnemy(AActor* EnemyReference);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCounterEnemy(AActor* EnemyReference);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	AActor* GetCounterEnemy();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	AActor* GetCurrentEnemy();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTag(const FGameplayTag& GameplayTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	FGameplayTag GetTag();






// protected:
// 	// Called when the game starts
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
