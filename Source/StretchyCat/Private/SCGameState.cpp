// Fill out your copyright notice in the Description page of Project Settings.

#include "SCGameState.h"

ASCGameState::ASCGameState()
{
	CurrentSharedLife = MaxSharedLife;
}

void ASCGameState::GetDamage(uint16 _dmg)
{
	CurrentSharedLife -= _dmg;
	if (CurrentSharedLife <= 0) {
		CurrentSharedLife = 0;
		GameOver(false);
	}
}
