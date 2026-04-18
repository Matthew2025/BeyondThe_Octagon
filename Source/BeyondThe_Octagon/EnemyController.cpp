// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

AEnemyController::AEnemyController(FObjectInitializer const &ObjectInit)
{
    //Reference to Behavior Tree Class
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> treeFinder(TEXT("/Script/AIModule.BehaviorTree'/Game/Games/Characters/MainCharacter/Prototype/AI/Behavior/BT_EnemyBT.BT_EnemyBT'"));
    
    //Getting the Behavior Tree directly from reference
    if(treeFinder.Succeeded())
    {
        BehaviorTree = treeFinder.Object;
    }

    //Initialize Behavior Tree and Blackboard Components
    BehaviorTreeComponent = ObjectInit.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Behavior Tree Component"));
    Blackboard = ObjectInit.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void AEnemyController::BeginPlay()
{
    Super::BeginPlay();

    // Run BehaviorTree
    RunBehaviorTree(BehaviorTree);
    BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AEnemyController::OnPossess(APawn *Pawn)
{
    //Run Default Possess Method
    Super::OnPossess(Pawn);

    //Initialize Blackboard
    if(Blackboard)
    {
        Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
        Blackboard->SetValueAsObject(TEXT("SelfActor"), Pawn);
    }
}

UBlackboardComponent *AEnemyController::getBlackboard() const
{
    return Blackboard;
}
