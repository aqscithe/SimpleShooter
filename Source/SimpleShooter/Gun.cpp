// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMesh, TEXT("MuzzleFlashSocket"));

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;
	
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FHitResult OutHit;
	bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(OutHit, ViewPointLocation, End, ECC_GameTraceChannel1);	
	if (bHitSuccess)
	{
		FVector ShotDirection = -ViewPointRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), 
			BulletImpact, 
			OutHit.ImpactPoint, 
			(ShotDirection + OutHit.ImpactNormal).Rotation()
		);

		AActor* HitActor = OutHit.GetActor();
		if (HitActor && HitActor != GetOwner() && HitActor != this)
		{
			FPointDamageEvent BulletDamageEvent = FPointDamageEvent(Damage, OutHit, ShotDirection, UDamageType::StaticClass());
			HitActor->TakeDamage(Damage, BulletDamageEvent, OwnerController, this);
			UE_LOG(LogTemp, Display, TEXT("Actor %s was shot."), *HitActor->GetName());
		}
	}
}

