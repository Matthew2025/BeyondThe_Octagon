// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MMAFighterCharacter.generated.h" // Has to be last include


UCLASS() 
class BEYONDTHE_OCTAGON_API AMMAFighterCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta =(AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta =(AllowPrivateAccess = "true"))
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

	UPROPERTY(EditAnywhere,Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,Category = "Input")
	class UInputAction* LookAction;









public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Called every single frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Character learns to listen to you i.e WASD for movement

protected:
	// Function to move in all directions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();


};
