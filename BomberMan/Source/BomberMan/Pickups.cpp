// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups.h"
#include "Bomber.h"

// Sets default values
APickups::APickups()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create staic mesh component
	m_cStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComponent"));

	//Apply the mesh and collison
	static ConstructorHelpers::FObjectFinder<UStaticMesh> pCube(TEXT("StaticMesh'/Game/Meshes/Brick.Brick'"));
	m_cStaticMeshComponent->SetStaticMesh(pCube.Object);
	m_cStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = m_cStaticMeshComponent;

	//Set the delegate function for overlap method
	m_cStaticMeshComponent->bGenerateOverlapEvents = true;
	FScriptDelegate BeginOverlapDelegate;
	BeginOverlapDelegate.BindUFunction(this, FName("OnOverlapBegin"));
	m_cStaticMeshComponent->OnComponentBeginOverlap.AddUnique(BeginOverlapDelegate);

	static ConstructorHelpers::FObjectFinder<UMaterial> pABomb(TEXT("Material'/Game/Materials/BombPlus_Mat'"));
	if (pABomb.Succeeded())
	{
		m_mat_AddBomb = pABomb.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pABombDist(TEXT("Material'/Game/Materials/BombDistPlus_Mat'"));
	if (pABombDist.Succeeded())
	{
		m_mat_AddBomb_Dist = pABombDist.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pASpeed(TEXT("Material'/Game/Materials/SpeedPlus_Mat'"));
	if (pASpeed.Succeeded())
	{
		m_mat_AddSpeed = pASpeed.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pSBomb(TEXT("Material'/Game/Materials/BombMinus_Mat'"));
	if (pSBomb.Succeeded())
	{
		m_mat_SubBomb = pSBomb.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pSBombDist(TEXT("Material'/Game/Materials/BombDistMinus_Mat'"));
	if (pSBombDist.Succeeded())
	{
		m_mat_SubBomb_Dist = pSBombDist.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pSSpeed(TEXT("Material'/Game/Materials/SpeedMinus_Mat'"));
	if (pSSpeed.Succeeded())
	{
		m_mat_SubSpeed = pSSpeed.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> pDet(TEXT("Material'/Game/Materials/BombDet_Mat'"));
	if (pDet.Succeeded())
	{
		m_mat_Det = pDet.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> pSound(TEXT("SoundWave'/Game/Sounds/power_up.power_up'"));
	if (pSound.Succeeded())
	{
		m_cPickupSound = pSound.Object;
	}
}

// Called when the game starts or when spawned
void APickups::BeginPlay()
{
	Super::BeginPlay();

	float rand = FMath::FRand();

	if (rand < 0.1)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_Det);
		m_ePickupType = EPickupType::Detonator;
	}
	else if (rand < 0.25)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_AddBomb);
		m_ePickupType = EPickupType::AddBombs;
	}
	else if (rand < 0.40)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_SubBomb);
		m_ePickupType = EPickupType::SubBombs;
	}
	else if (rand < 0.55)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_AddBomb_Dist);
		m_ePickupType = EPickupType::AddBombsDistance;
	}
	else if (rand < 0.70)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_SubBomb_Dist);
		m_ePickupType = EPickupType::SubBombsDistance;
	}
	else if (rand < 0.85)
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_AddSpeed);
		m_ePickupType = EPickupType::AddSpeed;
	}
	else
	{
		m_cStaticMeshComponent->SetMaterial(0, m_mat_SubSpeed);
		m_ePickupType = EPickupType::SubSpeed;
	}
	m_fSelfDestroyTime = FMath::RandRange(5.0f, 10.0f);
}

// Called every frame
void APickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_fSelfDestroyTime -= DeltaTime;

	if (m_fSelfDestroyTime <= 0.0f)
	{
		Destroy();
	}
}

void APickups::OnOverlapBegin(UPrimitiveComponent * newComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABomber* actor = (ABomber*)OtherActor;
		if (actor != nullptr && actor->GetName().Contains("Bomber_BP"))
		{
			switch (m_ePickupType)
			{
			case AddBombs:
				actor->AddMaxBombs();
				actor->AddScore(10);
				break;
			case AddBombsDistance:
				actor->AddBombDistance();
				actor->AddScore(10);
				break;
			case AddSpeed:
				actor->AddSpeed();
				actor->AddScore(10);
				break;
			case SubBombs:
				actor->SubMaxBombs();
				actor->AddScore(20);
				break;
			case SubBombsDistance:
				actor->SubBombDistance();
				actor->AddScore(20);
				break;
			case SubSpeed:
				actor->SubSpeed();
				actor->AddScore(20);
				break;
			case Detonator:
				actor->ActivateDetonator();
				actor->AddScore(30);
				break;
			default:
				break;
			}
			UGameplayStatics::PlaySound2D(GetWorld(), m_cPickupSound);
			Destroy();
		}
	}

}

