// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(class APawn* DeadPawn)
{
	Super::PawnKilled(DeadPawn);

	APlayerController* PlayerController = Cast<APlayerController>(DeadPawn->GetController());

	if (PlayerController)
	{
		EndGame(false);
	}
	else
	{
		for (AShooterAIController* ShooterAI : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!ShooterAI->IsDead())
				return;
		}
		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}