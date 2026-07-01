// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Pawn: %s and location: %s"), *PlayerPawn->GetName(), *PlayerPawn->GetActorLocation().ToString());
		SetFocus(PlayerPawn);
	}

}
