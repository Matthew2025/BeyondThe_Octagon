// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystemTypes.h"
#include "DamageSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageAvoided, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEYONDTHE_OCTAGON_API UDamageSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxHealth = 100;
	



//private - only visible inside the class
private:
	UPROPERTY()
	float currentHealth = maxHealth;

	UPROPERTY()
	bool isDead = false;

	UPROPERTY()
	bool isBlocking = false;

	UPROPERTY()
	bool isCountering = false;

	UPROPERTY()
	bool isInvincible = false;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// const - the reference variable can't be modified, so it's an input
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool HandleIncomingDamage(const FDamageInfo& DamageInfo);
	

	//Getter Functions
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float getCurrentHealth()
	{
		return currentHealth;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float getMaxHealth() const
	{
		return maxHealth;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool getIsDead() const
	{
		return isDead;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "States")
	bool getIsInvincible() const
	{
		return isInvincible;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "States")
	bool getIsBlocking() const
	{
		return isBlocking;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "States")
	bool getIsCountering() const
	{
		return isCountering;
	}

	//Setter Functions
	UFUNCTION(BlueprintCallable, Category = "States")
	void setIsBlocking(const bool block) 
	{
		isBlocking = block;
	}

	UFUNCTION(BlueprintCallable, Category = "States")
	void setIsInvincible(bool invincible) 
	{
		isInvincible = invincible;
	}

	UFUNCTION(BlueprintCallable, Category = "States")
	void setIsCountering(const bool counter) 
	{
		isCountering = counter;
	}

	UFUNCTION(BlueprintCallable, Category = "Health")
	void setStartingHealth(float startingHealth);

	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageAvoided OnDamageAvoided;

	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDeath OnDeath;




		
};
