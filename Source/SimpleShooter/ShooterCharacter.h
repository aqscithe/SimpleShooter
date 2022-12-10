// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookUp(float AxisValue);

	void LookRightRate(float AxisValue);
	void LookUpRate(float AxisValue);


	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MouseVerticalSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MouseHorizontalSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float GamepadLookSpeed = 50.f;
};
