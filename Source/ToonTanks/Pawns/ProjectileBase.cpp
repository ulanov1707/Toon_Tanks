// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include"Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));

	

	RootComponent = ProjectileMesh;
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Momement"));

	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;


	//after 3 seconds gets destroyed  i guess
	InitialLifeSpan = 3.f;

	FlyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Flying Particel"));
	FlyParticle->SetupAttachment(RootComponent);
	
	
 
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//every time when our bullet mesh hits something "OnHit" function gets called
	//AddDynami - is delegats(Binds). Binds EVENT to FUNCTION ,Each time EVENT is happened BINDED FUNCTION gets called 
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	if (LaunchSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound, GetActorLocation());
	}
}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	
	AActor* MyOwner = GetOwner();

	//early return if the there is no  valid reference, if its valid just do code below "if" 
	if (!MyOwner) {
		return;
	}


	

	//If the other actors isnt self or owner , then apply damage 
	if (OtherActor != NULL && OtherActor != this && OtherActor != MyOwner) 
	{
		//Applies damage to other actor
		UGameplayStatics::ApplyDamage(OtherActor/*To whom to apply damage*/,
										Damage,//amount of damage
										MyOwner->GetInstigatorController(),//reference to Controller
										this,
										DamageType//Damage type
		);
	
		if (HitParticle)//particle effect
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), FRotator::ZeroRotator);
		}
		if (HitSound) //sound 
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (HitShake) //camera shake
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HitShake, 1);
		}

		Destroy();
	}


	//Do some effects

	

}


