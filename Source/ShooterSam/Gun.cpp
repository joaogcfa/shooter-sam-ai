// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{

	MuzzleFlashParticleSystem->Activate(true);

	if(OwnerController)
	{
		FVector Location;
		FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location, Rotation);
		FVector End = Location + Rotation.Vector() * MaxRange;
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		if(GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel2, Params))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, Hit.ImpactPoint, Hit.ImpactPoint.Rotation());
			//DrawDebugSphere(GetWorld(), Hit.Location, 20, 12, FColor::Red, false, 2.0f);
			/*DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, false, 2.0f);
			DrawDebugLine(GetWorld(), Location, Hit.Location, FColor::Green, false, 2.0f);*/
			if(Hit.GetActor())
			{
				DrawDebugString(GetWorld(), Hit.Location, Hit.GetActor()->GetName(), nullptr, FColor::White, 2.0f);
				
				// Apply damage using GameplayStatics
				UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, OwnerController, this, UDamageType::StaticClass());
			}
			
		}
		
	}
}

