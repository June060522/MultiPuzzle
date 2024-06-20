// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiPuzzleGameMode.h"
#include "MultiPuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiPuzzleGameMode::AMultiPuzzleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
