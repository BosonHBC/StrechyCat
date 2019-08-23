// Fill out your copyright notice in the Description page of Project Settings.

#include "SCSpinTurtle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SceneComponent.h"
ASCSpinTurtle::ASCSpinTurtle()
{
	RotateParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("RotateParentComp"));
	
	RotateMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateComp"));
	RotateMovementComp->UpdatedComponent = RotateParentComp;

	InteractionPoint->SetupAttachment(RotateParentComp);
}

void ASCSpinTurtle::UseAbility()
{
	Super::UseAbility();
}

void ASCSpinTurtle::UnUseAbility()
{
	Super::UnUseAbility();
}

void ASCSpinTurtle::Interact()
{
	Super::Interact();
}

void ASCSpinTurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
