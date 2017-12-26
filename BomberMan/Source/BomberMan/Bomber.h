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

	//Binding Keyboard nd player ID
	UFUNCTION(BlueprintCallable, Category = "Bomber")
		void SetInput(int id);

private:
	int m_iPlayerID;
};
