// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "AltCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WEB_API AAltCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAltCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void MoveRight(float axis);
	void MoveUp(float axis);
	virtual void ServerSetMovement_Implementation() override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
