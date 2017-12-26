// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorData.h"


// Sets default values
AFloorData::AFloorData()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> pCube(TEXT("StaticMesh'/Game/Meshes/Brick.Brick'"));
	m_cMesh = pCube.Object;

	static ConstructorHelpers::FObjectFinder<UClass> pBrick(TEXT("Blueprint'/Game/Blueprints/Brick_BP.Brick_BP_C'"));
	m_cBrick = pBrick.Object;
}

// Called when the game starts or when spawned
void AFloorData::BeginPlay()
{
	Super::BeginPlay();

	m_iBlockWidth = 100;
	m_iGridSize = 10;
	m_fFillPercent = 0.4f;
}


// Called every frame
void AFloorData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloorData::CreateLevel()
{
	m_aOccupiedBricks.Empty();

	m_vInitPosition.X = ((m_iGridSize * 100) / 2) - (m_iBlockWidth / 2);
	m_vInitPosition.Y = -(((m_iGridSize * 100) / 2) - (m_iBlockWidth / 2));

	for (TActorIterator<AActor> It(GetWorld(), AStaticMeshActor::StaticClass()); It; ++It)
	{
		AStaticMeshActor* Actor = Cast<AStaticMeshActor>(*It);
		if (Actor->GetName() == "Floor")
		{
			Actor->SetActorScale3D(FVector(m_iGridSize / 10.0f, m_iGridSize / 10.0f, m_iGridSize / 10.0f));
		}
	}

	FVector location;
	location.X = m_vInitPosition.X - (1 * 100);
	location.Y = m_vInitPosition.Y + (1 * 100);
	location.Z = 0;
	APlayerStart* player = GetWorld()->SpawnActor<APlayerStart>(location, FRotator(0, 0, 0));
	player->PlayerStartTag = "Player1";
	m_aOccupiedBricks.Add(m_iGridSize + 1);
	m_aOccupiedBricks.Add(m_iGridSize + 2);
	m_aOccupiedBricks.Add(2 * m_iGridSize + 2);

	location.X = m_vInitPosition.X - ((m_iGridSize - 2) * 100);
	location.Y = m_vInitPosition.Y + ((m_iGridSize - 2) * 100);
	location.Z = 0;
	player = GetWorld()->SpawnActor<APlayerStart>(location, FRotator(0, 0, 0));
	player->PlayerStartTag = "Player2";
	m_aOccupiedBricks.Add((m_iGridSize - 2) * m_iGridSize + (m_iGridSize - 2));
	m_aOccupiedBricks.Add((m_iGridSize - 2) * m_iGridSize + (m_iGridSize - 3));
	m_aOccupiedBricks.Add((m_iGridSize - 3) * m_iGridSize + (m_iGridSize - 2));

	CreateWall();
	CreateBricks();
}

void AFloorData::SetGridSize(int grid)
{
	m_iGridSize = grid;
}

void AFloorData::SetFillPercent(float percent)
{
	m_fFillPercent = percent;
	if (m_fFillPercent > 0.7f)
	{
		m_fFillPercent = 0.7f;
	}
}

void AFloorData::CreateWall()
{
	FVector location;
	location.X = m_vInitPosition.X;
	location.Y = m_vInitPosition.Y;
	location.Z = 0;
	for (int i = 0; i < m_iGridSize; i++)
	{
		location.X = m_vInitPosition.X;
		location.Y = m_vInitPosition.Y + (i * 100);
		m_aOccupiedBricks.Add(i);
		Spawn(location);

		location.X = m_vInitPosition.X - ((m_iGridSize - 1) * 100);
		location.Y = m_vInitPosition.Y + (i * 100);
		m_aOccupiedBricks.Add((m_iGridSize - 1) * m_iGridSize + i);
		Spawn(location);

		if (i != 0 && i < m_iGridSize - 1)
		{
			location.X = m_vInitPosition.X - (i * 100);
			location.Y = m_vInitPosition.Y;
			m_aOccupiedBricks.Add(i * m_iGridSize);
			Spawn(location);

			location.X = m_vInitPosition.X - (i * 100);
			location.Y = m_vInitPosition.Y + ((m_iGridSize - 1) * 100);
			m_aOccupiedBricks.Add(i * m_iGridSize + (m_iGridSize - 1));
			Spawn(location);
		}
	}
}

int AFloorData::GetRandomID()
{
	int rand = FMath::RandRange(0, m_iGridSize*m_iGridSize - 1);
	if (m_aOccupiedBricks.Contains(rand))
	{
		return GetRandomID();
	}
	return rand;
}

void AFloorData::CreateBricks()
{
	int bricksToSpawn = (m_iGridSize*m_iGridSize - 1) * m_fFillPercent;

	for (int i = 0; i < bricksToSpawn; i++)
	{
		int id = GetRandomID();
		m_aOccupiedBricks.Add(id);

		FVector location;
		location.X = m_vInitPosition.X - ((id / m_iGridSize) * 100);
		location.Y = m_vInitPosition.Y + ((id % m_iGridSize) * 100);
		location.Z = 0;
		int rand = FMath::RandRange(0, 1000);
		if (rand < 300)
		{
			Spawn(location);
		}
		else
		{
			Spawn(location, true);
		}
	}
}

void AFloorData::Spawn(FVector location, bool destructable)
{
	if (destructable)
	{
		AActor* NewBlock = GetWorld()->SpawnActor<AActor>(m_cBrick, location, FRotator(0, 0, 0));
		TArray<UStaticMeshComponent*> Comps;
		NewBlock->GetComponents(Comps);
		if (Comps.Num() > 0)
		{
			UStaticMeshComponent* FoundComp = Comps[0];
			FoundComp->SetWorldScale3D(FVector(1, 1, 1));
			FoundComp->SetCastShadow(false);
		}
	}
	else
	{
		AStaticMeshActor* NewBlock = GetWorld()->SpawnActor<AStaticMeshActor>(location, FRotator(0, 0, 0));
		TArray<UStaticMeshComponent*> Comps;
		NewBlock->GetComponents(Comps);
		if (Comps.Num() > 0)
		{
			UStaticMeshComponent* FoundComp = Comps[0];
			FoundComp->SetStaticMesh(m_cMesh);
			FoundComp->SetWorldScale3D(FVector(1, 1, 1));
			FoundComp->SetCastShadow(false);
		}
	}
}

