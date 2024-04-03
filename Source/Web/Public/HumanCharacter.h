// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "HumanCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WEB_API AHumanCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AHumanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float dashSpeed = 1050.0f;
	bool dashed;
	
	void MoveRight(float axis);
	virtual void Jump() override;
	virtual void StopJumping() override;
	UFUNCTION(Server, Reliable)
	void Dash_Server();
	UFUNCTION(NetMulticast, Reliable)
	void Dash_Client();
	UFUNCTION(Server, Reliable)
	void StopDashing_Server();
	UFUNCTION(NetMulticast, Reliable)
	void StopDashing_Client();
	
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void ServerSetMovement_Implementation() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
