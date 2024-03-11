// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebGameMode.h"
#include "WebCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWebGameMode::AWebGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
