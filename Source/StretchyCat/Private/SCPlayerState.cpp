// Fill out your copyright notice in the Description page of Project Settings.

#include "SCPlayerState.h"
#include "Net/UnrealNetwork.h"

void ASCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPlayerState, CurrentHealth);
	DOREPLIFETIME(ASCPlayerState, MaxHealth);
}

void ASCPlayerState::SetCurrentLife(int _lives)
{
	CurrentHealth = _lives;
}

void ASCPlayerState::SetMaxLife(int _lives)
{
	MaxHealth = _lives;
}

int ASCPlayerState::GetCurrentHealth()
{
	return CurrentHealth;
}

int ASCPlayerState::GetMaxHealth()
{
	return MaxHealth;
}
