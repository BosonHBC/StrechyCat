// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRoom.h"
#include "Components/StaticMeshComponent.h"
#include "SCGameState.h"
#include "ObjectiveItemBase.h"
#include "SCCharacterBase.h"
#include "SCBaseController.h"
#include "SCPlayerState.h"
#include "StretchyCatGameMode.h"
#include <Net/UnrealNetwork.h>
#include "Components/BoxComponent.h"
// Sets default values
ABaseRoom::ABaseRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));
	RoomEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomEntrance"));
	RoomExit = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomExit"));
	RoomSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("CharacterSpawn"));
	RoomEntrance->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RoomEntrance->SetCollisionResponseToAllChannels(ECR_Ignore);
	RoomEntrance->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RoomEntrance->SetupAttachment(RootComponent);
	RoomSpawn->SetupAttachment(RootComponent);
	RoomExit->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RoomExit->SetCollisionResponseToAllChannels(ECR_Ignore);
	RoomExit->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RoomExit->SetupAttachment(RootComponent);
	
	RoomEntrance->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoom::EnterTheRoom);
	RoomExit->OnComponentEndOverlap.AddDynamic(this, &ABaseRoom::LeaveTheRoom);

	SetReplicates(true);
	RoomEntrance->SetIsReplicated(true);
	RoomExit->SetIsReplicated(true);
	IsRoomCompleted = false;
	CurrentObjectiveCount = 0;
	TotalObjectives = 0;

	//add default event
	OnCompleteRoom.BindUFunction(this, TEXT("OnRoomComplete"));
}

// Called when the game starts or when spawned
void ABaseRoom::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor *> children;
	GetAllChildActors(children);
	UE_LOG(LogTemp, Warning, TEXT("Children count %d"), children.Num())
	for (auto child : children)
	{
		auto castto = Cast<AObjectiveItemBase>(child);
		if (castto)
		{
			AllObjectives.Add(castto);
			castto->ItemRoom = this;
		}
	}
	TotalObjectives = AllObjectives.Num();
}

void ABaseRoom::EnterTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCCharacterBase* character = Cast<ASCCharacterBase>(OtherActor);
		if (character != nullptr)
		{
			auto pc = character->GetController<ASCBaseController>();
			if (pc)
			{
				pc->EnterTheRoom(RoomName, CurrentObjectiveCount, TotalObjectives);
				if (Role == ROLE_Authority)
				{
					GetWorld()->GetGameState<ASCGameState>()->SendMessageToUI(FText::FromString(TEXT("Player " + pc->GetPlayerState<ASCPlayerState>()->GetPlayerName() + " Entered room " + RoomName.ToString())));
				}
			}
		}
	}
}

void ABaseRoom::LeaveTheRoom(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCCharacterBase* character = Cast<ASCCharacterBase>(OtherActor);
		if (character != nullptr)
		{
			auto pc = character->GetController<ASCBaseController>();
			if (pc)
			{
				//pc->EnterTheRoom(CurrentObjectiveCount, TotalObjectives);
				if (Role == ROLE_Authority)
				{
					GetWorld()->GetGameState<ASCGameState>()->SendMessageToUI(FText::FromString(TEXT("Player " + pc->GetPlayerState<ASCPlayerState>()->GetPlayerName() + " Left room " + RoomName.ToString())));
				}
			}
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
}

bool ABaseRoom::CompleteObjective(int objNum)
{
	if (IsRoomCompleted)
		return false;
	if (CurrentObjectiveCount + objNum > TotalObjectives)
		return false;
	CurrentObjectiveCount += objNum;
	if (OnCompleteObjective.IsBound())
		OnCompleteObjective.Execute(objNum);

	if (CurrentObjectiveCount == TotalObjectives)
	{
		IsRoomCompleted = true;
		OnCompleteRoom.ExecuteIfBound();
	}
	return true;
}

bool ABaseRoom::UncompleteObjective(int objNum)
{
	if (IsRoomCompleted)
		return false;
	if (CurrentObjectiveCount - objNum < 0)
		return false;
	CurrentObjectiveCount -= objNum;
	if (OnUncompleteObjective.IsBound())
		OnUncompleteObjective.Execute(objNum);
	return true;
}

AObjectiveItemBase * ABaseRoom::GetAnUncompleteObjective() const
{
	for (auto a : AllObjectives)
	{
		if (!a->GetIfCompleted())
			return a;
	}
	return nullptr;
}

