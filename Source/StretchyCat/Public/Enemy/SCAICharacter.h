// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCAICharacter.generated.h"

UCLASS()
class STRETCHYCAT_API ASCAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCAICharacter();

	bool bHitSCCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class UPawnSensingComponent* PawnSeningComp;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnNotHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnSeenPawn(APawn* Pawn);

	bool bDetecting;
	float detectCD;


	void ResetAI() {
		// Go back to patrol point
		bDetecting = false;
		detectCD = 3;
	}
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
