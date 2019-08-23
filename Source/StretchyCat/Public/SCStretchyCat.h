// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCCharacterBase.h"
#include "SCStretchyCat.generated.h"

/**
 * 
 */
UCLASS()
class STRETCHYCAT_API ASCStretchyCat : public ASCCharacterBase
{
	GENERATED_BODY()
public:
	// Default Constructor
	ASCStretchyCat();

protected:
	void UseAbility() override;
	void UnUseAbility() override;
	void Interact() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* ExtendBodyCapComp;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float MaxForwardExtendDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float BodyShootSpeed;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UBoxComponent* ExtendBodyComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float BaseImpulse;
private:
	FVector BodyLandedLcation;
	bool bBodyOutside;

	AActor* HeadHitActor;
	FVector HeadHitPoint;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LateFunction")
		void OnBodyBackToBody();
	UFUNCTION(BlueprintCallable, Category = "LateFunction")
		void OnBodyReachDest();

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		float PercentToEnd;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bAbilityPressed;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bAbilityReleased;
};
