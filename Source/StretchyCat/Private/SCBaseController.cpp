// Fill out your copyright notice in the Description page of Project Settings.

#include "SCBaseController.h"
#include "SCCharacterBase.h"
#include "Engine/World.h"
#include "StretchyCatGameMode.h"

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