// Fill out your copyright notice in the Description page of Project Settings.

#include "SCPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "StretchyCatGameMode.h"

void ASCPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (Role == ROLE_Authority)
	{
		CurrentRoom = GetWorld()->GetAuthGameMode<AStretchyCatGameMode>()->InitialRoom;
	}
}

void ASCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPlayerState, CurrentHealth);
	DOREPLIFETIME(ASCPlayerState, MaxHealth);
	DOREPLIFETIME_CONDITION(ASCPlayerState, CurrentRoom, COND_OwnerOnly);
}

void ASCPlayerState::SetCurrentLife(int _lives)
{
	CurrentHealth = _lives;
}

void ASCPlayerState::SetMaxLife(int _lives)
{
	MaxHealth = _lives;
}

void ASCPlayerState::SetCurrentRoom(ABaseRoom* room)
{
	CurrentRoom = room;
}

int ASCPlayerState::GetCurrentHealth() const
{
	return CurrentHealth;
}

int ASCPlayerState::GetMaxHealth() const
{
	return MaxHealth;
}

ABaseRoom* ASCPlayerState::GetCurrentRoom() const
{
	return CurrentRoom;
}
