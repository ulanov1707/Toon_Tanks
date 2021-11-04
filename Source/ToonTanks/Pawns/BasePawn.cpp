// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include"Components/CapsuleComponent.h"
#include"Components/SceneComponent.h"
#include"Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(GetRootComponent());

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void ABasePawn::PawnDestroyed()// this is only for "PawnTurret" since Turret can be destroyed , Tank must be HIDED ONLY
{
	HandleDestruction();

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//Update TurretMesh rotation to face the LookAtTarget(Tank's location) passed in from the child class

	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X,LookAtTarget.Y,TurretMesh->GetComponentLocation().Z));

	TurretMesh->SetWorldRotation(TurretRotation);
}

void  ABasePawn::Fire()
{
	//Get projectileSpawnPoint location && rotation and -> Spawn Projectile class
	if (ProjectileClass) 
	{
		FVector LocationToSpawn = ProjectileSpawnPoint->GetComponentLocation();
		FRotator RotationToSpwan = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, LocationToSpawn, RotationToSpwan);
		TempProjectile->SetOwner(this);
	}
}

void  ABasePawn::HandleDestruction()
{
	if (DeathParticle) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), FRotator::ZeroRotator);
	}
	if (DeathSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if (DeathShake) //camera shake
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(DeathShake, 1);
	}

}