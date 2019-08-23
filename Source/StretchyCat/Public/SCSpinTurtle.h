// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCCharacterBase.h"
#include "SCSpinTurtle.generated.h"

/**
 * 
 */
UCLASS()
class STRETCHYCAT_API ASCSpinTurtle : public ASCCharacterBase
{
	GENERATED_BODY()
public:
	ASCSpinTurtle();

protected:
	void UseAbility() override;
	void UnUseAbility() override;
	void Interact() override;
	
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityPressed;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityReleased;
};
