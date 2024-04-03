// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WebGameMode.generated.h"

UCLASS(minimalapi)
class AWebGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	//void HandleStartingNewPlayer(APlayerController * NewPlayer) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
public:
	AWebGameMode();

	TSubclassOf<APawn> PawnClass1;
	TSubclassOf<APawn> PawnClass2;
};



