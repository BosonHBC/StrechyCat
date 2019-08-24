// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
#include "Components/StaticMeshComponent.h"
#include "SCGameState.h"
#include "ObjectiveItemBase.h"
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
	TotalObjectives = 0;
	PlayerSpawnLocation = FVector(0.0f, 0.0f, 0.0f);

	//add default event
	OnCompleteRoom.BindUFunction(this, TEXT("OnRoomComplete"));
}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();
	if (Role == ROLE_Authority)
	{
		TArray<AActor *> children;
		GetAllChildActors(children);
		UE_LOG(LogTemp, Warning, TEXT("Children count %d"), children.Num())
			for (auto child : children)
			{
				auto castto = Cast<AObjectiveItemBase>(child);
				if (castto)
					AllObjectives.Add(castto);
			}
		TotalObjectives = AllObjectives.Num();
	}
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

	DOREPLIFETIME(ABaseRoom, TotalObjectives);
	DOREPLIFETIME(ABaseRoom, CurrentObjectiveCount);
	DOREPLIFETIME(ABaseRoom, IsRoomCompleted);
	DOREPLIFETIME(ABaseRoom, AllObjectives);
}

