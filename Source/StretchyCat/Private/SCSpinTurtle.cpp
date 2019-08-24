// Fill out your copyright notice in the Description page of Project Settings.

#include "SCSpinTurtle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Puzzle/SCBulletProjectile.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
ASCSpinTurtle::ASCSpinTurtle()
{
	RotateParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("RotateParentComp"));
	RotateParentComp->SetupAttachment(RootComponent);
	RotateParentComp->SetRelativeLocation(FVector::ZeroVector);

	InteractionPoint->SetupAttachment(RotateParentComp);

	RotateRadSpeed = 300.f;
	currentRotateRadSpeed = 0.f;
	RotateRadSpeedDamping = 600.f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASCSpinTurtle::OnActorHit);
}

void ASCSpinTurtle::ServerUseAbility_Implementation()
{
	//Super::ServerUseAbility();
	bRotating = true;
	bRecovering = false;
	MulticastSetInitialRadSpeed();
}

bool ASCSpinTurtle::ServerUseAbility_Validate()
{
	return true;
}

void ASCSpinTurtle::ServerUnUseAbility_Implementation()
{

	bRecovering = true;
}

bool ASCSpinTurtle::ServerUnUseAbility_Validate()
{
	return true;
}

void ASCSpinTurtle::Interact()
{
	Super::Interact();
}

void ASCSpinTurtle::RecoverRotation()
{

}

void ASCSpinTurtle::MulticastSetInitialRadSpeed_Implementation()
{
	// Set the initial speed to all clients, and let them calculate current speed by themselves
	currentRotateRadSpeed = RotateRadSpeed;
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
					//UE_LOG(LogTemp, Log, TEXT("Yaw: %f"), RotateParentComp->RelativeRotation.Yaw);
				}
			}
		}
	

}

void ASCSpinTurtle::OnActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ASCBulletProjectile* Proj = Cast<ASCBulletProjectile>(OtherActor);
		if (Proj) {
			DrawDebugSphere(GetWorld(), SweepResult.ImpactPoint, 16, 8, FColor::Green, false, 1.f);
			
		}

	}
}

void ASCSpinTurtle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASCSpinTurtle, bRotating);
	DOREPLIFETIME(ASCSpinTurtle, bRecovering);
}
