// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCTurret.generated.h"

UCLASS()
class STRETCHYCAT_API ASCTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCTurret();
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
		class UCapsuleComponent * CapComp;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TSubclassOf<class ASCBulletProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		bool bCanSpawnProjectile;
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		class USceneComponent* SpawnLocationComp;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		float ShootingInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class USoundCue* ShootCue;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle shootingTimeHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFireProjetile();

	void ToggleShooting(bool _enable);

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float BulletSpawnLifeTime;
};
