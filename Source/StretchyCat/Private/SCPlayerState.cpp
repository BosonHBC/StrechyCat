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
		//CurrentRoomName = FName("Error Room");
	}
}

void ASCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCPlayerState, CurrentHealth);
	DOREPLIFETIME(ASCPlayerState, MaxHealth);
	DOREPLIFETIME(ASCPlayerState, CurrentRoomName);
	DOREPLIFETIME(ASCPlayerState, CurrentObjective);
	DOREPLIFETIME(ASCPlayerState, TotalObjective);
}
