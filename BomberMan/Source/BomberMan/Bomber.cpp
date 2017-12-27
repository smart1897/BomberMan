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
	m_iMaxBombsAvailable = 1;
	m_iBombsAvailable = 1;
	m_iBombBlastDistance = 150;
	m_fMovementSpeed = 0.8f;
	m_bActivateDetonator = false;
	m_fDetonatorTime = 10.0f;
	m_fMaxDetonatorTime = 10.0f;
	m_bShouldExplode = false;
	m_iBombsPlaced = 0;
	m_fScore = 0.0f;
	m_bDead = false;
}

// Called every frame
void ABomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_bActivateDetonator)
	{
		m_fDetonatorTime -= DeltaTime;
		if (m_fDetonatorTime < 0.0f)
		{
			m_bActivateDetonator = false;
			m_iBombsAvailable = m_iMaxBombsAvailable;
			m_bShouldExplode = false;
		}
	}
	if (m_bDead == false && m_fScore > 0.0f)
	{
		m_fScore -= DeltaTime;
	}
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
		AddMovementInput(FVector(1, 0, 0), delta*m_fMovementSpeed);
	}
}

void ABomber::MoveDown(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 90, 0));
		AddMovementInput(FVector(-1, 0, 0), delta*m_fMovementSpeed);
	}
}

void ABomber::MoveLeft(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 180, 0));
		AddMovementInput(FVector(0, -1, 0), delta*m_fMovementSpeed);
	}
}

void ABomber::MoveRight(float delta)
{
	if (delta > 0.0f)
	{
		GetMesh()->SetWorldRotation(FRotator(0, 0, 0));
		AddMovementInput(FVector(0, 1, 0), delta*m_fMovementSpeed);
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
		InputComponent->BindAction("DetonateBomb_P1", IE_Pressed, this, &ABomber::DetonateBomb);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveUP_P2", this, &ABomber::MoveUP);
		InputComponent->BindAxis("MoveDown_P2", this, &ABomber::MoveDown);
		InputComponent->BindAxis("MoveLeft_P2", this, &ABomber::MoveLeft);
		InputComponent->BindAxis("MoveRight_P2", this, &ABomber::MoveRight);
		InputComponent->BindAction("PlaceBomb_P2", IE_Pressed, this, &ABomber::PlaceBomb);
		InputComponent->BindAction("DetonateBomb_P1", IE_Pressed, this, &ABomber::DetonateBomb);
	}
}

void ABomber::AddBombs()
{
	m_iBombsAvailable++;
	m_iBombsPlaced--;
	m_bShouldExplode = false;
}

void ABomber::SubtractBombs()
{
	m_iBombsAvailable--;
	m_iBombsPlaced++;
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

void ABomber::AddMaxBombs()
{
	if (!m_bActivateDetonator)
	{
		m_iBombsAvailable++;
	}
	m_iMaxBombsAvailable++;
}

void ABomber::SubMaxBombs()
{	
	if ((m_iBombsAvailable + m_iBombsPlaced) >= 2)
	{
		m_iBombsAvailable--;
	}
	
	if (m_iMaxBombsAvailable >= 2)
	{
		m_iMaxBombsAvailable--;
	}
}

void ABomber::ActivateDetonator()
{
	m_bActivateDetonator = true;
	m_fDetonatorTime = m_fMaxDetonatorTime;
	m_iBombsAvailable = 1;
}

bool ABomber::IsDetonatorActivated()
{
	return m_bActivateDetonator;
}

void ABomber::AddBombDistance()
{
	m_iBombBlastDistance += 100;
}

void ABomber::SubBombDistance()
{	
	if (m_iBombBlastDistance > 150)
	{
		m_iBombBlastDistance -= 100;
	}
}

void ABomber::AddSpeed()
{	
	if (m_fMovementSpeed < 1.5f)
	{
		m_fMovementSpeed += 0.1f;
	}
}

void ABomber::SubSpeed()
{	
	if (m_fMovementSpeed > 0.8f)
	{
		m_fMovementSpeed -= 0.1f;
	}
}

void ABomber::DetonateBomb()
{
	if (m_bActivateDetonator)
	{
		m_bShouldExplode = true;
	}
}

bool ABomber::ShouldExplodeBomb()
{
	return m_bShouldExplode;
}

void ABomber::AddScore(int score)
{
	m_fScore += score;
}

int ABomber::GetScore()
{
	return m_fScore;
}

void ABomber::SetDead(bool isdead)
{
	m_bDead = isdead;
}

bool ABomber::IsDead()
{
	return m_bDead;
}
