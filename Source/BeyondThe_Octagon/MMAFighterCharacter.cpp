// Fill out your copyright notice in the Description page of Project Settings.


#include "MMAFighterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMMAFighterCharacter::AMMAFighterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;



	Camera = CreateDefaultSubobject<UCameraComponent>(("Camera"));
	Camera->SetupAttachment(SpringArm);
	

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	



}

// Called when the game starts or when spawned
void AMMAFighterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) // Is the controller a player controller(Human Input)
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext,0);

		}

	}
	
}




// Called every frame
void AMMAFighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMMAFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Jump);
	}

}


void AMMAFighterCharacter::Move(const FInputActionValue& Value)
{

	if (Controller != nullptr) // Check if controller is not null
	{
		// Controller gives camera orientation

		//Get a 2D vector (x = Forward/backward, y = right/left)
		FVector2D MovementVector = Value.Get<FVector2D>();


		//Get Forward and Right Direction
		const FRotator Rotation = Controller->GetControlRotation(); //Full Camera Rotation
		const FRotator YawRotation(0,Rotation.Yaw, 0); //Only Care about Horizontal Rotation

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Adding Movement Forward or Right
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);





	}



}

void AMMAFighterCharacter::Look(const FInputActionValue& Value)
{
	if(Controller != nullptr)
	{

	FVector2D InputVector = Value.Get<FVector2D>();
	AddControllerYawInput(InputVector.X); //Look Left and Right
	AddControllerPitchInput(InputVector.Y); //Look Up and Down

	}

}

void AMMAFighterCharacter::Jump()
{
	ACharacter::Jump();

}

