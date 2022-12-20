// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"

#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"


void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerShooter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AShooterGameMode::PawnKilled(APawn* DeadPawn)
{

}