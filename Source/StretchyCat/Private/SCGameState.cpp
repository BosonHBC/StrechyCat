// Fill out your copyright notice in the Description page of Project Settings.

#include "SCGameState.h"
#include "Engine/World.h"
#include "SCBaseController.h"
#include "SCPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "BaseRoom.h"
ASCGameState::ASCGameState()
{
	/*CurrentObjective = 0;
	ObjectiveGoal = 0;*/
}


void ASCGameState::ChangeLifeCount_Implementation(int cur_health, int max_health)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ASCBaseController * scBC = Cast<ASCBaseController>(It->Get());
		if (scBC && scBC->IsLocalController())
		{
			ASCPlayerState * scPS = scBC->GetPlayerState<ASCPlayerState>();
			scPS->SetCurrentLife(cur_health);
		}
	}
}

//void ASCGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(ASCGameState, ObjectiveGoal);
//	DOREPLIFETIME(ASCGameState, CurrentObjective);
//}

//void ASCGameState::SetGameObjective(int cur_obj, int max_obj)
//{
//	if (cur_obj < 0)
//	{
//		cur_obj = 0;
//		UE_LOG(LogTemp, Warning, TEXT("Current obj  < 0!!!"));
//	}
//	if (max_obj < 0)
//	{
//		max_obj = 0;
//		UE_LOG(LogTemp, Warning, TEXT("Max obj  < 0!!!"));
//	}
//	CurrentObjective = cur_obj;
//	ObjectiveGoal = max_obj;
//}

void ASCGameState::GameOver_Implementation(bool _success)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ASCBaseController * scBC = Cast<ASCBaseController>(It->Get());
		if (scBC && scBC->IsLocalController())
		{
			scBC->DisableInput(scBC);
			scBC->ShowServerMessage(FText::FromString(TEXT("YOU DIED")));
		}
	}
}

void ASCGameState::SendMessageToUI_Implementation(const FText& message)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ASCBaseController * scBC = Cast<ASCBaseController>(It->Get());
		if (scBC && scBC->IsLocalController())
		{
			scBC->ShowServerMessage(message);
		}
	}
}
