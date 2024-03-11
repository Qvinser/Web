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
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	//GetCharacterMovement()->bUseControllerDesiredRotation =true;
	//GetCharacterMovement()->RotationRate=FRotator(0.0f, 0.0f,  0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	
	//GetCharacterMovement()->AirControl = 0.6f;
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	GetCharacterMovement()->SetWalkableFloorAngle(60);
	
	bDead=false;
	dashed=false;
	running=false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetCharacterMovement()->Velocity[0]!=0)
	{
		GetCharacterMovement()->Velocity[0]=0;
	}
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
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::Dash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &AMainCharacter::StopRunning);

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
			return;
		}
		SetActorRotation(FRotator(0.0f, axis>=0 ? 90.0f : -90.0f,0.0f));
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

void AMainCharacter::Dash()
{
	if (Controller!=NULL && dashed==false)
	{
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			return;
		}
		const FVector Rotator = GetActorForwardVector();

		GetCharacterMovement()->MaxWalkSpeed = dashSpeed;
		GetMovementComponent()->Velocity.X = 2000.0f * Rotator.X;
		GetMovementComponent()->Velocity.Y = 2000.0f * Rotator.Y;
		//GetMovementComponent()->Velocity.Z = 100.0f;
		dashed = true;
		running=true;
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &AMainCharacter::StopDashing, 0.7f, false);
	}
}

void AMainCharacter::StopDashing()
{
	dashed=false;
	if (Controller!=NULL)
	{
		Run();
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
