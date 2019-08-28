// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveItemBase.h"
#include "StretchyCatGameMode.h"
#include <Net/UnrealNetwork.h>
#include <Engine/World.h>
#include "SCBaseController.h"
#include "SCPlayerState.h"
#include "BaseRoom.h"
#include "SCGameState.h"
// Sets default values
AObjectiveItemBase::AObjectiveItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isCompleted = false;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AObjectiveItemBase::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AObjectiveItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectiveItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AObjectiveItemBase, isCompleted)
}

void AObjectiveItemBase::CompleteItself()
{
	if (!isCompleted)
	{
		isCompleted = true;
		UE_LOG(LogTemp, Warning, TEXT("CompleteItself"));
		if (ItemRoom->CompleteObjective(1))
		{
			if (Role == ROLE_Authority)
			{
				auto gs = GetWorld()->GetGameState<ASCGameState>();
				if (gs)
				{
					gs->PlayerCompleteObjective(ItemRoom, 1);
					gs->SendMessageToUI(FText::FromString(TEXT("A potato just compeleted Obj in Room " + ItemRoom->RoomName.ToString())));
				}
			}
		}
	}
}


void AObjectiveItemBase::CompleteObjective_Implementation(ASCBaseController* playerController)
{
	if (!isCompleted)
	{
		isCompleted = true;
		if (playerController != nullptr)
			playerController->CompleteObjective(ItemRoom);
	}
}

void AObjectiveItemBase::UncompleteObjective_Implementation(ASCBaseController* playerController)
{
	if (isCompleted && !ItemRoom->IsRoomCompleted)
	{
		isCompleted = false;
		if (playerController != nullptr)
		{
			playerController->UncompleteObjective(ItemRoom);
		}
	}
}

