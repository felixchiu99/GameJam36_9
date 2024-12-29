// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NpcPreference.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class ENpcPreference : uint8
{
	None				UMETA(DisplayName = "None"),
	Money				UMETA(DisplayName = "Money"),
	Usefulness			UMETA(DisplayName = "Usefulness"),
	Looks				UMETA(DisplayName = "Looks"),
};
