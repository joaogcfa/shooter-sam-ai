// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"	
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AShooterSamCharacter* PlayerCharacter = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);

	for (AActor* Actor : ShooterAIActors)
	{
		AShooterAI* ShooterAI = Cast<AShooterAI>(Actor);
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(PlayerCharacter);
		}
	}
}
