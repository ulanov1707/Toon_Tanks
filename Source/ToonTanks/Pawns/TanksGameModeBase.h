// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay()override;
public:
	void ActorDied(AActor* DeadActor );

	UFUNCTION(BlueprintImplementableEvent)//functionality will be implemented in Blueprints 
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Start Delay", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 4;

	int32 NumberOfTurretsOnTheMap = 0;
	int32 GetNumberOfTurretsOnTheMap()const;

	void HandleGameStart();

	void HandleGameOver(bool PlayerWon);
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	APawnTank* RefToPlayerTank;


	APlayerControllerBase* PlayerControllerRef;


};
