// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomber.h"


// Sets default values
ABomber::ABomber()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABomber::BeginPlay()
{
	Super::BeginPlay();
	m_iBombsAvailable = 1;
	m_iBombBlastDistance = 150;
}

// Called every frame
void ABomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABomber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABomber::MoveUP(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 270, 0));
		AddMovementInput(FVector(1, 0, 0), delta);
	}
}

void ABomber::MoveDown(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 90, 0));
		AddMovementInput(FVector(-1, 0, 0), delta);
	}
}

void ABomber::MoveLeft(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 180, 0));
		AddMovementInput(FVector(0, -1, 0), delta);
	}
}

void ABomber::MoveRight(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 0, 0));
		AddMovementInput(FVector(0, 1, 0), delta);
	}
}

void ABomber::SetInput(int id)
{
	m_iPlayerID = id;

	if (id == 0)
	{
		InputComponent->BindAxis("MoveUP_P1", this, &ABomber::MoveUP);
		InputComponent->BindAxis("MoveDown_P1", this, &ABomber::MoveDown);
		InputComponent->BindAxis("MoveLeft_P1", this, &ABomber::MoveLeft);
		InputComponent->BindAxis("MoveRight_P1", this, &ABomber::MoveRight);
		InputComponent->BindAction("PlaceBomb_P1", IE_Pressed, this, &ABomber::PlaceBomb);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveUP_P2", this, &ABomber::MoveUP);
		InputComponent->BindAxis("MoveDown_P2", this, &ABomber::MoveDown);
		InputComponent->BindAxis("MoveLeft_P2", this, &ABomber::MoveLeft);
		InputComponent->BindAxis("MoveRight_P2", this, &ABomber::MoveRight);
		InputComponent->BindAction("PlaceBomb_P2", IE_Pressed, this, &ABomber::PlaceBomb);
	}
}

void ABomber::AddBombs()
{
	m_iBombsAvailable++;
}

void ABomber::SubtractBombs()
{
	m_iBombsAvailable--;
}

int ABomber::GetBombDistance()
{
	return m_iBombBlastDistance;
}

int ABomber::GetBombsAvailable()
{
	return m_iBombsAvailable;
}

void ABomber::PlaceBomb_Implementation()
{

}

