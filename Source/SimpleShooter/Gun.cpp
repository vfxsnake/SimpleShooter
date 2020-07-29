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

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{	
	AController* OwnerController = GetOwnerController();
	if (! OwnerController)
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	// draw a camera for debugin ray cast position:
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	// calculatin the end poitn of the trace:
	// create a vector from location pointing to Rotation direction scaled by max range scalar
	FVector End = Location + Rotation.Vector() * MaxRange;

	// tracing channel alog vector
	Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
}

AController* AGun::GetOwnerController() const
{
	// get view position fron character controller:
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return nullptr;
	}

	return OwnerPawn->GetController();

}

void AGun::PullTrigger() 
{
	// spawning emmiter
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	
	//spawning sound:
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess  = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		// drawin debug hit location
		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		// set direction to inverse of hit direction to point to us.
		
		if (ImpacktEffect)
		{
			// impact fx
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpacktEffect, Hit.Location, ShotDirection.Rotation());
			// iimpactSound
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
			
			//  applying damage:
			
			AActor* HitActor =  Hit.GetActor();
			if (HitActor )
			{
				// first create a FPointDamageEvent: takes Damage value, Hit result, Direction and a subclass in this case none
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); 
				AController* OwnerController = GetOwnerController();
			
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
}

