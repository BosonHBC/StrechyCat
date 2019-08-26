// Fill out your copyright notice in the Description page of Project Settings.

#include "SCInteractableBase.h"
#include "SCCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASCInteractableBase::ASCInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	RootComponent = SuperMesh;

	//SetReplicateMovement(true);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASCInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCInteractableBase::DoInteraction(ASCCharacterBase* ownActor)
{
	// Base Interaction
	UE_LOG(LogTemp, Log, TEXT("Interact by %s"), *ownActor->GetName());
}

void ASCInteractableBase::CancelInteraction()
{
	// Base Cancel Interaction
	UE_LOG(LogTemp, Log, TEXT("Cancel Interaction"));

}

void ASCInteractableBase::ServerCancelInteraction_Implementation()
{

}

bool ASCInteractableBase::ServerCancelInteraction_Validate()
{
	return true;
}

void ASCInteractableBase::ServerDoInteraction_Implementation(class ASCCharacterBase* ownActor)
{

}

bool ASCInteractableBase::ServerDoInteraction_Validate(class ASCCharacterBase* ownActor)
{
	return true;
}

