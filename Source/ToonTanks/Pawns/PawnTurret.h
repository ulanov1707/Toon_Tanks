// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTurret.generated.h"
class APawnTank;
UCLASS()
class TOONTANKS_API APawnTurret : public ABasePawn
{
	GENERATED_BODY()

public:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 300.f;

	void CheckFireCondition();

	FTimerHandle FireRateTimerHandle;

	APawnTank* PlayerPawn;

	float ReturnDistanceToPalyer();

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;

	
};
