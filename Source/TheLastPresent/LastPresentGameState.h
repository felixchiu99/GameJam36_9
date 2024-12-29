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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	EEnumInGameLevelState GameLevelState;
public:
	bool IsInMenu = false;
	bool IsOverlay = false;
	bool HasGameStarted = true;
	bool HasGameEnded = false;
	
	double timeStart;
	double timeEnd;

public:
	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintPure)
	float GetMillisecondElapsed();

	UFUNCTION(BlueprintCallable)
	void EndTimer();

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GoalReached();

	UFUNCTION(BlueprintCallable)
	void GamePause();

	UFUNCTION(BlueprintCallable)
	void GameResume();

	UFUNCTION(BlueprintCallable)
	bool IsInState(EEnumInGameLevelState GameState);

	void SetPlayerControllerPause(bool isPause);
};
