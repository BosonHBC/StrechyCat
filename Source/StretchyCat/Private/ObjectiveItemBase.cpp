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
}

bool AObjectiveItemBase::UncompleteObjective_Validate(ASCBaseController* playerController)
{
	return true;
}

bool AObjectiveItemBase::CompleteObjective_Validate(ASCBaseController* playerController)
{
	return true;
}

void AObjectiveItemBase::CompleteObjective_Implementation(ASCBaseController* playerController)
{
	AStretchyCatGameMode* GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM != nullptr)
	{
		if (!isCompleted)
		{
			isCompleted = true;
			auto playerState = playerController->GetPlayerState<ASCPlayerState>();
			UE_LOG(LogTemp, Warning, TEXT("CompleteObjective"));
			GM->IncCurrentObjectiveCount(playerState->GetCurrentRoom());
		}
	}
	
}

void AObjectiveItemBase::UncompleteObjective_Implementation(ASCBaseController* playerController)
{
	AStretchyCatGameMode* GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM != nullptr)
	{
		if (isCompleted)
		{
			isCompleted = false;
			auto playerState = playerController->GetPlayerState<ASCPlayerState>();
			UE_LOG(LogTemp, Warning, TEXT("UNCompleteObjective"));
			GM->DecCurrentObjectiveCount(playerState->GetCurrentRoom());
		}
	}
}

