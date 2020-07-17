// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();
    // ask for player pawn and stores in a pointer.
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
    //using the path findig geo move to the actor 
    MoveToActor(PlayerPawn); 

}
