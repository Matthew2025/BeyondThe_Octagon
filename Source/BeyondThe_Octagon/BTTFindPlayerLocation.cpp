// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTFindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyController.h"
#include "EnemyKeys.h"
#include "Kismet/GameplayStatics.h" // Allow us to grab player reference


UBTTFindPlayerLocation::UBTTFindPlayerLocation(FObjectInitializer const &ObjectInit)
{
    //Create a Node with this task, will be labeled find player location
    NodeName = TEXT("Find Player Location");


}

EBTNodeResult::Type UBTTFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent &TreeComponent, uint8 *NodeMemory)
{
    // Get AI Controller
    auto const AIController = Cast<AEnemyController>(TreeComponent.GetAIOwner());

    //Get Navigation System
    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    //Get Player Reference
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    APawn* Player = PlayerController->GetPawn();

    if(NavigationSystem)
    {
        //Set Blackboard value to be player location
        AIController->getBlackboard()->SetValueAsVector(EnemyKeys::targetLocation, Player->GetActorLocation());

    }

    //Finish Execution
    FinishLatentTask(TreeComponent, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;


}
