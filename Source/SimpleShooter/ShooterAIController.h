// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Public Functions
	virtual void Tick(float DeltaSeconds)override;

	// query if the ai character is dead
	bool IsDead() const;
	
protected:
	virtual void BeginPlay() override;

private:
	//private varialbes

	// temporal playerPawn*
	APawn* PlayerPawn = nullptr;

	// acceptance radius
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	
	//private Fucntions


};
