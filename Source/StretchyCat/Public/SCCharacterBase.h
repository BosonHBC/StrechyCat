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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* InteractCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* DeathCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* DamageCue;

	bool GetCarryingActor() const { return bCarryingActor; }
	void SetCarryingActor(bool val) { bCarryingActor = val; }
	USceneComponent* GetInteractionPoint() const { return InteractionPoint; };
	bool Invincible() const { return bInvincible; }
	FVector SpawnLocation;
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
	 UFUNCTION(Server, Reliable, WithValidation)
		 virtual void ServerUseAbility();

	 virtual void UnUseAbility();
	 UFUNCTION(Server, Reliable, WithValidation)
		 virtual void ServerUnUseAbility();

	void MoveForward(float _value);
	void MoveRight(float _value);
	void TurnAtRate(float _value);
	void LookUpAtRate(float _value);
	void Jump();


	virtual void Interact();
	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerInteract();
	virtual void UnInteract();
	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerUnInteract();

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
		class ASCInteractableBase* InteractingActor;
	UPROPERTY(BlueprintReadWrite , Category = "Gameplay")
		float InvinceTime;

	FTimerHandle InvinceTimeHandle;
	void OnInvinceTimeOver();

	bool bInteracting;
	bool bCarryingActor;
	FCollisionQueryParams CollisionParams;

	//UPROPERTY(EditDefaultsOnly)
	//	class UMaterial* NormalMaterial;
	//UPROPERTY(EditDefaultsOnly)
	//	class UMaterial* InvinceMaterial;


	void StartInvincible(AActor* DmgFrom);
	// invincible 
	UPROPERTY(Replicated)
	bool bInvincible;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(AActor* DmgFrom, int _dmg);

	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnTakeDamage(AActor* DmgFrom);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRespawn();

	void Respawn(const FVector& _other);

	class UAudioComponent* AudioComponent;
};
