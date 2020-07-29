// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

// forward declaration
class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// overriding TakeDamage:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
								 class AController* EventInstigator, AActor* DamageCauser) override;
	
	// funciton callable by blueprint as a native node that doesn't have an execution pin 
	// is callble inside blueprint natively.
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// this function become public to have the ability to shit fron the behavior tree from the ai controller.
	void Shoot();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	// variables
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	
	// health variables:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	// using the template class of Agun to store the object inside blue print,
	// this prevents to only store the specify class after that the gun pointer is stored
	// in the AGun pointer 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;


	// functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	

};
