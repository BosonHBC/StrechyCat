// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveItemBase.h"
#include "StretchyCatGameMode.h"
#include <Net/UnrealNetwork.h>
#include <Engine/World.h>
#include "SCBaseController.h"
#include "SCPlayerState.h"
#include "BaseRoom.h"
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
	DOREPLIFETIME(AObjectiveItemBase, CompletedPlayer)
}


void AObjectiveItemBase::CompleteObjective_Implementation(ASCBaseController* playerController)
{
	if (Role == ROLE_Authority && !isCompleted)
	{
		isCompleted = true;
		CompletedPlayer = playerController;
		auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
		if (GM)
		{
			GM->IncCurrentObjectiveCount(RoomAttached);
			UE_LOG(LogTemp, Warning, TEXT("GM Obj ++"));

		}
		if (playerController->IsLocalController())
		{
			playerController->ChangeCurrentRoomObjective(1);
			UE_LOG(LogTemp, Warning, TEXT("CompleteObjective"));
		}
	}
}

bool AObjectiveItemBase::CompleteObjective_Validate(ASCBaseController * playerController)
{
	return true;
}

bool AObjectiveItemBase::UncompleteObjective_Validate(ASCBaseController * playerController)
{
	return true;
}
void AObjectiveItemBase::UncompleteObjective_Implementation(ASCBaseController* playerController)
{

	if (Role == ROLE_Authority && CompletedPlayer == playerController)
	{
		isCompleted = false;
		CompletedPlayer = nullptr;
		auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
		if (GM)
		{
			GM->DecCurrentObjectiveCount(RoomAttached);
			UE_LOG(LogTemp, Warning, TEXT("GM Obj --"));

		}
		if (playerController->IsLocalController())
		{
			playerController->ChangeCurrentRoomObjective(-1);
			UE_LOG(LogTemp, Warning, TEXT("UNCompleteObjective"));
		}
	}
}

