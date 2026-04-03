// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimationsInstance.h"
#include "MMAFighterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimationsInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    //Check to see if we have a player pawn
    if(APawn* PlayerPawn = TryGetPawnOwner())
    {
        //If we have the player we cast it to a MMAFighterCharacter
        MMAFighter = Cast<AMMAFighterCharacter>(PlayerPawn);
        //if we have the MMAFighter then we have a movement component and assign 
        //component to movementcomp
        MoveComp = MMAFighter ? MMAFighter->GetCharacterMovement() : nullptr;

    }
}

void UPlayerAnimationsInstance::UpdateAnimationProperties(float DeltaTime)
{
    APawn* OwnerNow = TryGetPawnOwner();

    //Changing Characters and not get stuck 
    if(OwnerNow != MMAFighter || IsValid(MoveComp))
    {
        MMAFighter = Cast<AMMAFighterCharacter>(OwnerNow);
        MoveComp = MMAFighter ? MMAFighter->GetCharacterMovement() : nullptr;

    }
    // If one of these parameters is not set then we return
    if(!MMAFighter || !MoveComp)
    {
        return;
    }



    const FVector Velocity = MMAFighter->GetVelocity();
    speed = Velocity.Size2D(); // I don't need the component on Z to get the speed

    //Is in the air?
    bIsInAir = MoveComp->IsFalling();

    //Is the player actively providing movement input?
    //Is the player pressing some key?

    //Velocity - how fast the player is moving
    //Acceleration - is the player pressing some key

    bIsAccelerating = MoveComp->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER;
}
