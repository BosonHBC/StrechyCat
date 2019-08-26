// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SCAIEnemy.generated.h"

UCLASS()
class STRETCHYCAT_API ASCAIEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASCAIEnemy();


protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		class UStaticMeshComponent* SuperMesh;
	UPROPERTY(Edi, Category = Components)
		class USphereComponent* SphereComp;


	UPROPERTY(VisibleAnywhere, Category = Components)
		class UPawnSensingComponent* PawnSeningComp;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
