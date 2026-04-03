// Fill out your copyright notice in the Description page of Project Settings.


#include "MMAFighterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "DamageSystem/DamageableCharacterBase.h"
#include "DamageSystem/DamageSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMMAFighterCharacter::AMMAFighterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Spring Arm Components provide functionality to your camera so that it can expand 
	//or retract based on gameplay situations.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;


	// Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(("Camera"));
	Camera->SetupAttachment(SpringArm);
	

	bUseControllerRotationYaw = false; //Character doesn't turn with camera
	//True - Camera moves with character
	//False - Camera doesn't move with character
	bUseControllerRotationPitch = false;
	//Character moves with camera - true
	//Character doesn't move with camera - false
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	DamageSystemComponent = CreateDefaultSubobject<UDamageSystemComponent>(TEXT("Damage System Component"));



}

// Called when the game starts or when spawned
void AMMAFighterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) // Is the controller a player controller(Human Input)
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		//UEnhancedInputLocalPlayerSubsystem - in charge of handling input context for the enhanced input
		//PlayerController->GetLocalPlayer() - object tide to this controller
		//ULocalPlayer::GetSubsystem - fetches the enhanced input subsystem for that player (if exist store in subsystem)
		{
			Subsystem->AddMappingContext(PlayerMappingContext,0);

		}

	}

	if(DamageSystemComponent)
	{
		//Function called when on damage taken is dispatched
		DamageSystemComponent->OnDamageTaken.AddDynamic(this, &AMMAFighterCharacter::RespondToDamageTaken);
		DamageSystemComponent->OnDamageAvoided.AddDynamic(this, &AMMAFighterCharacter::RespondToDamageAvoided);
		DamageSystemComponent->OnDeath.AddDynamic(this, &AMMAFighterCharacter::RespondToDeath);

	}

	
}

void AMMAFighterCharacter::RespondToDamageTaken_Implementation(const FDamageInfo &DamageInfo)
{

}

void AMMAFighterCharacter::RespondToDamageAvoided_Implementation(const FDamageInfo &DamageInfo)
{

}

void AMMAFighterCharacter::RespondToDeath_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Move); // When Move Action triggered call the move action inside Move()
		// ETriggerEvent - continue firing while player is pressing the key
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMMAFighterCharacter::Jump);
	}

}

float AMMAFighterCharacter::getMaxHealth_Implementation()
{
    if(DamageSystemComponent)
	{
		return DamageSystemComponent->getMaxHealth();

	}
	else
	{
		return 0.0f;

	}
}

float AMMAFighterCharacter::getCurrentHealth_Implementation()
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

bool AMMAFighterCharacter::getIsDead_Implementation()
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

bool AMMAFighterCharacter::TakeDamage_Implementation(const FDamageInfo &DamageInfo)
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

void AMMAFighterCharacter::Move_Implementation(const FInputActionValue& Value)
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
