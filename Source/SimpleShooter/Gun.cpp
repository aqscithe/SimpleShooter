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
	UGameplayStatics::SpawnSoundAttached(GunShotSound, SkeletalMesh, TEXT("MuzzleFlashSocket"));

	FVector ShotDirection;
	FHitResult OutHit;

	bool bHitSuccess = GunTraceHit(ShotDirection, OutHit);
	if (bHitSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, OutHit.ImpactPoint, (ShotDirection + OutHit.ImpactNormal).Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BulletImpactSound, OutHit.ImpactPoint);
		DamageActor(ShotDirection, OutHit);

	}
}

void AGun::DamageActor(FVector& ShotDirection, FHitResult& OutHit)
{
	AActor* HitActor = OutHit.GetActor();
	if (HitActor)
	{
		AController* OwnerController = GetOwnerController();
		if (OwnerController)
		{
			FPointDamageEvent BulletDamageEvent = FPointDamageEvent(Damage, OutHit, ShotDirection, UDamageType::StaticClass());
			HitActor->TakeDamage(Damage, BulletDamageEvent, OwnerController, this);
		}
	}
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
		return nullptr;

	return OwnerPawn->GetController();
}

bool AGun::GunTraceHit(FVector& ShotDirection, FHitResult& OutHit)
{
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	AController* OwnerController = GetOwnerController();
	if (OwnerController)
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	else
		return false;

	ShotDirection = -ViewPointRotation.Vector();

	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	return GetWorld()->LineTraceSingleByChannel(OutHit, ViewPointLocation, End, ECC_GameTraceChannel1, Params);
}

