// Fill out your copyright notice in the Description page of Project Settings.

#include "SCSpinTurtle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
ASCSpinTurtle::ASCSpinTurtle()
{
	RotateParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("RotateParentComp"));
	RotateParentComp->SetupAttachment(RootComponent);
	RotateParentComp->SetRelativeLocation(FVector::ZeroVector);

	InteractionPoint->SetupAttachment(RotateParentComp);

	RotateRadSpeed = 300.f;
	currentRotateRadSpeed = 0.f;
	RotateRadSpeedDamping = 600.f;
}

void ASCSpinTurtle::UseAbility()
{
	Super::UseAbility();
	bRotating = true;
	bRecovering = false;
	currentRotateRadSpeed = RotateRadSpeed;
}

void ASCSpinTurtle::UnUseAbility()
{
	Super::UnUseAbility();
	bRecovering = true;
}

void ASCSpinTurtle::Interact()
{
	Super::Interact();
}

void ASCSpinTurtle::RecoverRotation()
{

}

void ASCSpinTurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating) {
		FRotator newRot = RotateParentComp->RelativeRotation;
		newRot.Yaw += DeltaTime * currentRotateRadSpeed;
		RotateParentComp->SetRelativeRotation(newRot);
		newRot.Yaw -= 90.f;
		GetMesh()->SetRelativeRotation(newRot);

		if (bRecovering) {
			currentRotateRadSpeed -= RotateRadSpeedDamping * DeltaTime;
			if (currentRotateRadSpeed < 200.f) {
				currentRotateRadSpeed = 200.f;
				if (RotateParentComp->RelativeRotation.Yaw > -3.f && RotateParentComp->RelativeRotation.Yaw < 3.f) {
					bRotating = false;
					RotateParentComp->SetRelativeRotation(FRotator::ZeroRotator);
					FRotator endRot = RotateParentComp->RelativeRotation;
					endRot.Yaw -= 90;
					GetMesh()->SetRelativeRotation(endRot);
					
				}
				UE_LOG(LogTemp, Log, TEXT("Yaw: %f"), RotateParentComp->RelativeRotation.Yaw);
			}
		}
	}
}
