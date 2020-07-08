// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// binding imputs from the engine settings imput connections to this component:
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	
	// binding Move Right
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &AShooterCharacter::MoveRight);

	/* for the LookUP function we are gonig to call a fucntion that is abailable from the pawn class.
	AddControllerPitchInput() this funciton adds the value of axis to the current pitch of the characater.*/
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	//bind look Right
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	// Binding Action
	// Binding Jump Action: Actions needs an enum to specify on which event will be triggerend:
	// jump is implemented in the character class so we call it form there.
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	//  this function is inherited fro pawn. adds the input value to currentPosition.
	// we multiply the axis value to the forward vector that is normalized so it can be
	// positive or negative.
	AddMovementInput(GetActorForwardVector() * AxisValue ); 
	
}

void AShooterCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}




