// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLastPresentGameMode.h"
#include "TheLastPresentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheLastPresentGameMode::ATheLastPresentGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
