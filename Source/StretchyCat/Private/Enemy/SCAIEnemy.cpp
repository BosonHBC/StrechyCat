// Fill out your copyright notice in the Description page of Project Settings.


#include "SCAIEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIModule/Classes/AIController.h"
// Sets default values
ASCAIEnemy::ASCAIEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = SuperMesh;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASCAIEnemy::OnHit);

	// invisible
	PawnSeningComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	
}

// Called when the game starts or when spawned
void ASCAIEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASCAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASCAIEnemy::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this) {
		UE_LOG(LogTemp, Log, TEXT("Hit %s"), *OtherActor->GetName());
		AAIController* atCtrl = Cast<AAIController>(GetController());
		//atCtrl->MoveToLocation(FVector(140, -350, 230));

	//	atCtrl
	}
}
