// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;

	GameModeRef = Cast<ATanksGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to the Owner"));
	}

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageActor)
{

	if (Damage == 0 || Health == 0 )//we put "Health == 0" so, that if the actor died , then it never goes to code below 
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);



	if (Health <= 0)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to the GameMode"));
		}
	}
}


