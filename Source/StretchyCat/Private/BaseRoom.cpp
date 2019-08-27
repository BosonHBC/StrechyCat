// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
#include "Components/StaticMeshComponent.h"
#include "SCGameState.h"
#include "ObjectiveItemBase.h"
#include "SCCharacterBase.h"
#include "SCPlayerState.h"
#include "StretchyCatGameMode.h"
#include <Net/UnrealNetwork.h>
#include "Components/BoxComponent.h"
#include "SCBaseController.h"
// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	RoomFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomFloor"));
	RootComponent = RoomFloor;
	RoomVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomVolume"));
	RoomSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("CharacterSpawn"));
	RoomVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RoomVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	RoomVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RoomVolume->SetupAttachment(RoomFloor);
	RoomSpawn->SetupAttachment(RoomFloor);
	
	
	RoomVolume->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoom::EnterTheRoom);
	RoomVolume->OnComponentEndOverlap.AddDynamic(this, &ABaseRoom::LeaveTheRoom);

	//RoomVolume->SetIsReplicated(true);
	
	IsRoomCompleted = false;
	CurrentObjectiveCount = 0;
	TotalObjectives = 0;

	//add default event
	//OnCompleteRoom.BindUFunction(this, TEXT("OnRoomComplete"));
}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();
	if (Role == ROLE_Authority)
	{
		TArray<AActor *> children;
		GetAllChildActors(children);
		for (auto child : children)
		{
			auto castto = Cast<AObjectiveItemBase>(child);
			if (castto)
			{
				AllObjectives.Add(castto);
				castto->RoomAttached = this;
			}
		}
		TotalObjectives = AllObjectives.Num();
		UE_LOG(LogTemp, Warning, TEXT("Objective count %d"), TotalObjectives)
	}
	
}

void ABaseRoom::EnterTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCCharacterBase* character = Cast<ASCCharacterBase>(OtherActor);
		if (character && character->IsLocallyControlled())
		{
			auto pc = character->GetController<ASCBaseController>();
			if (pc)
			{
				pc->ChangeCurrentRoomName(RoomName);
				pc->ChangeCurrentRoomObjective(CurrentObjectiveCount);
			}
		}
	}
}

void ABaseRoom::LeaveTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCCharacterBase* character = Cast<ASCCharacterBase>(OtherActor);
		if (character && character->IsLocallyControlled())
		{
			//leave the room
		}
	}
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

