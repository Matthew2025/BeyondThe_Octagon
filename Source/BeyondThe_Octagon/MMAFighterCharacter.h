// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DamageSystem/DamageableInterface.h"
#include "DamageSystem/DamageSystemComponent.h" 
#include "DamageSystem/DamageSystemTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "MMAFighterCharacter.generated.h" // Has to be last include

class UDamageSystemComponent;

class UCapsuleComponent;

UCLASS() 
class BEYONDTHE_OCTAGON_API AMMAFighterCharacter : public ACharacter, public IDamageableInterface

{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;







public:
	// Sets default values for this character's properties
	AMMAFighterCharacter(); // Define all things the character is or has

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Set things to happen when the game begins i.e "Hello Message"

	

	// Default Player Mapping
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* PlayerMappingContext;


	//Input Action Move
	UPROPERTY(EditAnywhere,Category = "Input")
	class UInputAction* MoveAction;

	//Input Action Jump with spacebar
	UPROPERTY(EditAnywhere,Category = "Input")
	class UInputAction* JumpAction;

	//Input Action Look with mouse
	UPROPERTY(EditAnywhere,Category = "Input")
	class UInputAction* LookAction;

	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageTaken(const FDamageInfo& DamageInfo);

	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamageAvoided(const FDamageInfo& DamageInfo);

	UFUNCTION(BlueprintNativeEvent)
	void RespondToDeath();









public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Called every single frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Character learns to listen to you i.e WASD for movement
	virtual float getMaxHealth_Implementation() override;
	virtual float getCurrentHealth_Implementation() override;
	virtual bool getIsDead_Implementation() override;
	virtual bool TakeDamage_Implementation(const FDamageInfo& DamageInfo);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDamageSystemComponent> DamageSystemComponent;
	

protected:
	// Function to move in all directions
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	void Jump();



};
