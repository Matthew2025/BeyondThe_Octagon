// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageSystemComponent.h"

// Sets default values for this component's properties
UDamageSystemComponent::UDamageSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UDamageSystemComponent::HandleIncomingDamage(const FDamageInfo& DamageInfo)
{

	//Failed to take damage because you are dead
    if(isDead)
	{
		return false;

	}

	//Character is Invincible and the attack shouldn't damage them, don't take damage
	//The character is countering and the attack is counterable, don't take damage
	//The character is blocking and the attack is blockable, don't take damage

	if((isInvincible && !DamageInfo.ShouldDamageInvincible) || (isCountering && DamageInfo.CanBeCountered) || (isBlocking && DamageInfo.CanBeBlocked))
	{
		OnDamageAvoided.Broadcast(DamageInfo);
		return false;
	}

	//Subtract damage amount from current health

	currentHealth = FMath::Clamp(currentHealth - DamageInfo.DamageAmount, 0.0f, maxHealth);
	OnDamageTaken.Broadcast(DamageInfo);

	if(currentHealth <= 0)
	{
		isDead = true;
		OnDeath.Broadcast();
	}
	return true;
}

void UDamageSystemComponent::setStartingHealth(float startingHealth)
{
	maxHealth = startingHealth;
	currentHealth = startingHealth;
}
