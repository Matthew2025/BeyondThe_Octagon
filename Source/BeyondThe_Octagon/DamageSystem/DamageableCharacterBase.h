// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageableInterface.h"
#include "DamageSystemComponent.h" 
#include "DamageSystemTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DamageableCharacterBase.generated.h"


class UDamageSystemComponent;

class UCapsuleComponent;

UCLASS()
class BEYONDTHE_OCTAGON_API ADamageableCharacterBase : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADamageableCharacterBase();

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAttackHitDirection hitDirection(AActor* damageInstigator);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void setAttackPlayer(bool AttackPlayer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool getAttackPlayer();




	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageTaken(const FDamageInfo& DamageInfo);
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageAvoided(const FDamageInfo& DamageInfo);
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDeath();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual & override - override funtion from parent or interface class

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Damageable Interface Implementations
	virtual float getMaxHealth_Implementation() override;
	virtual float getCurrentHealth_Implementation() override;
	virtual bool getIsDead_Implementation() override;
	virtual bool TakeDamage_Implementation(const FDamageInfo& DamageInfo) override;

	//Damage System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDamageSystemComponent> DamageSystemComponent;



};
