// Fill out your copyright notice in the Description page of Project Settings.


#include "SCExitDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SCCharacterBase.h"
#include "StretchyCatGameMode.h"
// Sets default values
ASCExitDoor::ASCExitDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = DoorMesh;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASCExitDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCExitDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


