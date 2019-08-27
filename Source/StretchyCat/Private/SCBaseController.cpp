// Fill out your copyright notice in the Description page of Project Settings.

#include "SCBaseController.h"
#include "SCCharacterBase.h"
#include "Engine/World.h"
#include "StretchyCatGameMode.h"
#include "SCPlayerState.h"
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

void ASCBaseController::ChangeMaxRoomObjective_Implementation(int obj)
{
	ASCPlayerState * PS = GetPlayerState<ASCPlayerState>();
	PS->TotalObjective = obj;
	auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM)
	{
		//GM->SendServerMessageToUI(FText::FromString("Player " + PS->PlayerName + " Goes To " + room->RoomName.ToString()));
	}
}

bool ASCBaseController::ChangeMaxRoomObjective_Validate(int obj)
{
	return true;
}

void ASCBaseController::ChangeCurrentRoomObjective_Implementation(int obj)
{
	ASCPlayerState * ps = GetPlayerState<ASCPlayerState>();
	ps->CurrentObjective += obj;
	auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>();
	if (GM)
	{
		/*if (obj > 0)
			GM->IncCurrentObjectiveCount(ps->CurrentObjective);
		else if (obj < 0)
			GM->DecCurrentObjectiveCount(ps->GetCurrentRoom());*/
		GM->SendServerMessageToUI(FText::FromString("Player " + ps->PlayerName + (obj > 0 ? "": "un") + "completed an obj!"));

	}
}

bool ASCBaseController::ChangeCurrentRoomObjective_Validate(int obj)
{
	return true;
}

void ASCBaseController::ChangeCurrentRoomName_Implementation(const FName & roomName)
{
	ASCPlayerState * PS = GetPlayerState<ASCPlayerState>();
	PS->CurrentRoomName = roomName;
	if (auto GM = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>())
	{
		GM->SendServerMessageToUI(FText::FromString("Player " + PS->PlayerName + " Goes To " + roomName.ToString()));
	}
}

bool ASCBaseController::ChangeCurrentRoomName_Validate(const FName & roomName)
{
	return true;
}