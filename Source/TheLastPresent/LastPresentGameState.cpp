// Fill out your copyright notice in the Description page of Project Settings.


#include "LastPresentGameState.h"
#include "GameState/EnumInGameLevelState.h"

void ALastPresentGameState::BeginPlay()
{
	Super::BeginPlay();
	GameStart();
}

void ALastPresentGameState::StartTimer()
{
	timeStart = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
	timeEnd = -1.0f;
}

float ALastPresentGameState::GetMillisecondElapsed()
{
	float elapsed;
	if (HasGameEnded == false) {
		elapsed = (FPlatformTime::ToMilliseconds(FPlatformTime::Cycles()) - timeStart);
	}
	else {
		elapsed = (timeEnd - timeStart);
	}

	if (elapsed < 0) {
		elapsed = 100000000000000;
	}

	return elapsed;
}

void ALastPresentGameState::EndTimer()
{
	timeEnd = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
}

void ALastPresentGameState::GameStart()
{
	SetPlayerControllerPause(false);
	GameLevelState = EEnumInGameLevelState::GameOngoing;
	HasGameStarted = true;
	HasGameEnded = false;
	StartTimer();
}

void ALastPresentGameState::GoalReached_Implementation()
{
	GameLevelState = EEnumInGameLevelState::GameEnded;
	EndTimer();
	HasGameEnded = true;
	SetPlayerControllerPause(true);
}

void ALastPresentGameState::GamePause()
{
	SetPlayerControllerPause(true);
	GameLevelState = EEnumInGameLevelState::GamePaused;
}

void ALastPresentGameState::GameResume()
{
	
	SetPlayerControllerPause(false);
	GameLevelState = EEnumInGameLevelState::GameOngoing;
}

bool ALastPresentGameState::IsInState(EEnumInGameLevelState GameState)
{
	return GameState == GameLevelState;
}

void ALastPresentGameState::SetPlayerControllerPause(bool isPause)
{
	UGameInstance* const GameInstance = GetGameInstance();
	APlayerController* const PC = GameInstance ? GameInstance->GetFirstLocalPlayerController() : nullptr;
	if (PC) {
		PC->SetPause(isPause);
	}
}
