// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Pickups.generated.h"

UENUM()
enum EPickupType
{
	AddBombs,
	AddBombsDistance,
	AddSpeed,
	SubBombs,
	SubBombsDistance,
	SubSpeed,
	Detonator
};

UCLASS()
class BOMBERMAN_API APickups : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickups();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Generate an overlap function whewhever actor passes through this actor
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UStaticMeshComponent* m_cStaticMeshComponent;//Static Mesh to Load

	EPickupType m_ePickupType;//Type of pickup

	//Materials for Pickup mesh
	UMaterialInterface* m_mat_AddBomb;
	UMaterialInterface* m_mat_AddBomb_Dist;
	UMaterialInterface* m_mat_AddSpeed;
	UMaterialInterface* m_mat_SubBomb;
	UMaterialInterface* m_mat_SubBomb_Dist;
	UMaterialInterface* m_mat_SubSpeed;
	UMaterialInterface* m_mat_Det;

	float m_fSelfDestroyTime;//Destrouy after certain time

	USoundBase* m_cPickupSound;
};
