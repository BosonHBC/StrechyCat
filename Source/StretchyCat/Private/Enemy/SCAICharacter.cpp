// Fill out your copyright notice in the Description page of Project Settings.


#include "SCAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIModule/Classes/AIController.h"
#include "Components/SphereComponent.h"
#include "SCCharacterBase.h"
// Sets default values
ASCAICharacter::ASCAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASCAICharacter::OnHit);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ASCAICharacter::OnNotHit);
	// invisible
	PawnSeningComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));


	SetReplicateMovement(true);
	SetReplicates(true);

}

// Called when the game starts or when spawned
void ASCAICharacter::BeginPlay()
{
	Super::BeginPlay();
	PawnSeningComp->OnSeePawn.AddDynamic(this, &ASCAICharacter::OnPawnSeen);

	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();

}

// Called every frame
void ASCAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (detectCD > 0) {
		detectCD -= DeltaTime;
	}
	else
	{
		detectCD = 0;
	}
}

void ASCAICharacter::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this) {
		UE_LOG(LogTemp, Log, TEXT("Hook Hit %s"), *OtherActor->GetName());
		ASCCharacterBase* myChar = Cast<ASCCharacterBase>(OtherActor);
		if (myChar) {
			// this is an actor
			myChar->TakeDamage(this, 1);
			ResetAI();
		}
	}
}
void ASCAICharacter::OnPawnSeen(APawn* Pawn)
{
	if (Pawn == nullptr) return;
	ASCCharacterBase* myChar = Cast<ASCCharacterBase>(Pawn);
	if (myChar) {
		MoveToActor(myChar);
	}
}

void ASCAICharacter::MoveToLocation(FVector _Location)
{
	AAIController* atCtrl = Cast<AAIController>(GetController());
	atCtrl->MoveToLocation(_Location, 10.f);

}

void ASCAICharacter::MoveToActor(AActor* _destActor)
{
	if (_destActor) {
		AAIController* atCtrl = Cast<AAIController>(GetController());
		//atCtrl->MoveToActor(_destActor, 10.f);
		FAIMoveRequest AIMoveResquest;
		AIMoveResquest.SetGoalActor(_destActor);
		atCtrl->MoveTo(AIMoveResquest);
	}
}

void ASCAICharacter::ResetAI()
{
	// Go back to patrol point
	bDetecting = false;
	detectCD = 3;
	MoveToLocation(InitialLocation);
}

void ASCAICharacter::OnNotHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


