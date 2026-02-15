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

public:
	// Sets default values for this character's properties
	AMMAFighterCharacter(); // Define all things the character is or has

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // Set things to happen when the game begins i.e "Hello Message"

	// Default Player Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")

	class UInputMappingContext* PlayerMappingContext;

	// Function to move in all directions
	void Move(const FInputActionValue& Value);

	//Input Action Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; // Called every single frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Character learns to listen to you i.e WASD for movement

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraSet, meta = (AllowPrivateAccess = "true")) //In Unreal we can access the camera boom
	class USpringArmComponent* CameraBoom; //Forward Declaration

public:

	FORCEINLINE USpringArmComponent* GetCameraBoom() const //get access to Camera Boom without changing the propeties of class
	{
		//Forceinline forces the complier to replace the function call with the function body
		//Remove Function Call Overhead
		//If I don't use it correctly I can create code bloat

		return CameraBoom;

	}



};
