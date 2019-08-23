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
	BoxComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootComponent = BoxComp;
	SuperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	SuperMesh->SetupAttachment(BoxComp);
}

void ASCIPickable::DoInteraction(class ASCCharacterBase* ownActor)
{
	Super::DoInteraction(ownActor);
	PickPointSceneComp = ownActor->GetInteractionPoint();
	bHolding = true;
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Ignore);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComp->SetEnableGravity(false);
}

void ASCIPickable::CancelInteraction()
{
	Super::CancelInteraction();
	bHolding = false;
	BoxComp->SetEnableGravity(true);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void ASCIPickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && PickPointSceneComp) {
		SetActorLocationAndRotation(PickPointSceneComp->GetComponentLocation() + PickPointSceneComp->GetForwardVector() * 40.f, PickPointSceneComp->GetComponentRotation());
	}
}
