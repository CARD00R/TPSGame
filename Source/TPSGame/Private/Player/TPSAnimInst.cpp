// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSAnimInst.h"
#include "Player/TPSCharacter.h"
#include "KismetAnimationLibrary.h"

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
		
		//Calculate Movement Speed & Direction
		CharacterSpeed = TPSPawn->GetVelocity().Length();
		CharacterDirection = UKismetAnimationLibrary::CalculateDirection(TPSPawn->GetVelocity(),TPSPawn->GetActorRotation());
	}
}
