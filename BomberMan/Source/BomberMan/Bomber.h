// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "Bomber.generated.h"

UCLASS()
class BOMBERMAN_API ABomber : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABomber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Player Movement
	void MoveUP(float delta);
	void MoveDown(float delta);
	void MoveLeft(float delta);
	void MoveRight(float delta);

	//Modifier function based on Pickups
	void AddMaxBombs();
	void SubMaxBombs();
	void ActivateDetonator();
	void AddBombDistance();
	void SubBombDistance();
	void AddSpeed();
	void SubSpeed();

	//Binding Keyboard nd player ID
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SetInput(int id);

	//Spawn bomb when key is preesed
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Bomber")
		void PlaceBomb();

	//Whenevr bomb is placed subtract the count
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void AddBombs();

	//Whenevr bomb is exploded add the bomb count
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SubtractBombs();

	//Distance to which bomb should explode
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		int GetBombDistance();

	//Get number of bombs available
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		int GetBombsAvailable();	

	//Check whether we have detonator
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		bool IsDetonatorActivated();

	//Explode the bomb with detonator
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void DetonateBomb();

	//Shold bomb explode
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		bool ShouldExplodeBomb();

	//Add score when ever we break 
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void AddScore(int score);

	//Get current score for player
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		int GetScore();

	//killed by bomb set player dead
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SetDead(bool isdead);

	//is Player Alive?
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		bool IsDead();

private:
	int m_iPlayerID; // PLayer id for bomber
	int m_iBombsAvailable; // current available bombs
	int m_iBombsPlaced; // current available bombs
	int m_iMaxBombsAvailable; // Maximum available bombs
	int m_iBombBlastDistance; // Bomb Blast Distance
	float m_fMovementSpeed; // player movement speed
	bool m_bActivateDetonator; // Activte detonator
	float m_fDetonatorTime; // how much time still we have detonator
	float m_fMaxDetonatorTime; // Maximun time we can have detonator
	bool m_bShouldExplode; //Explode the bomb detonator is preesed
	float m_fScore; //Player Score
	bool m_bDead;//is player dead
};
