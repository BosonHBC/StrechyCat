// Fill out your copyright notice in the Description page of Project Settings.

#include "SCStretchyCat.h"
#include"Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

ASCStretchyCat::ASCStretchyCat() {

	// Create Extend body
	ExtendBodyCapComp = CreateDefaultSubobject<UCapsuleComponent>("ExtendBody");
	ExtendBodyCapComp->SetupAttachment(RootComponent);
	ExtendBodyCapComp->InitCapsuleSize(32.f, 32.f);

	// Gameplay
	MaxForwardExtendDistance = 250.f;
	BodyShootSpeed = MaxForwardExtendDistance / 0.5f;

	// Body Collider for other to stand
	ExtendBodyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ExtendBoxCol"));
	ExtendBodyComp->SetupAttachment(RootComponent);

	// Override 
	ExtendBodyCapComp->SetRelativeLocation(FVector(0, 0, -30));
	InteractionPoint->SetupAttachment(ExtendBodyCapComp);
	InteractionPoint->SetRelativeLocation(FVector(40.f, 0, 0));

	CollisionParams.AddIgnoredComponent(ExtendBodyComp);
	CollisionParams.AddIgnoredComponent(ExtendBodyCapComp);

	PercentToEnd = 0;
	bAbilityPressed = false;
	bAbilityReleased = false;
}

void ASCStretchyCat::UseAbility()
{
	Super::UseAbility();
	FHitResult OutHit;
	FVector Start = ExtendBodyCapComp->GetComponentLocation();
	FVector Direction = ExtendBodyCapComp->GetForwardVector();

	float RelativeXLocation = MaxForwardExtendDistance;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, Start + Direction * MaxForwardExtendDistance, ECC_Visibility, CollisionParams)) {
		RelativeXLocation = FMath::Min((OutHit.ImpactPoint - Start).Size(), RelativeXLocation);
		DrawDebugLine(GetWorld(), Start, Start + Direction * RelativeXLocation, FColor::Red, true);
	}
	bBodyOutside = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(ExtendBodyCapComp, FVector(RelativeXLocation, 0, -30), FRotator(0.0f, 0.0f, 0.0f), true, false, RelativeXLocation / BodyShootSpeed, false, EMoveComponentAction::Type::Move, LatentInfo);
	bAbilityPressed = true;
	bAbilityReleased = false;
}

void ASCStretchyCat::UnUseAbility()
{
	Super::UnUseAbility();

	float RelativeXLocation = ExtendBodyCapComp->RelativeLocation.X;
	bAbilityReleased = true;
	bAbilityPressed = false;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(ExtendBodyCapComp, FVector(0, 0, -30), FRotator(0.0f, 0.0f, 0.0f), false, true, 2 * RelativeXLocation / BodyShootSpeed, false, EMoveComponentAction::Type::Move, LatentInfo);

}

void ASCStretchyCat::Interact()
{
	Super::Interact();

}

void ASCStretchyCat::OnBodyBackTOBody() {
	UE_LOG(LogTemp, Log, TEXT("Body Back!"));
}

void ASCStretchyCat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), InteractionPoint->GetComponentLocation(), 16, 8, FColor::Blue);
	if (bBodyOutside) {
		FVector RelativeLoc = ExtendBodyCapComp->RelativeLocation;
		PercentToEnd = 1 - (MaxForwardExtendDistance - ExtendBodyCapComp->RelativeLocation.X) / MaxForwardExtendDistance;
		RelativeLoc.X = (GetCapsuleComponent()->GetUnscaledCapsuleRadius() + ExtendBodyCapComp->RelativeLocation.X) / 2.f;
		ExtendBodyComp->SetRelativeLocation(RelativeLoc);
		FVector NewExtent((ExtendBodyCapComp->RelativeLocation.X - GetCapsuleComponent()->GetUnscaledCapsuleRadius()) / 2, 25.f, 25.f);
		ExtendBodyComp->SetBoxExtent(NewExtent);
		DrawDebugBox(GetWorld(), ExtendBodyComp->GetComponentLocation(), NewExtent, ExtendBodyComp->GetComponentRotation().Quaternion(),FColor::Yellow);

		if (ExtendBodyCapComp->RelativeLocation.X <= 0.01f) {
			bBodyOutside = false;
			ExtendBodyCapComp->SetRelativeLocation(FVector(0, 0, -30));
		}
	}

}