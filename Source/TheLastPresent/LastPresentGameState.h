// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LastPresentGameState.generated.h"

/**
 * 
 */
UCLASS()
class THELASTPRESENT_API ALastPresentGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	bool HasGameEnded = false;
};
