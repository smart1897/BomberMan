// Fill out your copyright notice in the Description page of Project Settings.

//content that is not created by me 
//Source taken from
//https://wiki.unrealengine.com/Local_Multiplayer_Tips

#pragma once

#include "Engine.h"
#include "Engine/GameViewportClient.h"
#include "BomberManViewportClient.generated.h"

/**
*
*/
UCLASS()
class BOMBERMAN_API UBomberManViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
};
