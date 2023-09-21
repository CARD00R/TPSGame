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

UENUM(BlueprintType)
enum class EStanceStatus : uint8
{
	Ess_StandIdling UMETA(DisplayName = "StandIdling"),
	Ess_StandJogging UMETA(DisplayName = "StandJogging"),
	Ess_StandSprinting UMETA(DisplayName = "StandSprinting"),
	Ess_Jumping UMETA(DisplayName = "Jumping"),
	Ess_CrouchIdling UMETA(DisplayName = "CrouchIdling"),
	Ess_CrouchWalking UMETA(DisplayName = "CrouchWalking"),
	Ess_CrouchSprinting UMETA(DisplayName = "CrouchSprinting"),
	Ess_InAirFalling UMETA(DisplayName = "InAirFalling"),
	Ess_Landing UMETA(DisplayName = "Landing"),
	Ess_Max UMETA(DisplayName = "DefaultMax")
};


UCLASS()
class TPSGAME_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	// Character State Enums
	// Parent Stance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character States")
	EParentStance ParentStance;
	UFUNCTION(BlueprintCallable, Category = "Character States")
	void SetParentStanceStatus(EParentStance aStatus);
	EParentStance GetParentStanceStatus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComp; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArmComp; 
	
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
	void Jump();
	void Crouch();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
