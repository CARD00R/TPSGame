// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TPSCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UTPSAnimInst;
class UCharacterMovementComponent;

// Character Enum States
UENUM(BlueprintType)
enum class EParentStance : uint8
{
	Eps_Standing UMETA(DisplayName = "Standing"),
	Eps_Crouching UMETA(DisplayName = "Crouching"),
	Eps_InAir UMETA(DisplayName = "InAir"),
	//Eps_Dead UMETA(DisplayName = "Dead"),
	Eps_Max UMETA(DisplayName = "DefaultMax")
};

/*
ARCHIVED STANDING & CROUCHING STANCES
UENUM(BlueprintType)
enum class EStandingStance : uint8
{
	Ess_StandingIdle UMETA(DisplayName = "StandingIdle"),
	Ess_StandingJog UMETA(DisplayName = "StandingJog"),
	Ess_StandingSprint UMETA(DisplayName = "StandingSprint"),
	Ess_Max UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class ECrouchingStance : uint8
{
	Ecs_CrouchingIdle UMETA(DisplayName = "CrouchingIdle"),
	Ecs_CrouchingWalk UMETA(DisplayName = "CrouchingWalk"),
	Ecs_Max UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EAirStance : uint8
{
	Eas_Jumping UMETA(DisplayName = "Jumping"),
	Eas_Falling UMETA(DisplayName = "Falling"),
	Eas_Landing UMETA(DisplayName = "Landing"),
	Eas_Max UMETA(DisplayName = "DefaultMax")
};*/

UCLASS()
class TPSGAME_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	// Character Parent State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character States")
	EParentStance ParentStance;
	UFUNCTION(BlueprintCallable, Category = "Character States")
	void SetParentStance(EParentStance aStatus);
	EParentStance GetParentStance();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComp; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComp;

	// Character Movement
	UCharacterMovementComponent* CharacterMovementComp;
	void SetMaxWalkSpeed(const float aSpeed);
	UPROPERTY(EditDefaultsOnly, Category = "Character Movement")
	float StandJogSpeed = 500.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Character Movement")
	float CrouchWalkSpeed = 300.0f;
	
	// Input
	// Stores Action Mappings for binding
	UPROPERTY(EditDefaultsOnly,Category = Input)
	UInputMappingContext* TPSContext;
	// Action Mappings (Key Inputs)
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveAction; 
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* CrouchAction;
	// Input functions
	void Move(const FInputActionValue& aValue);
	void Look(const FInputActionValue& aValue);
	void TPSJump();
	void TPSCrouch();
	void Stand();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
};
