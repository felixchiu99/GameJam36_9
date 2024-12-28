// Fill out your copyright notice in the Description page of Project Settings.


#include "LastPresentGameState.h"

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
	return timeEnd == -1.0f ? (FPlatformTime::ToMilliseconds(FPlatformTime::Cycles()) - timeStart) : (timeEnd - timeStart);
}

void ALastPresentGameState::EndTimer()
{
	timeEnd = FPlatformTime::ToMilliseconds(FPlatformTime::Cycles());
}

void ALastPresentGameState::GameStart()
{
	HasGameStarted = true;
	HasGameEnded = false;
	StartTimer();
}

void ALastPresentGameState::GoalReached()
{
	EndTimer();
	HasGameEnded = true;
	
}
