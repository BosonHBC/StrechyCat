// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
#include "Components/StaticMeshComponent.h"
#include "SCGameState.h"
#include <Net/UnrealNetwork.h>
// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoomFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomFloor"));
	RootComponent = RoomFloor;
	SetReplicates(true);
	IsRoomCompleted = false;
	CurrentObjectiveCount = 0;
	TotalObjectives = 2;
}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseRoom::EnterTheRoom()
{
}

void ABaseRoom::LeaveTheRoom()
{
}

// Called every frame
void ABaseRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseRoom::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ABaseRoom, TotalObjectives, COND_InitialOnly);
	DOREPLIFETIME(ABaseRoom, CurrentObjectiveCount);
	DOREPLIFETIME(ABaseRoom, IsRoomCompleted);
}

