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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class USceneComponent* RotateParentComp;


protected:
	void UseAbility() override;
	void UnUseAbility() override;
	void Interact() override;
	
	void RecoverRotation();

	float currentRotateRadSpeed;
	bool bRecovering;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityPressed;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityReleased;

	UPROPERTY( BlueprintReadOnly, Category = Gameplay)
		bool bRotating;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	float RotateRadSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		float RotateRadSpeedDamping;
};
