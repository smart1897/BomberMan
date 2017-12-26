// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "FloorData.generated.h"

UCLASS()
class BOMBERMAN_API AFloorData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Spawn brick or wall at given location
	void Spawn(FVector location, bool destructable = false);

	//Fill the floor based on grid size and fill percent
	UFUNCTION(BlueprintCallable, Category = "GRID")
		void CreateLevel();

	//Set the size of Floor
	UFUNCTION(BlueprintCallable, Category = "GRID")
		void SetGridSize(int grid);

	//How many brick we need to fill
	UFUNCTION(BlueprintCallable, Category = "GRID")
		void SetFillPercent(float percent);

	//Create the border wall so that playr will not fall
	void CreateWall();

	//create all the destructable bricks based on fill percent
	void CreateBricks();

	//get random grid number on the floor
	int GetRandomID();

private:
	int m_iBlockWidth; //brick width
	float m_fFillPercent; //percent to be filled by bricks
	FVector m_vInitPosition; //Top let position of the floor
	UStaticMesh* m_cMesh; // Brick mesh
	int m_iGridSize; // size of floor
	UClass* m_cBrick; // Destruble brick Blueprint
	TArray<int> m_aOccupiedBricks;	//All the occupied grid position in floor
};
