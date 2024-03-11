// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class WEB_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float walkSpeed = 450.0f;
	float runSpeed = 750.0f;
	float dashSpeed = 1050.0f;
	bool bDead;
	bool dashed;
	bool running;
	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class  USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class  UCameraComponent* FollowCamera;
	virtual void Tick(float DeltaTime) override;
	void MoveRight(float axis);
	virtual void Jump() override;
	virtual void StopJumping() override;
	void Dash();
	void StopDashing();
	void Run() const;
	void StopRunning();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

