// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebGameMode.h"
#include "MainPlayerController.h"
#include "HumanCharacter.h"
#include "AltCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWebGameMode::AWebGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SecondPerson/Blueprints/Characters/BPHuman"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SecondPerson/Blueprints/Characters/BP_male_character"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("/Game/SecondPerson/Blueprints/Characters/BPGhost"));
	PawnClass1 = PlayerPawnBPClass.Class;
	PawnClass2 = PlayerPawnBPClass2.Class;
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PawnClass1;
	}
	PlayerControllerClass  = AMainPlayerController::StaticClass();
}

UClass* AWebGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	int numPlayers = GetNumPlayers();
	if (numPlayers<=1)
	{
		if (PawnClass1 != NULL)
		{
			return PawnClass1;
		}
	}
	else
	{
		if (PawnClass2 != NULL)
		{
			return PawnClass2;
		}
	}
	return DefaultPawnClass;
}
