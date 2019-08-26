// Fill out your copyright notice in the Description page of Project Settings.


#include "SCAIEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
// Sets default values
ASCAIEnemy::ASCAIEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapComp"));
	RootComponent = CapComp;
	CapComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CapComp->OnComponentBeginOverlap.AddDynamic(this, &ASCAIEnemy::OnHit);

	SuperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpuerMesh"));
	SuperMesh->SetupAttachment(CapComp);
	SuperMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SuperMesh->SetRelativeRotation(FRotator(0,-90,0));

	// invisible
	MovementComp = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharaMovement"));
	MovementComp->UpdatedComponent = CapComp;
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
}
