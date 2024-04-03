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
	bool bDead;
	
	// Called every frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class  USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class  UCameraComponent* FollowCamera;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetMovement();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

