// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeflowCombat_ANS_SlowDownRate.h"

UFreeflowCombat_ANS_SlowDownRate::UFreeflowCombat_ANS_SlowDownRate()
{
    minPlayRate = 0.2f;
    Debug = false;
}

void UFreeflowCombat_ANS_SlowDownRate::NotifyBegin(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyBegin(MeshComponent, Animation, TotalDuration, EventReference);

    minPlayRate = FMath::Max(minPlayRate, lowestPlayRate);
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, FString::SanitizeFloat(minPlayRate), true);

    }

    if(MeshComponent && Animation)
    {
        //Store Actor Location in Distance Covered
        StartPlayerLocation = MeshComponent->GetOwner()->GetActorLocation();

    }

}

void UFreeflowCombat_ANS_SlowDownRate::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{

    Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime, EventReference);

    if(MeshComponent && Animation)
    {
        //Calculate Distance at every frame
        float Distance = FVector::Dist(StartPlayerLocation, MeshComponent->GetOwner()->GetActorLocation());
        float playRate = FMath::GetMappedRangeValueClamped(FVector2D(minDistance, maxDistance), FVector2D(maxPlayRate, minPlayRate), Distance);

         if(Distance >= minDistance && Distance <= maxDistance)
        {

            Animation->RateScale = playRate;

        }
        if(Debug == true)
        {


        
            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, FString::SanitizeFloat(Distance), true);
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat(playRate), true);
                    

            }
        }
    

   
    }

}

void UFreeflowCombat_ANS_SlowDownRate::NotifyEnd(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{

    Super::NotifyEnd(MeshComponent, Animation, EventReference);

    if(MeshComponent && Animation)
    {
         Animation->RateScale = maxPlayRate;

    }


}
