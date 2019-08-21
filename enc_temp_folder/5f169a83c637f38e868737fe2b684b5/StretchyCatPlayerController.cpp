// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StretchyCatPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "StretchyCatCharacter.h"
#include "Engine/World.h"

AStretchyCatPlayerController::AStretchyCatPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AStretchyCatPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AStretchyCatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

