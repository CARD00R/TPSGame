// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSAnimInst.generated.h"

class APawn;
class ATPSCharacter;
class ATPSAnimInst;

UCLASS()
class TPSGAME_API UTPSAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override; 
	// Movement Speeds
	UPROPERTY(BlueprintReadOnly, Category = "Physics")
	float CharacterSpeed = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Physics")
	float CharacterDirection = 0;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	APawn* TPSPawn;
	
	UPROPERTY(BlueprintReadOnly, Category = "Component")
	ATPSCharacter* TPSCharacter;

private:
	
};
