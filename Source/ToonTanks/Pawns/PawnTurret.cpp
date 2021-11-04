// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include"Kismet/GameplayStatics.h"
#include "PawnTank.h"


void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPalyer() > FireRange) 
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());//Parent's function makes turret rotate to the player if the player in range
	
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Each 2 seconds will call CheckFireCondition() i guess
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);


}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();

}

void APawnTurret::CheckFireCondition()
{
	//if the player is null or DEAD Dont Fire	
	if (!PlayerPawn  || !PlayerPawn->GetPlayerAlive()) {
		return;
	}


	//if the player in range then FIRE

	if (ReturnDistanceToPalyer() <= FireRange) {
		
		//Fire
		Fire();//Parent's function
	}
}

float APawnTurret::ReturnDistanceToPalyer()
{
	//check is we have a valid referecne to Player
	if (!PlayerPawn) {
		return 0.0f;
	}

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();

	return Distance;

}