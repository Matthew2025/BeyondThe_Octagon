// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyController.h"
#include "EnemyKeys.h"
#include "Kismet/GameplayStatics.h" 

UBTTChasePlayer::UBTTChasePlayer(FObjectInitializer const &ObjectInit)
{
    NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTChasePlayer::ExecuteTask(UBehaviorTreeComponent &TreeComponent, uint8 *NodeMemory)
{
    // Get AI Controller
    auto const AIController = Cast<AEnemyController>(TreeComponent.GetAIOwner());

    //Get Navigation System
    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    if(NavigationSystem)
    {
        //Get Location of Player
        FVector Location = AIController->getBlackboard()->GetValueAsVector(EnemyKeys::targetLocation);


        //Move AI towards player
        AIController->MoveToLocation(Location, 300.0f);

    }

    //Finish Execution
    FinishLatentTask(TreeComponent, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}
