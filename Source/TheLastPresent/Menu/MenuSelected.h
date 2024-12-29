// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSelected.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EMenuSelected : uint8
{
	None				UMETA(DisplayName = "None"),
	MainMenu			UMETA(DisplayName = "MainMenu"),
	PauseMenu			UMETA(DisplayName = "PauseMenu"),
	SettingMenu			UMETA(DisplayName = "SettingMenu"),
	LeaderboardMenu		UMETA(DisplayName = "LeaderboardMenu"),
};
