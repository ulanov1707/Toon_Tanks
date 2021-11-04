// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

	bAlive = true;
}



// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if (PlayerControllerRef) 
	{
		//Gives basically the location of the cursor or something like that 
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHit);
		FVector HitLocation = TraceHit.ImpactPoint;

		//rotates a FireGun of the tank based on cursors location 
		RotateTurret(HitLocation);
	}
}
// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}


void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}



void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	//Hide player

	bAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);//Sets Tick function to STOP RUNNING 


}


bool APawnTank::GetPlayerAlive() {
	return bAlive;
}