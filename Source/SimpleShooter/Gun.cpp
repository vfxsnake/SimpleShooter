// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// attaching the components inside the class
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);



}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() 
{
	// UE_LOG(LogTemp, Warning,TEXT("Pulling trigger from %s"), *GetName());
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	
	// get view position fron character controller:
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return ;
	}

	AController* OwnerController = OwnerPawn->GetController();

	if (! OwnerController)
	{
		return ;
	}
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// draw a camera for debugin ray cast position:
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	// calculatin the end poitn of the trace:
	// create a vector from location pointing to Rotation direction scaled by max range scalar
	FVector End = Location + Rotation.Vector() * MaxRange;

	// tracing channel alog vector
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bSuccess)
	{
		// drawin debug hit location
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		
		// set direction to inverse of hit direction to point to us.
		
		if (ImpacktEffect)
		{
			FVector ShotDirection = -Rotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpacktEffect, Hit.Location, ShotDirection.Rotation());
			//  applying damage:
			
			AActor* HitActor =  Hit.GetActor();
			if (HitActor )
			{
				// first create a FPointDamageEvent: takes Damage value, Hit result, Direction and a subclass in this case none
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); 
			
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
}

