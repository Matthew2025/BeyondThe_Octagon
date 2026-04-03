// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimationsInstance.generated.h"

class AMMAFighterCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UPlayerAnimationsInstance : public UAnimInstance
{
	GENERATED_BODY()

	//Begin Play of Animation Blueprint, get reference to character that holds the animation
	//We get the reference so that we read the character speed, jumping state, or aiming
	// and send the infromation to animation graph

	//Runs once when animation begins and where we prepare referernces and prevent crashes later
	// when animation tries to access data from the character
	virtual void NativeInitializeAnimation() override; 

	// Make function available in Blueprints so we can call it visually
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	private:
		UPROPERTY(Transient,VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		//Transient - this value only leaves at runtime. Unreal won't save it into assets or levels
		//Created when game starts and use it while the game is running

		// Character Using the animation
		TObjectPtr<AMMAFighterCharacter> MMAFighter = nullptr;
		//nullptr - Safe future proof way to point to U objects
		//Same syntax of a normal pointer but with more protection


		// UProperty - we are going to use the reflection system and garbage collection
		//Transient - we are not going to save on disk but on runtime.
		//Not automatically visible in the editor or blueprints because we didn't add the other parameters

		//Movement Component of Character using the animation
		UPROPERTY(Transient)
		TObjectPtr<UCharacterMovementComponent> MoveComp = nullptr;

		//Says if the character is in the air because is jumping or falling
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		bool bIsInAir = false;

		//It's indicating that the character is changing the speed
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		bool bIsAccelerating = false;

		//Indicating that the character is moving (speed different to zero)
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		bool bisMoving = false;

		//Movement Speed of Character
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, meta = (AllowPrivateAccess = "true"))
		float speed = 0.0f;

	
};
