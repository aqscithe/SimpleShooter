// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	class UParticleSystem* BulletImpact;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

public:	

	void PullTrigger();

	void HandleHit(FRotator& ViewPointRotation, FHitResult& OutHit, AController* OwnerController);
	

};
