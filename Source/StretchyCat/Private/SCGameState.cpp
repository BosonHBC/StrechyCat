// Fill out your copyright notice in the Description page of Project Settings.

#include "SCGameState.h"
#include "Engine/World.h"
#include "SCBaseController.h"
#include "SCPlayerState.h"
ASCGameState::ASCGameState()
{
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
