// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "WebGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WEB_API UWebGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Utilities")
	static bool HostSession(APlayerController* Player, FName SessionName, bool bIsLAN, int32 MaxNumPlayers);
};
