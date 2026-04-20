// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AITeleport.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


void UANS_AITeleport::NotifyTick(USkeletalMeshComponent *MeshComponent, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyTick(MeshComponent, Animation, FrameDeltaTime, EventReference);


    if(MeshComponent->GetOwner())
    {
    
        //C++ Equivalent of Get Owner -> Get Blackbaord
        const UBlackboardComponent* BlackboardComponent = UAIBlueprintHelperLibrary::GetBlackboard(MeshComponent->GetOwner());

        if(BlackboardComponent)
        {

        //Get Blackboard Key Literal Name
        const FName KeyName = FName("TargetActor");
        

        UObject* Value = BlackboardComponent->GetValueAsObject(KeyName);

            if(Value)
            {   //Cast to Character using the Value from the blackboard function GetValueAsObject
                ACharacter* Player = Cast<ACharacter>(Value);

                if(Player)
                {
                    FVector startLocation = MeshComponent->GetOwner()->GetActorLocation();
                    FVector playerLocation = Player->GetActorLocation();


                    FVector Direction = (startLocation - playerLocation).GetSafeNormal();
                    FVector teleportLocation = playerLocation + (Direction * offset);

                    FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(startLocation, playerLocation);


                    FVector interpreteLocation = FMath::VInterpTo(startLocation, teleportLocation, FrameDeltaTime, InterpretSpeed);
                    MeshComponent->GetOwner()->SetActorLocationAndRotation(interpreteLocation, lookAtRotation);




                }

            }

        }



    }

}
