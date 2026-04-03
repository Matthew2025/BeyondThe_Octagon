// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableCharacterBase.h"
#include "DamageSystemComponent.h"


// Sets default values
ADamageableCharacterBase::ADamageableCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSystemComponent = CreateDefaultSubobject<UDamageSystemComponent>(TEXT("Damage System Component"));

}

// Called when the game starts or when spawned
void ADamageableCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(DamageSystemComponent)
	{
		//Function called when on damage taken is dispatched
		DamageSystemComponent->OnDamageTaken.AddDynamic(this, &ADamageableCharacterBase::RespondToDamageTaken);
		DamageSystemComponent->OnDamageAvoided.AddDynamic(this, &ADamageableCharacterBase::RespondToDamageAvoided);
		DamageSystemComponent->OnDeath.AddDynamic(this, &ADamageableCharacterBase::RespondToDeath);

	}
	
}

void ADamageableCharacterBase::RespondToDamageTaken_Implementation(const FDamageInfo& DamageInfo)
{

}

void ADamageableCharacterBase::RespondToDamageAvoided_Implementation(const FDamageInfo& DamageInfo)
{

}


void ADamageableCharacterBase::RespondToDeath_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

// Called every frame
void ADamageableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADamageableCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ADamageableCharacterBase::getMaxHealth_Implementation()
{
	//Return the Max Health from damage system component
	if(DamageSystemComponent)
	{
		return DamageSystemComponent->getMaxHealth();

	}
	else
	{
		return 0.0f;

	}
}

float ADamageableCharacterBase::getCurrentHealth_Implementation()
{
	if(DamageSystemComponent)
	{
		return DamageSystemComponent->getCurrentHealth();

	}
	else
	{
		return 0.0f;

	}
}

bool ADamageableCharacterBase::getIsDead_Implementation()
{
	if(DamageSystemComponent)
	{
		return DamageSystemComponent->getIsDead();

	}
	else
	{
		return false;
	}
	
    
}

bool ADamageableCharacterBase::TakeDamage_Implementation(const FDamageInfo& DamageInfo)
{
	if(DamageSystemComponent)
	{
		return DamageSystemComponent->HandleIncomingDamage(DamageInfo);

	}
	else
	{
		return false;
	}
    
}
