// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    
    // find if the palyer controller is dead:
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
       EndGame(false);
    }

    for ( AShooterAIController* Controller :  TActorRange<AShooterAIController>( GetWorld() ) )
    {
        if (!Controller->IsDead())
        {
            return ;
        }

        EndGame(true);

    }


}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWiner) 
{
    // for iterate in a range of objects we use the for loop like this:
    // TActor retrun a lsit of Actors from world
    for (AController* Controller :  TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = (Controller->IsPlayerController() == bIsPlayerWiner);
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }   
}
