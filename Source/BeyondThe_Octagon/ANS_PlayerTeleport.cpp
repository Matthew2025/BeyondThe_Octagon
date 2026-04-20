// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_PlayerTeleport.h"
#include "FreeflowCombatBase.h"
#include "Kismet/KismetMathLibrary.h"


void UANS_PlayerTeleport::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime, EventReference);

    //Check if Owner is Valid for the animation
    if(MeshComponent->GetOwner())
    {
        //Get Freeflow Combat Component 
        UFreeflowCombatBase* FFCC = Cast<UFreeflowCombatBase>(MeshComponent->GetOwner()->GetComponentByClass(UFreeflowCombatBase::StaticClass()));
        //Check if FreeflowCombatComponent is valid
        if(FFCC)
        {
            //Get Enemy to Counter -> Enemy that is attacking
            if(FFCC->GetCounterEnemy())
            {
                //Get Location to where the enemy to counter is and then teleport to the location
                FVector startLocation = MeshComponent->GetOwner()->GetActorLocation();
                FVector endLocation = FFCC->GetCounterEnemy()->GetActorLocation();
                FVector direction = (startLocation - endLocation).GetSafeNormal();
                FVector teleportLocation = endLocation + (direction * offSet);
                FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(startLocation, endLocation);
                FVector interpreteLocation = FMath::VInterpTo(startLocation, teleportLocation, FrameDeltaTime, interpreteSpeed);
                FFCC->GetCounterEnemy()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(endLocation, startLocation));
                MeshComponent->GetOwner()->SetActorLocationAndRotation(interpreteLocation, lookAtRotation);



            }
        }
    }
}

void UANS_PlayerTeleport::NotifyEnd(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{

    Super::NotifyEnd(MeshComponent, Animation, EventReference);

    //Get Owner and make sure it is valid
    if(MeshComponent->GetOwner())
    {
        //Get FreeflowCombatComponent
        UFreeflowCombatBase* FFCC = Cast<UFreeflowCombatBase>(MeshComponent->GetOwner()->GetComponentByClass(UFreeflowCombatBase::StaticClass()));
        if(FFCC)
        {
            //Play Counter Montage on attacking enemy
            FFCC->PlayCounterMontage();
        }
    }
}
