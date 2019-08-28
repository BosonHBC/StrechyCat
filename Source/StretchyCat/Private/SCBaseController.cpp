// Fill out your copyright notice in the Description page of Project Settings.

#include "SCBaseController.h"
#include "SCCharacterBase.h"
#include "Engine/World.h"
#include "StretchyCatGameMode.h"
#include "SCPlayerState.h"
#include "SCGameState.h"
#include "BaseRoom.h"

ASCBaseController::ASCBaseController()
{
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASCBaseController::SelectCharacterClass_Implementation(TSubclassOf<class ASCCharacterBase> selectedClass)
{
	auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM)
	{
		GM->CreateSelectedPawn(selectedClass, this);
		UE_LOG(LogTemp, Display, TEXT("Character Created"));
	}
}
bool ASCBaseController::SelectCharacterClass_Validate(TSubclassOf<class ASCCharacterBase> selectedClass)
{
	return true;
}

void ASCBaseController::CompleteObjective(ABaseRoom * room)
{
	if (room->CompleteObjective(1))
	{
		if (Role == ROLE_Authority)
		{
			auto gs = GetWorld()->GetGameState<ASCGameState>();
			if (gs)
			{
				ASCPlayerState * PS = GetPlayerState<ASCPlayerState>();
				gs->PlayerCompleteObjective(room, 1);
				gs->SendMessageToUI(FText::FromString(TEXT("Player " + PS->GetPlayerName() + " Compelete Obj in Room " + room->RoomName.ToString())));
			}
		}
	}
}

void ASCBaseController::UncompleteObjective(ABaseRoom * room)
{
	if (room->UncompleteObjective(1))
	{
		if (Role == ROLE_Authority)
		{
			auto gs = GetWorld()->GetGameState<ASCGameState>();
			if (gs)
			{
				ASCPlayerState * PS = GetPlayerState<ASCPlayerState>();
				gs->PlayerCompleteObjective(room, -1);
				gs->SendMessageToUI(FText::FromString(TEXT("Player " + PS->GetPlayerName() + " Uncompelete Obj in Room " + room->RoomName.ToString())));
			}
		}
	}
}

void ASCBaseController::EnterTheRoom(const FName& roomName, int curObj, int totalObj)
{
	ASCPlayerState * playerState = GetPlayerState<ASCPlayerState>();
	if (playerState)
	{
		playerState->RoomNamePlayerIn = roomName;
		playerState->CurrentObjective = curObj;
		playerState->TotalObjective = totalObj;
		OnPlayerEnterRoom();
	}

}
