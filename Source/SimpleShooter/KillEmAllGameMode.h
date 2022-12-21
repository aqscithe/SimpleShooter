// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameMode.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public AShooterGameMode
{
	GENERATED_BODY()
	
public:
	void PawnKilled(class APawn* DeadPawn) override;

private:

	void EndGame(bool bIsPlayerWinner);
};
