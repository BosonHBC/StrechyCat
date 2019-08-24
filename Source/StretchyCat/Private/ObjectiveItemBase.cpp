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

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AObjectiveItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectiveItemBase::Internal_UncompleteObjective(ASCBaseController* playerController)
{
	AStretchyCatGameMode* GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM != nullptr)
	{
		if (isCompleted)
		{
			isCompleted = false;
			auto playerState = playerController->GetPlayerState<ASCPlayerState>();
			GM->DecCurrentObjectiveCount(playerState->GetCurrentRoom());
		}
	}
}

void AObjectiveItemBase::Internal_CompleteObjective(ASCBaseController* playerController)
{
	AStretchyCatGameMode* GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM != nullptr)
	{
		if (!isCompleted)
		{
			isCompleted = true;
			auto playerState = playerController->GetPlayerState<ASCPlayerState>();
			GM->IncCurrentObjectiveCount(playerState->GetCurrentRoom());
		}
	}
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

void AObjectiveItemBase::CompleteObjective_Implementation(ASCBaseController* playerController)
{
	Internal_CompleteObjective(playerController);
	
}

void AObjectiveItemBase::UncompleteObjective_Implementation(ASCBaseController* playerController)
{
	Internal_UncompleteObjective(playerController);
}

