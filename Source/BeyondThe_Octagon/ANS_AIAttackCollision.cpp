// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AIAttackCollision.h"
#include "FreeflowCombatBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FreeflowCombatData.h"



void UANS_AIAttackCollision::NotifyBegin(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference)
{

    Super::NotifyBegin(MeshComponent, Animation, TotalDuration, EventReference);

    //Saving to a variable, so the value resets to what we set in the ANS
    AttackOnceTrigger = doAttackOnce;
}

void UANS_AIAttackCollision::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
   Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime, EventReference);

   if(AttackOnceTrigger)
   {
        //If Attack should be done only once, use the private variable that gets reset at Begin Notify to check
        DoCollisionCheck(MeshComponent);
        AttackOnceTrigger = false;
   }
   else if(!doAttackOnce)
   {
        //If Attack can be triggered multiple times, then use the exposed variable since the private gets set to false when it is true
        //It will continue to run the multiple hit logic after attacking once.
        DoCollisionCheck(MeshComponent);
   }

}

void UANS_AIAttackCollision::DoCollisionCheck(USkeletalMeshComponent *MeshComponent)
{

    //Creating HitResult Variable
    FHitResult HitResult;

    //Values for SphereTraceSingle
    const FVector InSocket = MeshComponent->GetSocketLocation(startSocket);
    const FVector OutSocket = MeshComponent->GetSocketLocation(endSocket);

    //Converting TraceType to TraceQuery
    const ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);

    //Creating a variable for Actors Array
    TArray<AActor*> ActorsToIgnore;

    //Adding Actors to the Array
    ActorsToIgnore.Add(MeshComponent->GetOwner());

    //Variable for Trace Debug
    EDrawDebugTrace::Type DoTrace;

    //Set Debug Type based on Debug bool exposed to AnimNotifyState
    if(debug)
    {
        DoTrace = EDrawDebugTrace::ForDuration;
    }
    else
    {
        DoTrace = EDrawDebugTrace::None;
    }

    bool bHit = UKismetSystemLibrary::SphereTraceSingle(MeshComponent->GetWorld(), InSocket, OutSocket, radius, TraceChannel, true, ActorsToIgnore, DoTrace, HitResult, true);

    const AActor* HitActor = HitResult.GetActor();

    if(bHit)
    {
        if(HitActor && HitResult.GetActor()->GetComponentByClass(UFreeflowCombatBase::StaticClass()))
        {

            

            //Print HitActor Name - Debugging
            FString HitActorName = HitActor->GetName();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Hit Actor %s"), *HitActorName));

            UFreeflowCombatBase* FFCS = Cast<UFreeflowCombatBase>(HitActor->GetComponentByClass(UFreeflowCombatBase::StaticClass()));

            if(!(FFCS->GetTag() == HitCollisionExclusionTag) || !(FFCS->GetTag() == FinisherTag))
            {

            
                EAttackHitDirection HitDirection = FFCS->HitDirection(MeshComponent->GetOwner());
                if(HitDirection != EAttackHitDirection::None)
                {
                    FFCS->PlayHitMontage(HitDirection);
                }
                else
                {
                    FFCS->PlayHitMontage(EAttackHitDirection::forward);
                }
            }
        }
    }


}
