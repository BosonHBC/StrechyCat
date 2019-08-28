// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle/SCBulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SCCharacterBase.h"
#include "SCSpinTurtle.h"
#include "SCAICharacter.h"
// Sets default values
ASCBulletProjectile::ASCBulletProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	//CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASCBulletProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 2.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASCBulletProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ASCBulletProjectile::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCCharacterBase* Base = Cast< ASCCharacterBase>(OtherActor);
		if (Base)
		{
			ASCSpinTurtle* Turtle = Cast<ASCSpinTurtle>(Base);
			if (Turtle) {
				if (Turtle->bRotating) {
					// Deflecting

				}
				else {
					// Damage Turtle
					if (!Turtle->Invincible())
						Turtle->TakeDamage(this, 1);
					Destroy();
				}
			}
			// Not a Turtle
			else {
				// Damage Character
				if (!Base->Invincible())
					Base->TakeDamage(this, 1);
				Destroy();
			}
		}
		else {
			ASCAICharacter* AIBase = Cast<ASCAICharacter>(OtherActor);

			if (AIBase) {
				AIBase->KillMyself();
			}
			Destroy();
		}
	}
}


