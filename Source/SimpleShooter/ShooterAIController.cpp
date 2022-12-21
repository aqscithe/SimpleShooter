// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (EnemyAIBehavior)
	{
		RunBehaviorTree(EnemyAIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
		
		
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ShooterAIChar = Cast<AShooterCharacter>(GetPawn());
	if (ShooterAIChar)
		return ShooterAIChar->IsDead();
	return true;
}