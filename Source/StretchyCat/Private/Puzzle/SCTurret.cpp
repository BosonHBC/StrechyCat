// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle/SCTurret.h"
#include "Engine/World.h"
#include "Puzzle/SCBulletProjectile.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
ASCTurret::ASCTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	SpawnLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	SpawnLocationComp->SetupAttachment(MeshComp);

	ShootingInterval = 0.2f;
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

void ASCTurret::FireProjetile()
{
	UWorld* const World = GetWorld();
	if (World) {
		UE_LOG(LogTemp, Log, TEXT("Fire!"));
		const FVector SpawnLocation = ((SpawnLocationComp != nullptr) ? SpawnLocationComp->GetComponentLocation() : GetActorLocation());

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		World->SpawnActor<ASCBulletProjectile>(ProjectileClass, SpawnLocation, SpawnLocationComp->GetComponentRotation(), ActorSpawnParams);

	}

}

void ASCTurret::ToggleShooting(bool _enable)
{
	if (_enable) {
		bCanSpawnProjectile = true;
		// Start timer
		GetWorldTimerManager().SetTimer(shootingTimeHandle, this, &ASCTurret::FireProjetile, ShootingInterval, true, 0.5f);
	}
	else {
		bCanSpawnProjectile = false;
		// disable timer
		GetWorldTimerManager().ClearTimer(shootingTimeHandle);
	}
}

