// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSAnimInst.h"
#include "Player/TPSCharacter.h"
#include "KismetAnimationLibrary.h"
#include "Math/Vector.h"

void UTPSAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if(!TPSPawn)
	{
		TPSPawn = TryGetPawnOwner();
	}
}

void UTPSAnimInst::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if(!TPSPawn)
	{
		TPSPawn = TryGetPawnOwner();
	}
	else
	{
		TPSCharacter = Cast<ATPSCharacter>(TPSPawn);
		
		// Determine if character is moving backwards
		BackwardsCheck = FVector::DotProduct(TPSCharacter->GetActorForwardVector(),TPSCharacter->GetVelocity());

		// Calculate Movement speed
		CharacterSpeed = TPSPawn->GetVelocity().Length();
		// Is character moving backwards, with backwards buffer velocity of -30cm/s
		if(BackwardsCheck<-30.0f)
			CharacterSpeed*=-1.0f;

		// Calculate Character direction
		CharacterDirection = UKismetAnimationLibrary::CalculateDirection(TPSPawn->GetVelocity(),TPSPawn->GetActorRotation());
		// A forced reset to direction -180 as the player approaches full directional circle
		if(CharacterDirection > 150.0f && CharacterSpeed < 0)
			CharacterDirection*=-1.0f;
		
		
	}
}
