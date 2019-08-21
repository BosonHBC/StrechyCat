// Fill out your copyright notice in the Description page of Project Settings.

#include "SCStretchyCat.h"
#include"Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
ASCStretchyCat::ASCStretchyCat() {

	// Create Extend body
	ExtendBodyCapComp = CreateDefaultSubobject<UCapsuleComponent>("ExtendBody");
	ExtendBodyCapComp->SetupAttachment(RootComponent);
	ExtendBodyCapComp->InitCapsuleSize(32.f, 32.f);

	// Gameplay
	MaxForwardExtendDistance = 250.f;
	BodyShootSpeed = MaxForwardExtendDistance / 0.5f;
}

void ASCStretchyCat::UseAbility()
{
	Super::UseAbility();
	UE_LOG(LogTemp, Log, TEXT("Using Ability"));
	FHitResult OutHit;
	FVector Start = ExtendBodyCapComp->GetComponentLocation();
	FVector Direction = ExtendBodyCapComp->GetForwardVector();
	FCollisionQueryParams CollisionParams;
	float RelativeXLocation = MaxForwardExtendDistance;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, Start + Direction * MaxForwardExtendDistance, ECC_Visibility, CollisionParams)) {
		RelativeXLocation = FMath::Min((OutHit.ImpactPoint - Start).Size(), RelativeXLocation);
	}

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(ExtendBodyCapComp, FVector(RelativeXLocation, 0, 0), FRotator(0.0f, 0.0f, 0.0f), true, false, RelativeXLocation / BodyShootSpeed, false, EMoveComponentAction::Type::Move, LatentInfo);


}

void ASCStretchyCat::UnUseAbility()
{
	Super::UnUseAbility();

	float RelativeXLocation = ExtendBodyCapComp->RelativeLocation.X;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(ExtendBodyCapComp, FVector(0, 0, 0), FRotator(0.0f, 0.0f, 0.0f), true, false, 2 * RelativeXLocation / BodyShootSpeed, false, EMoveComponentAction::Type::Move, LatentInfo);

}

void ASCStretchyCat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}