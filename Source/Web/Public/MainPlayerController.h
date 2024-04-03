// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WEB_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/* Constructor */
	AMainPlayerController(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }

protected:

	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn();

	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

};
