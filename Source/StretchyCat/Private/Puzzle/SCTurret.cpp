// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle/SCTurret.h"
#include "Engine/World.h"
#include "Puzzle/SCBulletProjectile.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
// Sets default values
ASCTurret::ASCTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapComp"));
	RootComponent = CapComp;
	SpawnLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	SpawnLocationComp->SetupAttachment(CapComp);

	ShootingInterval = 0.2f;
	BulletSpawnLifeTime = 2.f;
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASCTurret::BeginPlay()
{
	Super::BeginPlay();
	ToggleShooting(true);
}

// Called every frame
void ASCTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASCTurret::MulticastFireProjetile_Implementation()
{

	if (ProjectileClass) {
		const FVector SpawnLocation = ((SpawnLocationComp != nullptr) ? SpawnLocationComp->GetComponentLocation() : GetActorLocation());

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		ASCBulletProjectile* projtile = GetWorld()->SpawnActor<ASCBulletProjectile>(ProjectileClass, SpawnLocation, SpawnLocationComp->GetComponentRotation(), ActorSpawnParams);
		if (projtile) {
			projtile->InitialLifeSpan = BulletSpawnLifeTime;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null projetile ref"));
		}
	}

}

void ASCTurret::ToggleShooting(bool _enable)
{
	if (Role == ROLE_Authority) {
		if (_enable) {
			bCanSpawnProjectile = true;
			// Start timer
			GetWorldTimerManager().SetTimer(shootingTimeHandle, this, &ASCTurret::MulticastFireProjetile, ShootingInterval, true, 0.5f);
		}
		else {
			bCanSpawnProjectile = false;
			// disable timer
			GetWorldTimerManager().ClearTimer(shootingTimeHandle);
		}
	}

}

