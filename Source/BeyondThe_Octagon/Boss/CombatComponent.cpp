// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::Attack(FName attackName)
{

	//Check if map has elements
	if(attackMap.Num() == 0)
	{
		return;
	}

	//Get Owner of component and then get their animator
	UAnimInstance* AnimInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();

	//Return early if the anim instance wasn't found
	if(!AnimInstance)
	{
		return;
	}

	//Get Attack from the map
	FAttack* Attack = attackMap.Find(attackName);

	//Return Early if attack not found
	if(!Attack)
	{
		return;
	}

	//Get the attack montage from attack
	UAnimMontage* AttackMontage = Attack->AttackMontage;

	//Play Attack if Valid
	if(AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
	}

}

void UCombatComponent::StopAttack(float BlendOutTime, FName attackName)
{
	//Check if map has elements
	if(attackMap.Num() == 0)
	{
		return;
	}

	//Get Owner of components and then get their animator
	UAnimInstance* AnimInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();

	//Return early of the anim instance wasn't found
	if(!AnimInstance)
	{
		return;
	}

	//Get the attack from the map
	FAttack* Attack = attackMap.Find(attackName);

	//Return early if attack not found
	if(Attack)
	{
		return;
	}

	//Get the attack montage from attack
	UAnimMontage* AttackMontage = Attack->AttackMontage;

	//Play the attack is valid
	if(AttackMontage)
	{
		AnimInstance->Montage_Stop(BlendOutTime, AttackMontage);
	}
}

bool UCombatComponent::isAttacking()
{

	//Check if map has elements
	if(attackMap.Num() == 0)
	{
		return false;
	}

	//Get owner of component and then get their animator
	UAnimInstance* AnimInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();

	//Return early if the anim instance wasn't found
	if(!AnimInstance)
	{
		return false;
	}

	//Get map keys
	TArray<FName> Keys;

	//Check all attacks to see if any of them are currently playing 
	for(int i = 0; i < Keys.Num(); i++)
	{
		//Return when you find an attack playing
		if(AnimInstance->Montage_IsPlaying(attackMap.Find(Keys[i])->AttackMontage))
		{
			return false;
		}
	}
    return false;
}
