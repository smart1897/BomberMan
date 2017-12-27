// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Bomber.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//set player who spwaned this bomb
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SpawnedBy(ABomber* by);

	//Which player spwaned this bomb
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		ABomber* GetSpawnedBY();

	//How much distance it will effect
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		int GetBombBlastDistance();

	//How much distance it should effect
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SetBombBlastDistance(int distance);

private:

	int m_iBombBlastDistance;//distance it will effect
	ABomber* m_cOwner; //player who spwaned this bomb
	
};
