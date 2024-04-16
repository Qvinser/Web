// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AHumanCharacter::AHumanCharacter()
{
}

void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
	bDashed = false;
	ServerSetMovement();
}

void AHumanCharacter::MoveRight(float axis)
{
	if ((Controller!=NULL) && (axis!=0.0f))
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			//return;
		}
		const FRotator absoluteRotator = (FRotator(0, 1.0f,0));
		FVector absoluteDirection = FRotationMatrix(absoluteRotator).GetUnitAxis(EAxis::Y);
		absoluteDirection.X = axis < 0 ? 10e-5 : -10e-5;
		//const FRotator Rotator = Controller->GetControlRotation();
		//const FRotator YawRotator(0.0f, Rotator.Yaw, 0.0f);
		//const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(absoluteDirection, axis);
	}
	
}

void AHumanCharacter::Jump()
{
	Super::Jump();
	if ((Controller!=NULL))
	{
		ACharacter::Jump();
	}
}

void AHumanCharacter::StopJumping()
{
	Super::StopJumping();
	if ((Controller!=NULL))
	{
		ACharacter::StopJumping();
	}
}
void AHumanCharacter::Dash_Server_Implementation()
{
	bDashed = true;
	Dash_Client();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AHumanCharacter::StopDashing_Server, 0.1f, false);
}
void AHumanCharacter::Dash_Client_Implementation()
{
	if (Controller!=NULL && bDashed==true)
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			//return;
		}
		const FVector Rotator = GetActorForwardVector();

		GetCharacterMovement()->MaxWalkSpeed = dashSpeed;
		GetMovementComponent()->Velocity.Y = 2000 * Rotator.Y;
	}
}

void AHumanCharacter::StopDashing_Server_Implementation()
{
	bDashed=false;
	StopDashing_Client();
}
void AHumanCharacter::StopDashing_Client_Implementation()
{
	if (Controller!=NULL)
	{
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
		if (GetMovementComponent()->Velocity.Y > walkSpeed)
		{
			GetMovementComponent()->Velocity.Y = walkSpeed;
		}
		else if (GetMovementComponent()->Velocity.Y < -walkSpeed)
		{
			GetMovementComponent()->Velocity.Y = -walkSpeed;
		}
	}
}


/*void AMainCharacter::MoveForward(float axis)
{
	if ((Controller!=NULL) && (axis!=0.0f))
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			return;
		}
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YawRotator(0.0f, Rotator.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, axis);
	}
}*/

void AHumanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller!=NULL && bDashed==true)
	{
		const FRotator Rotator = this->GetActorRotation();
		const FRotator YawRotator(0.0f, Rotator.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 1.0f);
	}
}

void AHumanCharacter::ServerSetMovement_Implementation()
{
	Super::ServerSetMovement_Implementation();
}



void AHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHumanCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHumanCharacter::StopJumping);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AHumanCharacter::Dash_Server);
	//PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMainCharacter::StopRunning);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHumanCharacter::MoveRight);
}
