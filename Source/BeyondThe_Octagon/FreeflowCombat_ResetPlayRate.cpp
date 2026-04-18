// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeflowCombat_ResetPlayRate.h"

UFreeflowCombat_ResetPlayRate::UFreeflowCombat_ResetPlayRate()
{
    minPlayRate = 0.2f;
    Debug = false;
}

void UFreeflowCombat_ResetPlayRate::NotifyBegin(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float TotalDuration, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyBegin(MeshComponent, Animation, TotalDuration, EventReference);

    minPlayRate = FMath::Max(minPlayRate, lowestPlayRate);

    if(MeshComponent && Animation)
    {
        //Store Actor Location in Distance Covered
        StartPlayerLocation = MeshComponent->GetOwner()->GetActorLocation();

    }

}

void UFreeflowCombat_ResetPlayRate::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime, EventReference);

    if(MeshComponent && Animation)
    {
        //Calculate Distance at every frame
        float Distance = FVector::Dist(StartPlayerLocation, MeshComponent->GetOwner()->GetActorLocation());
        float playRate = FMath::GetMappedRangeValueClamped(FVector2D(minDistance, maxDistance), FVector2D(minPlayRate, maxPlayRate), Distance);

        if(Distance >= minDistance && Distance <= maxDistance)
        {

            Animation->RateScale = playRate;

        }

        if(Debug == true)
        {

            if(GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::SanitizeFloat(Distance), true);
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(playRate), true);
                    

            }
        }
      

    }
}

void UFreeflowCombat_ResetPlayRate::NotifyEnd(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
     Super::NotifyEnd(MeshComponent, Animation, EventReference);

     if(MeshComponent && Animation)
     {
        Animation->RateScale = maxPlayRate;
     }



}
