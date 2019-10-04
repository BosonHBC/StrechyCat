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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* SpinningCue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class USceneComponent* RotateParentComp;


protected:
	void ServerUseAbility_Implementation() override;
	bool ServerUseAbility_Validate() override;
	void ServerUnUseAbility_Implementation() override;
	bool ServerUnUseAbility_Validate() override;


	void Interact() override;
	
	void RecoverRotation();


	float currentRotateRadSpeed;
	UPROPERTY(Replicated)
	bool bRecovering;

	UFUNCTION(NetMulticast, Reliable)
		void MulticastSetInitialRadSpeed();

	virtual void BeginPlay() override;
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityPressed;
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
		bool bAbilityReleased;

	UPROPERTY( BlueprintReadOnly, Replicated,Category = Gameplay)
		bool bRotating;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	float RotateRadSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		float RotateRadSpeedDamping;

	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE bool GetRecovering() const { return bRecovering; }
};
