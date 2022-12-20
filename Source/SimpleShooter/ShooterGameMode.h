// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
		virtual void BeginPlay() override;

		virtual void PawnKilled(class APawn* DeadPawn);

private:

	
	class AShooterCharacter* PlayerShooter;
	
};
