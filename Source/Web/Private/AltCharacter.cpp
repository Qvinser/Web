// Fill out your copyright notice in the Description page of Project Settings.


#include "AltCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAltCharacter::AAltCharacter()
{
}

void AAltCharacter::BeginPlay()
{
	Super::BeginPlay();
	ServerSetMovement();
}

void AAltCharacter::MoveRight(float axis)
{
	if ((Controller!=NULL) && (axis!=0.0f))
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			//return;
		}
		const FRotator absoluteRotator = (FRotator(0.0f, 1.0f,0.0f));
		const FVector absoluteDirection = FRotationMatrix(absoluteRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(absoluteDirection, axis);
	}
}

void AAltCharacter::MoveUp(float axis)
{
	if ((Controller!=NULL) && (axis!=0.0f))
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			//return;
		}
		const FRotator absoluteRotator = (FRotator(0, 0, 1.0f));
		FVector absoluteDirection = FRotationMatrix(absoluteRotator).GetUnitAxis(EAxis::Z);
		absoluteDirection[0] = axis>=0 ? -10e-5 : 10e-5;
		absoluteDirection[1] = 0.0f;
		AddMovementInput(absoluteDirection, axis);
	}
}

void AAltCharacter::ServerSetMovement_Implementation()
{
	Super::ServerSetMovement_Implementation();
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
}

void AAltCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAltCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AAltCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Move Up / Down", this, &AAltCharacter::MoveUp);
}
