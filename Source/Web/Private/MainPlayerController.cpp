// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

AMainPlayerController::AMainPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Make sure the PawnClass is Replicated */
	bReplicates = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ServerSetPawn();
}

bool AMainPlayerController::ServerSetPawn_Validate()
{
	return true;
}

void AMainPlayerController::ServerSetPawn_Implementation()
{
	MyPawnClass = GetWorld()->GetAuthGameMode()->GetDefaultPawnClassForController(this);

	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

// Replication
void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMainPlayerController, MyPawnClass);
}