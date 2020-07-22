// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();
    // ask for player pawn and stores in a pointer.
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (AIBehavior)
    {
        // runs the behavior tree specified on Aicontroller blueprint
        RunBehaviorTree(AIBehavior);
        
        // create a verctor key for blackboard
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }


}

void AShooterAIController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    // seting and de setting player location, setting last Known location
    if(LineOfSightTo(PlayerPawn))
    {
        // Sett Player Location :
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        
        // Set LastKnownLocation:
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }

    else
    {
       
        
        // GetBlackboardComponent()->ClearValue(TEXT("LastKnownPlayerLocation"));
        
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
    
    
}
