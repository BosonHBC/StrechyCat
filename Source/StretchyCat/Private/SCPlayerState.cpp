// Fill out your copyright notice in the Description page of Project Settings.

#include "SCPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "BaseRoom.h"
#include "StretchyCatGameMode.h"

void ASCPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ASCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPlayerState, CurrentHealth);
	DOREPLIFETIME(ASCPlayerState, MaxHealth);
	DOREPLIFETIME(ASCPlayerState, CurrentObjective);
	DOREPLIFETIME(ASCPlayerState, TotalObjective);
	DOREPLIFETIME(ASCPlayerState, RoomNamePlayerIn);
}

void ASCPlayerState::SetCurrentLife(int _lives)
{
	CurrentHealth = _lives;
}

void ASCPlayerState::SetMaxLife(int _lives)
{
	MaxHealth = _lives;
}

void ASCPlayerState::SetCurrentRoomObj_Implementation(const FName & roomName, int curObj, int totObj)
{
	RoomNamePlayerIn = roomName;
	CurrentObjective = curObj;
	TotalObjective = totObj;
}

int ASCPlayerState::GetCurrentHealth() const
{
	return CurrentHealth;
}

int ASCPlayerState::GetMaxHealth() const
{
	return MaxHealth;
}

