// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* CurrentOwner = OwnerComp.GetAIOwner();
    if (!CurrentOwner)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* Character = Cast<AShooterCharacter>(CurrentOwner->GetPawn());

    if (!Character)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot();

    return EBTNodeResult::Succeeded;
}
