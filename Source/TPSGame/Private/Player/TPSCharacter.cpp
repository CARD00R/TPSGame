// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSCharacter.h"
//Enhanced Input Subsystem
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  Can be turned off to improve performance
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller)) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TPSContext, 0);
		}
	}
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


#pragma region CHARACTER INPUT
// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Jump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Crouch);
	}
}

// moving forward/backward and left/right
void ATPSCharacter::Move(const FInputActionValue& aValue)
{
	const FVector2d MovementVector = aValue.Get<FVector2D>();

	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementVector.X);
}

// looking up/down and left/right
void ATPSCharacter::Look(const FInputActionValue& aValue)
{
	const FVector2d LookAxisVector = aValue.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ATPSCharacter::Jump()
{
	// Complete Jump Checks here
	SetParentStanceStatus(EParentStance::Eps_Standing);
	UE_LOG(LogTemp, Warning, TEXT("Jumping"));
}

void ATPSCharacter::Crouch()
{
	// Complete Crouch Checks here
	SetParentStanceStatus(EParentStance::Eps_Crouching);
	UE_LOG(LogTemp, Warning, TEXT("Crouching"));
}
#pragma endregion 

// Setter
void ATPSCharacter::SetParentStanceStatus(EParentStance aStatus)
{
	ParentStance = aStatus;
}
//Getter
EParentStance ATPSCharacter::GetParentStanceStatus()
{
	return ParentStance;
}
