// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ShooterCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealthComponent::PointDamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::PointDamageTaken(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	float DamageToApply = FMath::Min(Health, Damage);

	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Actor %s received %f damage. Current Health: %f"), *DamagedActor->GetName(), DamageToApply, Health);

	if (Health <= 0.f)
	{
		Cast<AShooterCharacter>(DamagedActor)->SetDead(true);
	}
}

