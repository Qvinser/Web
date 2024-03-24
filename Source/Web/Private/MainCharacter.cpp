// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 5000.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->FieldOfView = 15.0f;
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	//GetCharacterMovement()->bUseControllerDesiredRotation =true;
	//GetCharacterMovement()->RotationRate=FRotator(0.0f, 0.0f,  0.0f);
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10000.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.6f;
	//GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	GetCharacterMovement()->SetWalkableFloorAngle(60);

	GetCharacterMovement()->bConstrainToPlane = true;
	
	bDead=false;
	dashed=false;
	running=false;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller!=NULL && dashed==true)
	{
		const FRotator Rotator = this->GetActorRotation();
		const FRotator YawRotator(0.0f, Rotator.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, 1.0f);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::Dash_Server);
	//PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMainCharacter::StopRunning);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMainCharacter::MoveRight);
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

void AMainCharacter::MoveRight(float axis)
{
	if ((Controller!=NULL) && (axis!=0.0f))
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			//return;
		}
		// SetActorRotation(FRotator(0.0f, axis>=0 ? 90.0f : -90.0f,0.0f));
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YawRotator(0.0f, Rotator.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, axis);
	}
	
}

void AMainCharacter::Jump()
{
	Super::Jump();
	if ((Controller!=NULL))
	{
		ACharacter::Jump();
	}
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
	if ((Controller!=NULL))
	{
		ACharacter::StopJumping();
	}
}
void AMainCharacter::Dash_Server_Implementation()
{
	dashed = true;
	Dash_Client();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AMainCharacter::StopDashing_Server, 0.1f, false);
}
void AMainCharacter::Dash_Client_Implementation()
{
	if (Controller!=NULL && dashed==true)
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

void AMainCharacter::StopDashing_Server_Implementation()
{
	dashed=false;
	StopDashing_Client();
}
void AMainCharacter::StopDashing_Client_Implementation()
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

void AMainCharacter::Run() const
{
	if (Controller!=NULL)
	{
		if (running==true)GetCharacterMovement()->MaxWalkSpeed=runSpeed;
		else GetCharacterMovement()->MaxWalkSpeed=runSpeed;
	}
}

void AMainCharacter::StopRunning()
{
	if (Controller!=NULL)
	{
		running=false;
		if (!dashed)GetCharacterMovement()->MaxWalkSpeed=walkSpeed;
	}
}
