// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FreeflowCombatData.h"
#include "EnemyComponentBase.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEYONDTHE_OCTAGON_API UEnemyComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyComponentBase();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAttackHitDirection HitDirection(AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAttackPlayer(bool AttackPlayer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	bool GetAttackPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetPlayerDead(const bool ActorDead);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	bool GetPlayerDead();



private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = true))
	bool Dead;





// protected:
// 	// Called when the game starts
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
