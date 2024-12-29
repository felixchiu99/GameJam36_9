// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumInGameLevelState.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EEnumInGameLevelState : uint8
{
	GameOngoing  UMETA(DisplayName = "GameOngoing"),
	GamePaused  UMETA(DisplayName = "GamePaused"),
	GameEnded  UMETA(DisplayName = "GameEnded"),
};
