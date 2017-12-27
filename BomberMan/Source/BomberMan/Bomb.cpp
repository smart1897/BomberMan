// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"


// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::SpawnedBy(ABomber * by)
{
	m_cOwner = by;
}

ABomber * ABomb::GetSpawnedBY()
{
	return m_cOwner;
}

int ABomb::GetBombBlastDistance()
{
	return m_iBombBlastDistance;
}

void ABomb::SetBombBlastDistance(int distance)
{
	m_iBombBlastDistance = distance;
}

