// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner())
	{
		AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (ShooterCharacter)
		{
			ShooterCharacter->Shoot();
			return EBTNodeResult::Succeeded;
		}	
	}
	return EBTNodeResult::Failed;
}