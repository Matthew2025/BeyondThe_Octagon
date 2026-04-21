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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Counter")
	void PlayCounterMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Counter")
	void ComboCounter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attack")
	FPlayerAttackAnimationData GetAttackAnimations();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attack")
	void SetAttackAnimations(const FPlayerAttackAnimationData& NewAttackAnimation);


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combo")
	void ResetComboCounter();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = true))
	FPlayerAttackAnimationData AttackAnimations;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	int Combo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tumer Handle")
	FTimerHandle ComboCounterTimerHandle;










// protected:
// 	// Called when the game starts
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
