// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTank.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOONTANKS_API APawnTank : public ABasePawn
{
	GENERATED_BODY()

public:

	APawnTank();

	bool GetPlayerAlive();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Movement" ,meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 200.0f;

	bool bAlive;//to stop Turret track the tank after the tank is died

	APlayerController* PlayerControllerRef;
	FHitResult TraceHit;

	FVector MoveDirection;
	FQuat RotationDirection;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();

protected:

	virtual void HandleDestruction() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
