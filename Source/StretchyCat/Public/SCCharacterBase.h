// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCCharacterBase.generated.h"


UCLASS()
class STRETCHYCAT_API ASCCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCCharacterBase();
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCameraComp;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USceneComponent* InteractionPoint;

	virtual void UseAbility();
	virtual void UnUseAbility();
	void MoveForward(float _value);
	void MoveRight(float _value);
	void TurnAtRate(float _value);
	void LookUpAtRate(float _value);
	void Jump();

	virtual void TakeDamage(int _dmg);

	virtual void Interact();

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		class ASCInteractableBase* InteractingActor;

	bool bInteracting;

	FCollisionQueryParams CollisionParams;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USceneComponent* GetInteractionPoint() const { return InteractionPoint; };
};
