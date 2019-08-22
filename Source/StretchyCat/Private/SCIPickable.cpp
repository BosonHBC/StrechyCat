// Fill out your copyright notice in the Description page of Project Settings.

#include "SCIPickable.h"
#include "SCCharacterBase.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ASCIPickable::ASCIPickable()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	RootComponent = BoxComp;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SuperMesh->SetupAttachment(BoxComp);
}

void ASCIPickable::DoInteraction(class ASCCharacterBase* ownActor)
{
	Super::DoInteraction(ownActor);
	PickPointSceneComp = ownActor->GetInteractionPoint();
	bHolding = true;
	
	BoxComp->SetEnableGravity(false);
}

void ASCIPickable::CancelInteraction()
{
	Super::CancelInteraction();
	bHolding = false;
	BoxComp->SetEnableGravity(true);
}

void ASCIPickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && PickPointSceneComp) {
		SetActorLocationAndRotation(PickPointSceneComp->GetComponentLocation() + PickPointSceneComp->GetForwardVector() * 40.f, PickPointSceneComp->GetComponentRotation());
	}
}
