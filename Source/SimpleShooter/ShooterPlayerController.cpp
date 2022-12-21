// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenClass);
		if (WinScreenClass)
			WinScreenWidget->AddToViewport();
	}
	else
	{
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenClass);
		if (LoseScreenClass)
			LoseScreenWidget->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartLevelTimerHandle, this, &APlayerController::RestartLevel, RestartLevelTimer, false);
}