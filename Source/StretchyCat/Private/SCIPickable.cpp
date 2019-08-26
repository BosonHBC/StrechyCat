// Fill out your copyright notice in the Description page of Project Settings.

#include "SCIPickable.h"
#include "SCCharacterBase.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
ASCIPickable::ASCIPickable()
{
	PrimaryActorTick.bCanEverTick = true;

	//SetReplicateMovement(true);
}

void ASCIPickable::DoInteraction(class ASCCharacterBase* ownActor)
{
	Super::DoInteraction(ownActor);
	
	
}

void ASCIPickable::CancelInteraction()
{
	Super::CancelInteraction();


}

void ASCIPickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && PickPointSceneComp) {
		SetActorLocationAndRotation(PickPointSceneComp->GetComponentLocation() + PickPointSceneComp->GetForwardVector() * 40.f, PickPointSceneComp->GetComponentRotation());
	}
}

void ASCIPickable::ServerDoInteraction_Implementation(class ASCCharacterBase* ownActor)
{
	PickPointSceneComp = ownActor->GetInteractionPoint();
	bHolding = true;
	UE_LOG(LogTemp, Log, TEXT( "Server Set replicate"));
	MulticastDoInteraction(ownActor);
	SetReplicateMovement(false);

}

void ASCIPickable::ServerCancelInteraction_Implementation()
{
	bHolding = false;
	MulticastCancelInteraction();
}


void ASCIPickable::MulticastDoInteraction_Implementation(class ASCCharacterBase* ownActor)
{

	SuperMesh->SetEnableGravity(false);
	UE_LOG(LogTemp, Log, TEXT("Multicast interaction"));
}

void ASCIPickable::MulticastCancelInteraction_Implementation()
{
	SuperMesh->SetEnableGravity(true);
	SetReplicateMovement(true);
}

void ASCIPickable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASCIPickable, bHolding);
	DOREPLIFETIME(ASCIPickable, PickPointSceneComp);
}