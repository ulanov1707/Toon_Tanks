// Fill out your copyright notice in the Description page of Project Settings.


#include "TanksGameModeBase.h"
#include "PawnTank.h"
#include"PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include"PlayerControllerBase.h"

void ATanksGameModeBase::BeginPlay()
{
	
	NumberOfTurretsOnTheMap = GetNumberOfTurretsOnTheMap();//Current Number of Turrets on the map 

	RefToPlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));//Reference to PLayer


	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	Super::BeginPlay();
}

void ATanksGameModeBase::ActorDied(AActor* DeadActor)
{
	//check what type of actor died if turret , destroy .If Player  -> Go to lose condition

	if (DeadActor == RefToPlayerTank)
	{
		RefToPlayerTank->PawnDestroyed();
		HandleGameOver(false);//Player Loose

		if (PlayerControllerRef) 
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) 
	{
		DestroyedTurret->PawnDestroyed();
		NumberOfTurretsOnTheMap--;

		if (NumberOfTurretsOnTheMap == 0) 
		{
			HandleGameOver(true);//Playr Win
		}

	}

}

int32 ATanksGameModeBase::GetNumberOfTurretsOnTheMap() const
{

	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();//dont know what it does ,check it online

	TArray<AActor*> TurretActors;//holds ref to all Turrets on the Map in the array 
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);//Finds all the Turrets on the map and saves it into array

	return TurretActors.Num();
}

void ATanksGameModeBase::HandleGameStart()
{

	//call BP versions GameStart();
	GameStart();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		//Lecture 156
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATanksGameModeBase::HandleGameOver(bool PlayerWon)
{

	//call BP version of GameOver();
	GameOver(PlayerWon);

}
