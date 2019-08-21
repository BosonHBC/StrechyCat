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

		FHitResult OutHit(ForceInit);
		GetHitResultUnderCursor(ECC_Visibility, false, OutHit);
		if (OutHit.GetActor() != nullptr) {
			FVector norm = OutHit.ImpactPoint - GetPawn()->GetActorLocation();
			norm.Normalize();
			FRotator newLookAt = FRotationMatrix::MakeFromX(norm).Rotator();
			newLookAt.Pitch = 0;
			newLookAt.Roll = 0;
			FRotator NewRot = FMath::RInterpTo(GetControlRotation(), newLookAt, DeltaTime, 8);
			SetControlRotation(NewRot);
		}
	
}

void AStretchyCatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

